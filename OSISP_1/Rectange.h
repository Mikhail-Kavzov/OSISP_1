#pragma once
#include "Entity.h"

namespace Drawing {
	class Rectangle :public Entity {
	protected:
		int x, y, width, height;
	public:
		Rectangle();
		Rectangle(int x, int y, int width, int height);
		void Move(int dx, int dy) override;
		void Draw(HDC hdc) override;
		bool IsBorder(int left, int top, int right, int bottom) override;
	};
}