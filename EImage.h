#ifndef _E_IMAGE_H_
#define _E_IMAGE_H_

namespace Eg {

	class EImage {
		int imageWidth, imageHeight;
		unsigned tex;
	public:
		EImage();
		bool load(const char* name);
		void bind();
		int width() const {
			return imageWidth;
		}
		int height() const {
			return imageHeight;
		}
	};
	
}

#endif
