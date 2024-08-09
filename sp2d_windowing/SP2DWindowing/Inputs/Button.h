#pragma once

namespace SP2D::Windowing::Inputs
{
	struct Button
	{
		bool bIsPressed{ false }, bJustPressed{ false }, bJustReleased{ false };
		void Update(bool bPressed);
		void Reset();
	};
}
