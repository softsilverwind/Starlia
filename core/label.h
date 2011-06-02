#ifndef __LABEL_H__
#define __LABEL_H__

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
		Color3d color;
		unsigned int charsPerLine;
		double charsPerLineD;
		unsigned int linesPrinted;
		double maxlineD;
		Justify justify;

		void breakText(const string&);

	public:

		StarLabel(string text, Coordinate2d topLeft, Coordinate2d botRight, double charHeight, Color3d, Justify justify = LEFT, void (*onClick)(Coordinate2d) = NULL);

		void chText(const string& newText);

		void draw();
		bool recalc();
		void speakYourMind();
};

}

#endif /* __LABEL_H__ */
