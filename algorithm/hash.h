#ifndef __HASH_H__
#define __HASH_H__

#include <map>
#include "exception.h"
#include "matrix.h"
#include "../structs.h"

using namespace std;

namespace Starlia
{

template <typename T1, typename T2>
class Hash
{
	private:
		map<T1, T2> hash;

	public:
		Hash();
		T2& find(const T1& key)
		{
			hash<T1, T2>::iterator it = hash.find(key);
			if (it == hash.end())
				throw Nonexistent();
		}

		void insert(const T1& key, const T2& value)
		{
			hash[key] = value;
		}
};

template <typename T>
class Hash<Coordinate2i, T>
{
	private:
		typedef struct
		{
			bool valid;
			T value;	
		}
		ElemType;
		Matrix<ElemType> hash;

	public:
		Hash(Coordinate2i size)
			hash(size)
		{
			hash.initzero();
		}

		T& find(Coordinate2i pos)
		{
			ElemType& elem = hash(pos);

			if (elem.valid)
				return elem.value;
			else
				throw Nonexistent;
		}

		void insert(Coordinate2i pos, const T& value)
		{
			ElemType& elem = hash(pos);
			elem.valid = true;
			elem.value = value;
		}
};

template <typename T>
class Hash<int, T>
{
	private:
		int size;
		T hash;

	public:
		Hash(int size)
			size(size)
		{
			hash = new int[size];
		}

		~Hash()
		{
			delete [] hash;
		}

		T& find(int pos)
		{
			if (pos >= 0 && pos < size)
				return hash[pos];
			else
				throw Out_of_bounds();
				
		}

		void insert(int pos, const T& value)
		{
			if (pos >= 0 && pos < size)
				hash[pos] = value;
			else
				throw Out_of_bounds;
		}
};

}

#endif /* __HASH_H__ */
