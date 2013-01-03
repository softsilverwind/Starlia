#include <string>

#include <GL/glew.h>

#include <core/layer.h>

using namespace std;

namespace Starlia
{

void SLayer::draw()
{
	glUseProgram(program);
}

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
	wvp = world * view * projection;
}

void SLayer::setView(const mat4& v)
{
	view = v;
	wvp = world * view * projection;
}

void SLayer::setProjection(const mat4& p)
{
	projection = p;
	wvp = world * view * projection;
}

int SLayer::getAttrib(const string& attrib)
{
	return glGetAttribLocation(program, attrib.c_str());
}

}
