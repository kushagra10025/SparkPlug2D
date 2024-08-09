#include "Button.h"

void SP2D::Windowing::Inputs::Button::Update(bool bPressed)
{

	bJustPressed = !bIsPressed && bPressed;
	bJustReleased = bIsPressed && !bPressed;
	bIsPressed = bPressed;
}

void SP2D::Windowing::Inputs::Button::Reset()
{
	bJustPressed = false;
	bJustReleased = false;
}


