#ifndef __LABEL_H__
#define __LABEL_H__

#include <functional>
#include <string>
#include <vector>
#include <list>
#include "structs.h"
#include "object.h"

using namespace std;

namespace Starlia
{

class StarLabel : public StarWidget
{
	public:
		typedef enum
		{
			LEFT = 0, CENTER = 1, RIGHT = 2
		}
		Justify;

	private:
		vector<string> textArray;
		vector<double> justifyOffset;

		double charHeight;
		double charWidth;
		Color3f color;
		unsigned int charsPerLine;
		double charsPerLineD;
		unsigned int linesPrinted;
		double maxlineD;
		Justify justify;

		void breakText(const string&);

	public:

		StarLabel(string text, Coord2d topLeft, Coord2d botRight, double charHeight, Color3f, Justify justify = LEFT, function<void (Coord2d)> onClick = NULL);

		void chText(const string& newText);

		void draw();
		void update();
		void speakYourMind();
};

}

#endif /* __LABEL_H__ */
