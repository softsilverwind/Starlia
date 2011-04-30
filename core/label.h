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
			STATIC, WRITE, PSYCHIC, DOUBLE_PSYCHIC, END_PSYCHIC
		}
		EngineMode;

		typedef enum
		{
			LEFT = 0, CENTER = 1, RIGHT = 2
		}
		Justify;

	private:
		vector<string> textArray;
		vector<double> justifyOffset;

		int timeAlive;
		double charHeight;
		double charWidth;
		Color3d color;
		double duration;
		unsigned int charsPerLine;
		double charsPerLineD;
		unsigned int linesPrinted;
		double maxlineD;
		EngineMode mode;
		Justify justify;

		void breakText(const string&);

	public:
		static void initialize();
		static void writeCharacter(unsigned char c);

		StarLabel(string text, Coordinate2d topLeft, Coordinate2d botRight, double charHeight, Color3d, int duration = 0, EngineMode = STATIC, Justify justify = LEFT, void (*onClick)() = NULL);

		void chText(const string& newText, int newDuration = 0, EngineMode newMode = STATIC);
		void chText(const string& newText, int newDuration, Color3d newColor, EngineMode newMode = STATIC);

		void draw();
		bool recalc();
		void speakYourMind();
};

}

#endif /* __LABEL_H__ */
