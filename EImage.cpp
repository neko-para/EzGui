#include "global.h"
#include "EImage.h"

namespace Eg {
	
	EImage::EImage() {
		width = height = 0;
		tex = 0;
	}

	bool EImage::load(const char* name) {
		GLint i;
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFileType(name, 0);
		if (fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilename(name);
		}
		FIBITMAP* fib = FreeImage_Load(fif, name, 0);
		if (!fib) {
			return false;
		}
		FIBITMAP* temp = fib;
		fib = FreeImage_ConvertTo32Bits(fib);
		FreeImage_Unload(temp);
		GLubyte* data = (GLubyte*)FreeImage_GetBits(fib);
		if (!data) {
			FreeImage_Unload(fib);
			return false;
		}
		width = FreeImage_GetWidth(fib);
		height = FreeImage_GetHeight(fib);
		for (i = 0; i < width * height; ++i) {
			GLubyte temp = data[i << 2];
			data[i << 2] = data[(i << 2) | 2];
			data[(i << 2) | 2] = temp;
		}
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		FreeImage_Unload(fib);
		return true;
	}

	void EImage::bind() {
		glBindTexture(GL_TEXTURE_2D, tex);
	}
}
