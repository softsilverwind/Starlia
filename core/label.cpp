#include <iostream>
#include <cstdio>
#include <cctype>
#include <GL/glut.h>
#include "structs.h"
#include "label.h"
#include "basicRender.h"

// This code equals a googolplex of WTFs/second! Abandon all hope ye who enter here!
// This code is so shit it has grown sentient life in it...

#define sensible_duration($1) (($1) * 10 + 120)

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
}

StarLabel::StarLabel(string text, Coordinate2d topLeft, Coordinate2d botRight, double charHeight, Color3d color, int duration, EngineMode mode, Justify justify, void (*onClick)())
	: StarWidget(topLeft, botRight, onClick), charHeight(charHeight), color(color), duration(duration), mode(mode), justify(justify)
{
	timeAlive = 0;

	charWidth = 0.5 * charHeight;
	charsPerLineD = (botRight.x - topLeft.x + 0.5 * charWidth) / (1.5 * charWidth); 
	// adding a dummy space at the end of the line. It won't be displayed either way
	// Each space between two characters is one half the width of a character.

	charsPerLine = (unsigned int) charsPerLineD;

	if (!duration)
		this->duration = sensible_duration(text.length());

	breakText(text);

	maxlineD = (topLeft.y - botRight.y + 0.5 * charHeight) / (1.5 * charHeight);
	// Adding a dummy space at the bottom end of the label.
	// Each space between two lines is one half the height of a character.
	
	linesPrinted = min((unsigned int) maxlineD, (unsigned int) textArray.size());
}

void StarLabel::draw()
{
	int count = 0;
	double color_factor;

#ifdef __DEBUG__
	glColor3d(0,0.2,0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(topLeft.x, topLeft.y);
	glVertex2d(topLeft.x, botRight.y);
	glVertex2d(botRight.x, botRight.y);
	glVertex2d(botRight.x, topLeft.y);
	glEnd();
#endif

	/*
	switch (mode)
	{
		case PSYCHIC:
			color_factor = timeAlive / 100.0;
			break;

		case DOUBLE_PSYCHIC:
			color_factor = min(timeAlive / 100.0, (duration - timeAlive) / 100.0);
			break;

		case END_PSYCHIC:
			color_factor = (duration - timeAlive) / 100.0;
			break;

		default:
			color_factor = 1;
			break;
	}

	if (color_factor > 1)
		color_factor = 1;

	glColor3d(color.r * color_factor, color.g * color_factor, color.b * color_factor);
	*/

	glColor3d(color.r, color.g, color.b);
	glTranslated(topLeft.x,topLeft.y,0);
	glScaled(charWidth / 2, charHeight / 2, 0);
	glTranslated(1, -1, 0);
	glColor3d(color.r, color.g, color.b);
	for (unsigned int i = 0; i < linesPrinted; ++i)
	{
		glPushMatrix();
		string& text = textArray[i];

		glTranslated(justifyOffset[i], 0, 0);

		for (string::iterator it = text.begin(); it != text.end(); ++it, ++count)
		{
			VectorLetter::writeCharacter(toupper(*it));
			glTranslated(3,0,0);
		}
		
		glPopMatrix();
		glTranslated(0, -3, 0);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

bool StarLabel::recalc()
{
	if (duration < 0)
		return true;

	return ++timeAlive <= duration;
}

void StarLabel::chText(const string& text, int newDuration, EngineMode newMode)
{
	timeAlive = 0;

	if (!duration)
		duration = sensible_duration(text.length());
	else
		duration = newDuration;

	textArray.clear();
	justifyOffset.clear();
	breakText(text);
}

void StarLabel::chText(const string& newText, int newDuration, Color3d newColor, EngineMode newMode)
{
	chText(newText, newDuration);
	color = newColor;
	mode = newMode;
}

void StarLabel::speakYourMind()
{
	for(vector<string>::iterator it = textArray.begin(); it != textArray.end(); ++it)
		cerr << *it << "$" << endl;
}

}
