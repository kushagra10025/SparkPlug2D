#include "SDL_Wrappers.h"
#include <iostream>
#include <SP2DLogging/Log.h>

void SP2D::Utils::SDL_Destroyer::operator()(SDL_Window* window) const
{
	SDL_DestroyWindow(window);
	SP2D_CORE_INFO("Destroyed SDL Window");
}

void SP2D::Utils::SDL_Destroyer::operator()(SDL_GameController* controller) const
{

}

void SP2D::Utils::SDL_Destroyer::operator()(SDL_Cursor* cursor) const
{

}

Controller make_shared_controller(SDL_GameController* controller)
{

}

Cursor make_shared_controller(SDL_Cursor* cursor)
{

}
