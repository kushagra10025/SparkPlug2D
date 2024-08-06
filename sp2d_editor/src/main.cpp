#define SDL_MAIN_HANDLED 1;

#include "Application.h"

int main(int argc, char** argv)
{
	auto& app = SP2D::Editor::Application::GetInstance();
	app.Run();

	return 0;
}