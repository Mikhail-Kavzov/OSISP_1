#pragma once
#include <Windows.h>
#include <gdiplus.h>

namespace Drawing{
	using namespace Gdiplus;

	class Entity {
	public:
		virtual void Move(int dx, int dy) = 0;
		virtual void Draw(HDC hdc) = 0;
		virtual bool IsBorder(int left, int top, int right, int bottom) = 0;
	};
}
