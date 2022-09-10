#include "Image.h"

namespace Drawing {
	Image::Image(int x, int y,const wchar_t* path):Rectangle(x,y,0,0) {
		hBitMap=(HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
		BITMAP bitMap;
		GetObject(hBitMap, sizeof(BITMAP), &bitMap);
		width = bitMap.bmWidth;
		height = bitMap.bmHeight;
	}
	void Image::Draw(HDC hdc) {		
 		HDC memDC = CreateCompatibleDC(hdc);
		HGDIOBJ oldBmp = SelectObject(memDC, hBitMap);
		StretchBlt(hdc, x,y, width, height, memDC, 0, 0, width,
			height, SRCCOPY);
		SelectObject(memDC, oldBmp);
		DeleteDC(memDC);
	}
}