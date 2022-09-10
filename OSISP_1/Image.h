#pragma once
#include "Rectange.h"

namespace Drawing {
	class Image :public Rectangle {
		HBITMAP hBitMap;
	public:
		Image(int x, int y,const wchar_t* path);
		void Draw(HDC hdc) override;
		~Image() {
			delete hBitMap;
		}
	};
}