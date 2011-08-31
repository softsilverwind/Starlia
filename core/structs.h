#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <iostream>
using namespace std;

namespace Starlia
{

typedef struct Coordinate2i
{
	int x,y;
	Coordinate2i() {};
	Coordinate2i(int x, int y) : x(x), y(y) {};

	Coordinate2i operator+(const Coordinate2i& second) { return Coordinate2i(x + second.x, y + second.y); }
	Coordinate2i operator-(const Coordinate2i& second) { return Coordinate2i(x - second.x, y - second.y); }
	Coordinate2i operator/(int second) { return Coordinate2i(x / second, y / second); }
	Coordinate2i operator*(int second) { return Coordinate2i(x * second, y * second); }
	Coordinate2i operator/(const Coordinate2i& second) { return Coordinate2i(x / second.x, y / second.y); }

	Coordinate2i operator+=(Coordinate2i second) { return Coordinate2i(x += second.x, y += second.y); }
	Coordinate2i operator-=(Coordinate2i second) { return Coordinate2i(x -= second.x, y -= second.y); }
	Coordinate2i operator*=(Coordinate2i second) { return Coordinate2i(x *= second.x, y *= second.y); }
}
Coordinate2i;

inline istream& operator >> (istream& is, Coordinate2i& coord)
{
	return is >> coord.x >> coord.y;
}

inline ostream& operator << (ostream& os, const Coordinate2i& coord)
{
	return os << "(" << coord.x << ", " << coord.y << ")";
}

typedef struct Coordinate2d
{
	double x,y;
	Coordinate2d() {};
	Coordinate2d(double x, double y) : x(x), y(y) {};

	Coordinate2d operator+(const Coordinate2d& second) { return Coordinate2d(x + second.x, y + second.y); }
	Coordinate2d operator-(const Coordinate2d& second) { return Coordinate2d(x - second.x, y - second.y); }
	Coordinate2d operator/(int second) { return Coordinate2d(x / second, y / second); }
	Coordinate2d operator*(int second) { return Coordinate2d(x * second, y * second); }
	Coordinate2d operator/(const Coordinate2d& second) { return Coordinate2d(x / second.x, y / second.y); }

	Coordinate2d operator+=(Coordinate2d second) { return Coordinate2d(x += second.x, y += second.y); }
	Coordinate2d operator-=(Coordinate2d second) { return Coordinate2d(x -= second.x, y -= second.y); }
	Coordinate2d operator*=(Coordinate2d second) { return Coordinate2d(x *= second.x, y *= second.y); }
	Coordinate2d operator*=(int second) { return Coordinate2d(x *= second, y *= second); }
}
Coordinate2d;

inline istream& operator >> (istream& is, Coordinate2d& coord)
{
	return is >> coord.x >> coord.y;
}

inline ostream& operator << (ostream& os, const Coordinate2d& coord)
{
	return os << "(" << coord.x << ", " << coord.y << ")";
}

typedef struct Coordinate2dpolar
{
	double r,a;
	Coordinate2dpolar() {};
	Coordinate2dpolar(double r, double a) : r(r), a(a) {};
}
Coordinate2dpolar;

typedef struct Coordinate3d
{
	double x,y,z;
	Coordinate3d() {};
	Coordinate3d(double x, double y, double z) : x(x), y(y), z(z) {};

	Coordinate3d operator+(const Coordinate3d& second) { return Coordinate3d(x + second.x, y + second.y, z + second.z); }
	Coordinate3d operator-(const Coordinate3d& second) { return Coordinate3d(x - second.x, y - second.y, z - second.z); }
	Coordinate3d operator/(double second) { return Coordinate3d(x / second, y / second, z / second); }
	Coordinate3d operator*(double second) { return Coordinate3d(x * second, y * second, z * second); }
	Coordinate3d operator/(const Coordinate3d& second) { return Coordinate3d(x / second.x, y / second.y, z / second.z); }

	Coordinate3d operator+=(Coordinate3d second) { return Coordinate3d(x += second.x, y += second.y, z += second.z); }
	Coordinate3d operator-=(Coordinate3d second) { return Coordinate3d(x -= second.x, y -= second.y, z -= second.z); }
	Coordinate3d operator*=(Coordinate3d second) { return Coordinate3d(x *= second.x, y *= second.y, z *= second.z); }
	Coordinate3d operator*=(double second) { return Coordinate3d(x *= second, y *= second, z *= second); }
}
Coordinate3d;

inline istream& operator >> (istream& is, Coordinate3d& coord)
{
	return is >> coord.x >> coord.y >> coord.z;
}

inline ostream& operator << (ostream& os, const Coordinate3d& coord)
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
