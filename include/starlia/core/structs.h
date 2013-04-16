#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <iostream>

namespace Starlia
{

using namespace std;

template <typename T>
struct Coord3;

template <typename T>
struct Coord2
{
	T x,y;
	Coord2<T>() {};
	Coord2<T>(T x, T y) : x(x), y(y) {};

	Coord2<T> operator+(const Coord2<T>& second) { return Coord2<T>(x + second.x, y + second.y); }
	Coord2<T> operator-(const Coord2<T>& second) { return Coord2<T>(x - second.x, y - second.y); }
	Coord2<T> operator*(T second) { return Coord2<T>(x * second, y * second); }
	Coord2<T> operator/(T second) { return Coord2<T>(x / second, y / second); }

	Coord2<T> operator+=(Coord2<T> second) { x += second.x; y += second.y; return *this; }
	Coord2<T> operator-=(Coord2<T> second) { x -= second.x; y -= second.y; return *this; }
	Coord2<T> operator*=(T second) { x *= second; y *= second; return *this; }
	Coord2<T> operator/=(T second) { x /= second; y /= second; return *this; }

	template<typename T2>
	Coord2<T>(Coord2<T2> second) { x = second.x; y = second.y; }

	template<typename T2>
	Coord2<T>(Coord3<T2> second) { x = second.x; y = second.y; }
};

template <typename T>
inline istream& operator >> (istream& is, Coord2<T>& coord)
{
	return is >> coord.x >> coord.y;
}

template <typename T>
inline ostream& operator << (ostream& os, const Coord2<T>& coord)
{
	return os << "(" << coord.x << ", " << coord.y << ")";
}

typedef Coord2<int> Coord2i;
typedef Coord2<float> Coord2f;
typedef Coord2<double> Coord2d;


template <typename T>
struct Coord3
{
	T x,y,z;
	Coord3<T>() {};
	Coord3<T>(T x, T y, T z) : x(x), y(y), z(z) {};

	Coord3<T> operator+(const Coord3<T>& second) { return Coord3<T>(x + second.x, y + second.y, z + second.z); }
	Coord3<T> operator-(const Coord3<T>& second) { return Coord3<T>(x - second.x, y - second.y, z - second.z); }
	Coord3<T> operator*(T second) { return Coord3<T>(x * second, y * second, z * second); }
	Coord3<T> operator/(T second) { return Coord3<T>(x / second, y / second, z / second); }

	Coord3<T> operator+=(Coord3<T> second) { x += second.x; y += second.y; z += second.z; return *this; }
	Coord3<T> operator-=(Coord3<T> second) { x -= second.x; y -= second.y; z -= second.z; return *this; }
	Coord3<T> operator*=(T second) { x *= second; y *= second; z *= second; return *this; }
	Coord3<T> operator/=(T second) { x /= second; y /= second; z /= second; return *this; }

	template <typename T2>
	Coord3<T>(Coord3<T2> second) { x = second.x; y = second.y; z = second.z; }

	template<typename T2>
	Coord3<T>(Coord2<T2> second) { x = second.x; y = second.y; z = 0; }
};

template <typename T>
inline istream& operator >> (istream& is, Coord3<T>& coord)
{
	return is >> coord.x >> coord.y >> coord.z;
}

template <typename T>
inline ostream& operator << (ostream& os, const Coord3<T>& coord)
{
	return os << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
}

typedef Coord3<int> Coord3i;
typedef Coord3<float> Coord3f;
typedef Coord3<double> Coord3d;


struct Color3f
{
	float r,g,b;
	Color3f() {};
	Color3f(float r, float g, float b) : r(r), g(g), b(b) {};
};

inline istream& operator >> (istream& is, Color3f& color)
{
	return is >> color.r >> color.g >> color.b;
}

inline ostream& operator << (ostream& os, const Color3f& color)
{
	return os << "(" << color.r << ", " << color.g << ", " << color.b << ")";
}


struct Color4f
{
	float r,g,b,a;
	Color4f() {};
	Color4f(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};
};

inline istream& operator >> (istream& is, Color4f& color)
{
	return is >> color.r >> color.g >> color.b >> color.a;
}

inline ostream& operator << (ostream& os, const Color4f& color)
{
	return os << "(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
}


struct Polar2f
{
	float r, a;
	Polar2f() {};
	Polar2f(float r, float a) : r(r), a(a) {};
};

}

#endif
