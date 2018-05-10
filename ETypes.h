#ifndef _E_TYPES_H_
#define _E_TYPES_H_

namespace Eg {

	template <typename T>
	struct EPointT {
		T x, y;
		EPointT(const T& xx, const T& yy) : x(xx), y(yy) {}
		EPointT() : EPointT(T(0), T(0)) {}
		EPointT& operator+=(const EPointT& p) {
			x += p.x;
			y += p.y;
			return *this;
		}
		EPointT& operator-=(const EPointT& p) {
			x -= p.x;
			y -= p.y;
			return *this;
		}
	};

	typedef EPointT<int> EPointi;
	typedef EPointT<double> EPointf;

	template <typename T>
	struct ERectT {
		T left, up, right, down;
		ERectT(const T& l, const T& u, const T& r, const T& d) : left(l), up(u), right(r), down(d) {}
		ERectT(const EPointT<T>& lu, const EPointT<T>& rd) : left(lu.x), up(lu.y), right(rd.x), down(rd.y) {}
		ERectT() : ERectT(0, 0, 0, 0) {}
	};

	typedef ERectT<int> ERecti;
	typedef ERectT<double> ERectf;

	struct EColor {
		double red, green, blue, alpha;
		EColor(double r, double g, double b, double a = 1.0) : red(r), green(g), blue(b), alpha(a) {}
		EColor() : EColor(0, 0, 0) {}
	};

}

#endif
