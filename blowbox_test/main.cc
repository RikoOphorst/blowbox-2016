#include "blowbox/blowbox_include.h"

using namespace blowbox;
using namespace blowbox::direct3d;

int main(int argc, char** argv)
{
	Blowbox* blowbox = Blowbox::Create();

	Renderer* renderer = Renderer::Create();
	blowbox->SetRenderer(renderer);

	Window* window = Window::MakeWindow("A blowbox game", 1280, 720);
	renderer->SetWindow(window);

	GameObject* player = GameObject::Create();

	blowbox->Initialise();
	blowbox->Run();

	delete blowbox;

	return 0;
}