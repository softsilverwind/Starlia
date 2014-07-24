#include <iostream>
#include <string>

#include <GL/glew.h>

#include <core/layer.h>

using namespace std;

namespace Starlia
{

bool SLayer::eventKeyPress(SDLKey c)
{
	auto it = keypresses.find(c);

	if (it != keypresses.end())
	{
		(it->second)();
		return true;
	}

	return block & Block_Keyboard;
}

bool SLayer::eventKeyRelease(SDLKey c)
{
	auto it = keyreleases.find(c);

	if (it != keyreleases.end())
	{
		(it->second)();
		return true;
	}

	return block & Block_Keyboard;
}


SLayer::SLayer()
	: invalid(false), block(0)
{}

void SLayer::setWorld(const mat4& w)
{
	world = w;
	wvp = projection * view * world;
}

void SLayer::setView(const mat4& v)
{
	view = v;
	wvp = projection * view * world;
}

void SLayer::setProjection(const mat4& p)
{
	projection = p;
	wvp = projection * view * world;
}

const mat4& SLayer::getWVP()
{
	return wvp;
}

int SLayer::getAttrib(const string& name)
{
	int ret = glGetAttribLocation(getActiveProgram(), name.c_str());
	return ret;
}

int SLayer::getUniform(const string& name)
{
	int ret = glGetUniformLocation(getActiveProgram(), name.c_str());
	return ret;
}

}
