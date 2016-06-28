#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>
#include <vector>

#define BB_CONSOLE_SERVER_PORT 60000
#define BB_CONSOLE_MAX_CLIENTS 1

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

int main(int argc, char** argv)
{
	//#ifdef HEAP_INSPECTOR_ENABLED
	//	HeapInspectorServer::InitialiseHeapHooks();
	//	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	//	HeapInspectorServer::SetHeapName(0, "blowbox_main");
	//#endif

	MemoryManager::Create();
	FreeListAllocator* allocator = MemoryManager::Instance()->ConstructAllocator<FreeListAllocator>(sizeof(Console) * 10000);
	Console* console = Console::Create(allocator);

	BB_REPORT("This is a log",		BB_MESSAGE_TYPE_LOG);
	BB_REPORT("This is a warning",	BB_MESSAGE_TYPE_WARNING);
	BB_REPORT("This is a error",	BB_MESSAGE_TYPE_ERROR);

	/*Blowbox* blowbox = Blowbox::Create();
	Window* window = Window::MakeWindow("blowbox", 800, 600);
	Renderer* renderer = Renderer::Create();
	blowbox->SetWindow(window);
	blowbox->SetRenderer(renderer);

	Camera* camera = Camera::Create(BB_CAMERA_PROJECTION_MODES::BB_CAMERA_PROJECTION_MODE_PERSPECTIVE);

	renderer->SetWindow(window);
	renderer->SetCamera(camera);

	blowbox->Initialise();

	blowbox->Run();

	std::cin.get();*/

//#ifdef HEAP_INSPECTOR_ENABLED
//	HeapInspectorServer::Shutdown();
//	HeapInspectorServer::ShutdownHeapHooks();
//#endif
	return 0;
}