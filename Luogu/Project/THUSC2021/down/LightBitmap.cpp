#include "LightImage.h"

namespace Light
{
	void Image::SaveBitmapToFile(const char *_path) const
	{
		printf("Saving bitmap: '%s'\n", _path);
		FILE* pFile;
		pFile = fopen(_path, "wb");
		UINT rw = width, rh = height;
		UINT widthBytes = ((rw * 3 + 3) / 4) * 4;
		BITMAPFILEHEADER fileheader = { 0x4d42, 54 + widthBytes * rh, 0, 0, 0x36 };
		BITMAPINFOHEADER infoheader = { 0x28, (int)rw, (int)rh, 1, 0x18, 0, 0, 0, 0, 0, 0 };
		int res;
		res = fwrite(&fileheader, sizeof(fileheader), 1, pFile);
		res = fwrite(&infoheader, sizeof(infoheader), 1, pFile);
		for (int y = rh - 1; y >= 0; y--)
		{
			res = fwrite(pixels + y * width, sizeof(Color), width, pFile);
			for (int i = 0; i < widthBytes - 3 * width; i++)
				fputc(0, pFile);
		}
		fclose(pFile);
	    
		return;
	}
}
