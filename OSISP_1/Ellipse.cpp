#include "Ellipse.h"

namespace Drawing {
	Ellipse::Ellipse() :Ellipse(100, 100, 70, 30) {
	}

	Ellipse::Ellipse(int xCenter, int yCenter, int a, int b) : xCenter(xCenter), yCenter(yCenter), a(a), b(b) {
	}

	void Ellipse::Draw(HDC hdc) {
		Graphics graphics(hdc);
		Pen pen(Color::Black);
		SolidBrush brush(Color::Red);
		RectF ellipseRect(xCenter - a, yCenter - b, xCenter + a, yCenter + b);
		graphics.FillEllipse(&brush, ellipseRect);
		graphics.DrawEllipse(&pen, ellipseRect);
	}

	void Ellipse::Move(int dx, int dy) {
		xCenter += dx;
		yCenter += dy;
	}

	inline bool Ellipse::IsBorder(int left, int top, int right, int bottom) {
		return (xCenter - a <= left || xCenter + a >= right) || (yCenter - b <= top || yCenter + b >= bottom);
	}
}