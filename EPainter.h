#ifndef _E_PAINTER_H_
#define _E_PAINTER_H_

#include "EWindow.h"
#include "ETypes.h"

#include <vector>
#include <initializer_list>

namespace Eg {
	
	class EPainter {
		
	public:
		enum DrawMode {
			Points,
			Lines,
			LineLoop,
			LineStrip,
			Triangles,
			TriangleStrip,
			TriangleFan,
			Quads,
			QuadStrip,
			Polygon
		};
		struct PointData : public std::vector<double> {
			using std::vector<double>::vector;
			PointData(const std::initializer_list<EPointf> &pts) {
				for (const auto& p : pts) {
					push_back(p.x);
					push_back(p.y);
				}
			}
			void add(const EPointf& pt) {
				push_back(pt.x);
				push_back(pt.y);
			}
			void sub() {
				pop_back();
				pop_back();
			}
		};
		struct ColorData : public std::vector<double> {
			using std::vector<double>::vector;
			ColorData(const std::initializer_list<EColor> &cls) {
				for (const auto& c : cls) {
					push_back(c.red);
					push_back(c.green);
					push_back(c.blue);
					push_back(c.alpha);
				}
			}
			void add(const EColor& c) {
				push_back(c.red);
				push_back(c.green);
				push_back(c.blue);
				push_back(c.alpha);
			}
			void sub() {
				pop_back();
				pop_back();
				pop_back();
				pop_back();
			}
		};
		EPainter();
		void draw(DrawMode mode, const PointData& vertexs, const ColorData& colors);
		void draw(DrawMode mode, const PointData& vertexs, const PointData& texcoords);
		void draw(DrawMode mode, const PointData& vertexs, const ColorData& colors, const PointData& texcoords);
	};
	
}

#endif
