#include "Image.h"
namespace Drawing {
	Image::Image(int x, int y,const wchar_t* path):Rectangle(x,y,0,0) {
		img=Gdiplus::Image::FromFile(path);
		width = img->GetWidth();
		height = img->GetHeight();
	
	}
	void Image::Draw(HDC hdc) {		
		Graphics    graphics(hdc);
		graphics.DrawImage(img, x, y, width, height);
	}

}