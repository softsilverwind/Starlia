#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <iostream>
using namespace std;

namespace Starlia
{

typedef struct Coord2i
{
	int x,y;
	Coord2i() {};
	Coord2i(int x, int y) : x(x), y(y) {};

	Coord2i operator+(const Coord2i& second) { return Coord2i(x + second.x, y + second.y); }
	Coord2i operator-(const Coord2i& second) { return Coord2i(x - second.x, y - second.y); }
	Coord2i operator/(int second) { return Coord2i(x / second, y / second); }
	Coord2i operator*(int second) { return Coord2i(x * second, y * second); }
	Coord2i operator/(const Coord2i& second) { return Coord2i(x / second.x, y / second.y); }

	Coord2i operator+=(Coord2i second) { return Coord2i(x += second.x, y += second.y); }
	Coord2i operator-=(Coord2i second) { return Coord2i(x -= second.x, y -= second.y); }
	Coord2i operator*=(Coord2i second) { return Coord2i(x *= second.x, y *= second.y); }
}
Coord2i;

inline istream& operator >> (istream& is, Coord2i& coord)
{
	return is >> coord.x >> coord.y;
}

inline ostream& operator << (ostream& os, const Coord2i& coord)
{
	return os << "(" << coord.x << ", " << coord.y << ")";
}

typedef struct Coord2d
{
	double x,y;
	Coord2d() {};
	Coord2d(double x, double y) : x(x), y(y) {};

	Coord2d operator+(const Coord2d& second) { return Coord2d(x + second.x, y + second.y); }
	Coord2d operator-(const Coord2d& second) { return Coord2d(x - second.x, y - second.y); }
	Coord2d operator/(int second) { return Coord2d(x / second, y / second); }
	Coord2d operator*(int second) { return Coord2d(x * second, y * second); }
	Coord2d operator/(const Coord2d& second) { return Coord2d(x / second.x, y / second.y); }

	Coord2d operator+=(Coord2d second) { return Coord2d(x += second.x, y += second.y); }
	Coord2d operator-=(Coord2d second) { return Coord2d(x -= second.x, y -= second.y); }
	Coord2d operator*=(Coord2d second) { return Coord2d(x *= second.x, y *= second.y); }
	Coord2d operator*=(int second) { return Coord2d(x *= second, y *= second); }
}
Coord2d;

inline istream& operator >> (istream& is, Coord2d& coord)
{
	return is >> coord.x >> coord.y;
}

inline ostream& operator << (ostream& os, const Coord2d& coord)
{
	return os << "(" << coord.x << ", " << coord.y << ")";
}

typedef struct Polar2d
{
	double r,a;
	Polar2d() {};
	Polar2d(double r, double a) : r(r), a(a) {};
}
Polar2d;

typedef struct Coord3d
{
	double x,y,z;
	Coord3d() {};
	Coord3d(double x, double y, double z) : x(x), y(y), z(z) {};

	Coord3d operator+(const Coord3d& second) { return Coord3d(x + second.x, y + second.y, z + second.z); }
	Coord3d operator-(const Coord3d& second) { return Coord3d(x - second.x, y - second.y, z - second.z); }
	Coord3d operator/(double second) { return Coord3d(x / second, y / second, z / second); }
	Coord3d operator*(double second) { return Coord3d(x * second, y * second, z * second); }
	Coord3d operator/(const Coord3d& second) { return Coord3d(x / second.x, y / second.y, z / second.z); }

	Coord3d operator+=(Coord3d second) { return Coord3d(x += second.x, y += second.y, z += second.z); }
	Coord3d operator-=(Coord3d second) { return Coord3d(x -= second.x, y -= second.y, z -= second.z); }
	Coord3d operator*=(Coord3d second) { return Coord3d(x *= second.x, y *= second.y, z *= second.z); }
	Coord3d operator*=(double second) { return Coord3d(x *= second, y *= second, z *= second); }
}
Coord3d;

inline istream& operator >> (istream& is, Coord3d& coord)
{
	return is >> coord.x >> coord.y >> coord.z;
}

inline ostream& operator << (ostream& os, const Coord3d& coord)
{
	return os << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
}

typedef struct Color3f
{
	float r,g,b;
	Color3f() {};
	Color3f(float r, float g, float b) : r(r), g(g), b(b) {};
}
Color3f;

}

#endif /* __STRUCTS_H__ */
