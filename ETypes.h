#ifndef _E_TYPES_H_
#define _E_TYPES_H_

namespace Eg {

	template <typename T>
	struct EPointT {
		T x, y;
		EPointT(const T& xx, const T& yy) : x(xx), y(yy) {}
		EPointT() : EPointT(T(0), T(0)) {}
	};

	typedef EPointT<int> EPointi;
	typedef EPointT<double> EPointf;

	struct EColor {
		double red, green, blue, alpha;
		EColor(double r, double g, double b, double a = 1.0) : red(r), green(g), blue(b), alpha(a) {}
		EColor() : EColor(0, 0, 0) {}
	};

}

#endif