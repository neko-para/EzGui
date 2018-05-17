#include "global.h"
#include "EPainter.h"
#include <assert.h>

namespace Eg {
	
	EPainter::EPainter() {

	}

	void EPainter::draw(DrawMode mode, const PointData& vertexs, const ColorData& colors) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(2, GL_DOUBLE, 0, vertexs.data());
		glColorPointer(4, GL_DOUBLE, 0, colors.data());
		glDrawArrays(mode, 0, vertexs.size() / 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	void EPainter::draw(DrawMode mode, const PointData& vertexs, const PointData& texcoords) {
		glEnableClientState(GL_VERTEX_ARRAY);
		assert(glGetError());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		assert(glGetError());
		glVertexPointer(2, GL_DOUBLE, 0, vertexs.data());
		assert(glGetError());
		glTexCoordPointer(2, GL_DOUBLE, 0, texcoords.data());
		assert(glGetError());
		glDrawArrays(mode, 0, vertexs.size() / 2);
		assert(glGetError());
		glDisableClientState(GL_VERTEX_ARRAY);
		assert(glGetError());
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		assert(glGetError());
	}

	void EPainter::draw(DrawMode mode, const PointData& vertexs, const ColorData& colors, const PointData& texcoords) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_DOUBLE, 0, vertexs.data());
		glColorPointer(4, GL_DOUBLE, 0, colors.data());
		glTexCoordPointer(2, GL_DOUBLE, 0, texcoords.data());
		glDrawArrays(mode, 0, vertexs.size() / 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

}
