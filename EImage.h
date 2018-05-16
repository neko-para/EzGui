#ifndef _E_IMAGE_H_
#define _E_IMAGE_H_

namespace Eg {

	class EImage {
		int width, height;
		unsigned tex;
	public:
		EImage();
		bool load(const char* name);
		void bind();
	};
	
}

#endif
