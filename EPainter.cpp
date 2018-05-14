#include "global.h"
#include "EPainter.h"

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
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_DOUBLE, 0, vertexs.data());
		glTexCoordPointer(2, GL_DOUBLE, 0, texcoords.data());
		glDrawArrays(mode, 0, vertexs.size() / 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
