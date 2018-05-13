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

	enum EGlobalColor {
		WHITE,
		BLACK,
		RED,
		DARKRED,
		GREEN,
		DARKGREEN,
		BLUE,
		DARKBLUE,
		CYAN,
		DARKCYAN,
		MAGENTA,
		DARKMAGENTA,
		YELLOW,
		DARKYELLOW,
		GRAY,
		DARKGRAY,
		LIGHTGRAY,
		TRANSPARENT,
		NUMBER_OF_GLOBAL_COLORS
	};

	struct EColor {
		double red, green, blue, alpha;
		EColor(double r, double g, double b, double a = 1.0) : red(r), green(g), blue(b), alpha(a) {}
		EColor(int r, int g, int b, int a = 255) : EColor(r / 255.0, g / 255.0, b / 255.0, a / 255.0) {}
		EColor() : EColor(0, 0, 0) {}
		EColor(EGlobalColor g);
		void set() const; // glColor4d
	};

}

#endif
