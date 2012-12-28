#include <iostream>

#include <starlia/core/structs.h>

using namespace Starlia;
using namespace std;

int main()
{
	{
		cout << "2d conversions" << endl;

		Coord2d d(4.2142124412, 6.21948719);
		Coord2f f = d;
		Coord2i i = d;

		cout << d << endl << f << endl << i << endl;
	}

	{
		cout << "3d conversions" << endl;

		Coord3d d(4.2142124412, 6.21948719, 4.12098);
		Coord3f f = d;
		Coord3i i = d;

		cout << d << endl << f << endl << i << endl;
	}

	{
		cout << "2d -> 3d" << endl;

		Coord2d d(4.2142124412, 6.21948719);
		Coord3i i = d;

		cout << d << endl << i << endl;
	}

	{
		cout << "3d -> 2d" << endl;

		Coord3d d(4.2142124412, 6.21948719, 4.12098);
		Coord2i i = d;

		cout << d << endl << i << endl;
	}

	return 0;
}
