#pragma once
#include <Windows.h>

namespace MColor {
	enum Color {
		Black = RGB(0, 0, 0),
		Green = RGB(0, 255, 0),
		Blue = RGB(0, 0, 255),
		Red = RGB(255, 0, 0),
		White = RGB(255, 255, 255),
		Yellow = RGB(255, 255, 0),
		Brown = RGB(139, 69, 19),
		Orange = RGB(255, 140, 0),
		Purple = RGB(148, 0, 211),
		LightBlue = RGB(0, 255, 255),
		Magenta = RGB(255, 0, 255)
	};
}