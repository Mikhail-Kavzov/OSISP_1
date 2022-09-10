#pragma once
#include "Entity.h"

namespace Drawing {
	class Ellipse : public Entity {
		int xCenter, yCenter, a, b;
	public:
		Ellipse();
		Ellipse(int x, int y, int a, int b);
		void Move(int dx, int dy) override;
		void Draw(HDC hdc) override;
		bool IsBorder(int left, int top, int right, int bottom) override;
	};
}
