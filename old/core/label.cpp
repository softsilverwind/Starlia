#include <functional>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <GL/gl.h>
#include "structs.h"
#include "label.h"
#include "basicRender.h"

using namespace std;

namespace Starlia
{

void StarLabel::breakText(const string& text)
{
	int i;
	int currLinePos = 0;
	int lastSpace = 0;

	while (text.length() - currLinePos > charsPerLine)
	{
		for(i = currLinePos + charsPerLine; !isblank(text[i]); --i)
			;

		lastSpace = i;
		while(isblank(text[--i]))
			;
		
		textArray.push_back(text.substr(currLinePos, i + 1 - currLinePos));

		currLinePos = lastSpace + 1;
	}

	textArray.push_back(text.substr(currLinePos, text.length() - currLinePos));

	for(unsigned int i = 0; i < textArray.size(); ++i)
		justifyOffset.push_back(justify * ((botRight.x - topLeft.x) - (textArray[i].size() * charWidth * 1.5 - charWidth * 0.5)) / charWidth);

	linesPrinted = min((unsigned int) maxlineD, (unsigned int) textArray.size());
}

StarLabel::StarLabel(string text, Coord2d topLeft, Coord2d botRight, double charHeight, Color3f color, Justify justify, function<void (Coord2d)> onClick)
	: StarWidget(topLeft, botRight, onClick), charHeight(charHeight), color(color), justify(justify)
{
	charWidth = 0.5 * charHeight;
	charsPerLineD = (botRight.x - topLeft.x + 0.5 * charWidth) / (1.5 * charWidth); 

	// adding a dummy space at the end of the line. It won't be displayed either way
	// Each space between two characters is one half the width of a character.
	charsPerLine = (unsigned int) charsPerLineD;

	// Adding a dummy space at the bottom end of the label.
	// Each space between two lines is one half the height of a character.
	maxlineD = (topLeft.y - botRight.y + 0.5 * charHeight) / (1.5 * charHeight);

	breakText(text);

	
}

void StarLabel::draw()
{
#ifdef __DEBUG__
	glColor3f(0,0.2,0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(topLeft.x, topLeft.y);
	glVertex2d(topLeft.x, botRight.y);
	glVertex2d(botRight.x, botRight.y);
	glVertex2d(botRight.x, topLeft.y);
	glEnd();
#endif

	glColor3f(color.r, color.g, color.b);
	glTranslated(topLeft.x,topLeft.y,0);
	glScaled(charWidth / 2, charHeight / 2, 0);
	glTranslated(1, -1, 0);
	glColor3f(color.r, color.g, color.b);
	for (unsigned int i = 0; i < linesPrinted; ++i)
	{
		glPushMatrix();
		string& text = textArray[i];

		glTranslated(justifyOffset[i], 0, 0);

		for (string::iterator it = text.begin(); it != text.end(); ++it)
		{
			VectorLetter::writeCharacter(toupper(*it));
			glTranslated(3,0,0);
		}
		
		glPopMatrix();
		glTranslated(0, -3, 0);
	}

	glPopMatrix();
}

void StarLabel::update()
{
}

void StarLabel::chText(const string& text)
{
	textArray.clear();
	justifyOffset.clear();
	breakText(text);
}

void StarLabel::speakYourMind()
{
	for(vector<string>::iterator it = textArray.begin(); it != textArray.end(); ++it)
		cerr << *it << "$" << endl;
}

}