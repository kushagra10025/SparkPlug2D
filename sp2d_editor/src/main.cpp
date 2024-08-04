#define SDL_MAIN_HANDLED 1;
#include <Windowing/Window/Window.h>
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

int main(int argc, char** argv)
{
	bool running = true;

	// Init SDL
	SDL_SetMainReady();
	
	// if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // This can be used instead of individually adding the INIT Flags.
	// Removed the SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER flags as they were adding Delay in INIT
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_HAPTIC) != 0)
	{
		std::string error = SDL_GetError();
		std::cout << "SDL Init Failed! : " << error << std::endl;
		running = false;
		return -1;
	}

	// Setup OpenGL
	if (SDL_GL_LoadLibrary(NULL) != 0)
	{
		std::string error = SDL_GetError();
		std::cout << "SDL OpenGL Load Failed! : " << error << std::endl;
		running = false;
		return -1;
	}

	// Set OpenGL Attribs
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Set Number of Bits per Channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Hardware Acceleration

	// Create the Window
	//SP2D::Windowing::Window window("Demo Window", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true, SDL_WINDOW_OPENGL);
	SP2D::Windowing::Window window("Demo Window", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true, (SDL_WINDOW_OPENGL));

	if (!window.GetWindow())
	{
		std::cout << "SDL Window Creation Failed! : " << std::endl;
		running = false;
		return -1;
	}

	// Create the OpenGL Context
	window.SetGLContext(SDL_GL_CreateContext(window.GetWindow().get()));

	if (!window.GetGLContext())
	{
		std::string error = SDL_GetError();
		std::cout << "SDL Failed to Create OpenGL Context! : " << error << std::endl;
		running = false;
		return -1;
	}

	SDL_GL_MakeCurrent(window.GetWindow().get(), window.GetGLContext());
	SDL_GL_SetSwapInterval(1);

	// Initialize Glad
	if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
	{
		std::cout << "Failed to Initialize GLAD! : " << std::endl;
		running = false;
		return -1;
	}

	SDL_Event event{};

	// Window Loop
	while (running)
	{
		// Process Events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym = SDLK_ESCAPE)
					running = false;
				break;
			default:
				break;
			}
		}

		glViewport(
			window.GetXPos(),
			window.GetYPos(),
			window.GetWidth(),
			window.GetHeight()
		);

		glClearColor(0.f, 0.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window.GetWindow().get());
	}

	SDL_Quit();
	std::cout << "Closing!" << std::endl;

	return 0;
}