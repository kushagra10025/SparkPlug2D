#include "SDL_Wrappers.h"

#include <iostream>

void SP2D::Utils::SDL_Destroyer::operator()(SDL_Window* window) const
{
	SDL_DestroyWindow(window);
	std::cout << "Destroyed SDL Window\n";
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
