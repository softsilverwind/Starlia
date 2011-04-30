#ifndef __STRUCTS_H__
#define __STRUCTS_H__

namespace Starlia
{

typedef struct Coordinate2d
{
	double x,y;
	Coordinate2d() {};
	Coordinate2d(double x, double y) : x(x), y(y) {};

	Coordinate2d operator+(Coordinate2d second) { return Coordinate2d(x + second.x, y + second.y); }
	Coordinate2d operator-(Coordinate2d second) { return Coordinate2d(x - second.x, y - second.y); }
	Coordinate2d operator/(int second) { return Coordinate2d(x / second, y / second); }

	Coordinate2d operator+=(Coordinate2d second) { return Coordinate2d(x += second.x, y += second.y); }
	Coordinate2d operator-=(Coordinate2d second) { return Coordinate2d(x -= second.x, y -= second.y); }
	Coordinate2d operator*=(Coordinate2d second) { return Coordinate2d(x *= second.x, y *= second.y); }
}
Coordinate2d;

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
}
Coordinate3d;

typedef struct Color3d
{
	double r,g,b;
	Color3d() {};
	Color3d(double r, double g, double b) : r(r), g(g), b(b) {};
}
Color3d;

}

#endif /* __STRUCTS_H__ */
