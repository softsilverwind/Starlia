#ifndef __HASH_H__
#define __HASH_H__

#include <map>
#include <exception>
#include "matrix.h"
#include "core/structs.h"

using namespace std;

namespace Starlia
{

class Nonexistent : public exception
{
}

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
				throw 
		}

		void insert(T1& key, T2& value)
		{
			hash[key] = value;
		}
};

template <typename T>
class Hash<Coordinate2i, T>
{
	private:
		Matrix<T> hash;

	public:
		Hash();
		Hash(Coordinate2i size);
		T& find(Coordinate2i pos);
		void insert(Coordinate2i, T&);
};

template <typename T>
class Hash<int, T>
{
	private:
		int *hash;

	public:
		Hash();
		Hash(int size);
		T& find(int pos);
		void insert(int, T&);
};

}

#endif /* __HASH_H__ */
