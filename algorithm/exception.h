#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>

using namespace std;

class Out_of_bounds : public exception
{
};

class Nonexistent : public exception
{
};

#endif /* __EXCEPTION_H__ */
