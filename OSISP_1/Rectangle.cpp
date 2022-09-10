#include "Rectange.h"

namespace Drawing {

	Rectangle::Rectangle() :Rectangle(100, 100, 200, 200) {
	}

	Rectangle::Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
	}
	void Rectangle::Draw(HDC hdc) {
		HPEN hPen = CreatePen(PS_SOLID, 1, Color::Black);
		HBRUSH hBrush = CreateSolidBrush(Color::Blue);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		::Rectangle(hdc, x, y, x + width, y + height);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
	void Rectangle::Move(int dx, int dy) {
		x += dx;
		y += dy;
	}
	
	inline bool Rectangle::IsBorder(int left, int top, int right, int bottom) {
		return (x <= left || x + width >= right) || (y <= top || y + height >= bottom);
	}
}