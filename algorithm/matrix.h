#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <starlia.h>

namespace Starlia
{

template <class T>
class Matrix
{
	private:
		Coordinate2i size;
		T *contents;
		T dummy;
		
		int loc(int x, int y)
		{
			return x * size.y + y;
		}

	public:
		Matrix(Coordinate2i size)
			: size(size)
		{
			contents = new T[size.x * size.y];
		}

		Matrix(istream& is)
		{
			is >> size;
			contents = new T[size.x * size.y];
			is >> *this;
		}

		Matrix(Coordinate2i size, T init_val)
			: size(size)
		{
			contents = new T[size.x * size.y];
			for (int i = 0; i < size.x; ++i)
				for (int j = 0; j < size.y; ++j)
					getVal(i,j) = init_val;
		}

		~Matrix()
		{
			delete [] contents;
		}

		T& getVal(int x, int y, bool getDummy = false)
		{
			if (x >= 0 && x < size.x && y >= 0 && y < size.y)
				return contents[loc(x,y)];
			else
				if (getDummy)
				{
					dummy = T();
					return dummy;
				}
				else
					throw "Out of bounds";
		}

		T& getVal(Coordinate2i pos, bool getDummy = false)
		{
			return getVal(pos.x, pos.y, getDummy);
		}

		Coordinate2i getSize()
		{
			return size;
		}

		void initialize(T t)
		{
			for (int i = 0; i < size.x; ++i)
				for (int j = 0; j < size.y; ++j)
					getVal(i,j) = t;
		}


	friend istream& operator >> (istream& is, Matrix<T>& mat)
	{
		for (int j = 0; j < mat.size.y; ++j)
			for (int i = 0; i < mat.size.x; ++i)
				is >> mat.getVal(i,j);

		return is;
	}

	friend ostream& operator << (ostream& os, Matrix<T>& mat)
	{
		for (int j = 0; j < mat.size.y; ++j)
		{
			for (int i = 0; i < mat.size.x; ++i)
				os << mat.getVal(i,j);
			os << endl;
		}

		return os;
	}
};

}

#endif /* __MATRIX_H__ */
