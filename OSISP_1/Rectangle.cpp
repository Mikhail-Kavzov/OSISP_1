#include "Rectange.h"

namespace Drawing {

	Rectangle::Rectangle() :Rectangle(100, 100, 200, 200) {
	}

	Rectangle::Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
	}
	void Rectangle::Draw(HDC hdc) {
		Graphics graphics(hdc);
		Pen pen(Color::Black);
		SolidBrush brush(Color::Blue);
		Rect rect(x, y, width, height);
		graphics.FillRectangle(&brush, rect);
		graphics.DrawRectangle(&pen, rect);
	}
	void Rectangle::Move(int dx, int dy) {
		x += dx;
		y += dy;
	}
	
	inline bool Rectangle::IsBorder(int left, int top, int right, int bottom) {
		return (x <= left || x + width >= right) || (y <= top || y + height >= bottom);
	}
}