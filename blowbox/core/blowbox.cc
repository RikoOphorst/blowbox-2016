#include "blowbox.h"

#include "../util/macros.h"
#include "../graphics/direct3d/renderer.h"

#include <iostream>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Blowbox::Blowbox() :
		renderer_(nullptr),
		can_run_(false),
		running_(false)
	{

	}
	
	//------------------------------------------------------------------------------------------------------
	Blowbox::~Blowbox()
	{
		BB_SAFE_DELETE(renderer_);
	}

	//------------------------------------------------------------------------------------------------------
	Blowbox* Blowbox::Create()
	{
		return new Blowbox();
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Initialise()
	{
		BB_ASSERT_NOTNULL(renderer_, "A renderer has to be set in order to initialise Blowbox. Use Blowbox::SetRenderer() to set a renderer.");

		renderer_->Initialise();

		can_run_ = true;
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Run()
	{
		BB_ASSERT(can_run_, "Blowbox has to be initialised before it can be run. Use Blowbox::Initialise() to initialise Blowbox.");

		running_ = true;

		while (running_)
		{
			renderer_->Draw();
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	void Blowbox::SetRenderer(direct3d::Renderer* renderer)
	{
		renderer_ = renderer;
	}
}