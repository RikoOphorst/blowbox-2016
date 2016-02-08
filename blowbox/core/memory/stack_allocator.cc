#include "stack_allocator.h"

#include "../../../blowbox/util/macros.h"
#include "../../../blowbox/core/memory/pointer_util.h"
#include "../../../blowbox/core/memory/heap_inspector.h"

namespace blowbox
{
	namespace memory
	{
		StackAllocator::StackAllocator(void* start, const size_t& size) :
			Allocator(start, size),
			top_(start),
			prev_alloc_(nullptr)
		{

		}

		StackAllocator::~StackAllocator()
		{
		
		}

		void* StackAllocator::Allocate(const size_t& size, const uint32_t& alignment)
		{
			BB_ASSERT(size != 0 && alignment != 0, "Size and/or alignment cannot be null");
			
			uint32_t adjustment = PointerUtil::AlignForwardAdjustmentWithHeader(top_, alignment, sizeof(AllocationHeader));

			BB_ASSERT(used_memory_ + size + adjustment < size_, "Not enough space left in StackAllocator");
			
			uintptr_t aligned_address = (uintptr_t)top_ + adjustment;

			AllocationHeader* header = (AllocationHeader*)(aligned_address - sizeof(AllocationHeader));
			header->prev_alloc = prev_alloc_;
			header->adjustment = adjustment;

			prev_alloc_ = (void*)aligned_address;
			top_ = (void*)(aligned_address + size);

			used_memory_ += size + adjustment;
			num_allocations_++;

			if (heap_inspector_notifications_enabled_)
			{
				BB_HEAP_ALLOC(header, sizeof(AllocationHeader));
				BB_HEAP_ALLOC((void*)aligned_address, size);
			}

			return (void*)aligned_address;
		}

		void StackAllocator::Deallocate(void* ptr)
		{
			BB_ASSERT(ptr == prev_alloc_, "You can only deallocate the last allocated object in this allocator");

			AllocationHeader* header = (AllocationHeader*)(PointerUtil::Subtract(ptr, sizeof(AllocationHeader)));

			used_memory_ -= (uintptr_t)top_ - (uintptr_t)ptr + header->adjustment;
			num_allocations_--;

			top_ = PointerUtil::Subtract(ptr, header->adjustment);
			prev_alloc_ = header->prev_alloc;

			{
				BB_HEAP_BEGIN_FREE();
				BB_HEAP_END_FREE(header);
			}

			{
				BB_HEAP_BEGIN_FREE();
				BB_HEAP_END_FREE(ptr);
			}
		}
	}
}