#include <iostream>
#include <cstdio>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/core.h>
#include <core/basic.h>

#include "shaders/shaders.h"

namespace Starlia
{

using namespace std;
using namespace glm;

SClearColorLayer::SClearColorLayer(Color3f color)
	: color(color)
{
}

void SClearColorLayer::draw()
{
	glClearColor(color.r, color.g, color.b, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

SClearDepthLayer::SClearDepthLayer()
{
}

void SClearDepthLayer::draw()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

SStaticShaderLayer::SStaticShaderLayer(shared_ptr<SCamera> camera, const string& v_shader, const string& f_shader)
	: camera(camera)
{
	const char *v_s = v_shader.c_str();
	const char *f_s = f_shader.c_str();

	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &v_s, NULL);
	glCompileShader(vs);

	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &f_s, NULL);
	glCompileShader(fs);

	linked_program = glCreateProgram();
	glAttachShader(linked_program, vs);
	glAttachShader(linked_program, fs);
	glLinkProgram(linked_program);

	int link_ok = 0;
	glGetProgramiv(linked_program, GL_LINK_STATUS, &link_ok);

	if (!link_ok)
	{
		cerr << "SStaticShaderLayer failed to link shader" << endl;
		cerr << "Vertex Shader:" << endl;
		cerr << v_s << endl;
		cerr << "Fragment Shader:" << endl;
		cerr << f_s << endl;

		cerr << "Link Errors:" << endl;
		StarCore::printShaderErrors(linked_program);
		cerr << "Vertex Shader Errors:" << endl;
		StarCore::printShaderErrors(vs);
		cerr << "Fragment Shader Errors:" << endl;
		StarCore::printShaderErrors(fs);
		cerr << "End of error message" << endl;
	}

	shared_ptr<SObject> obj;
	if (obj = dynamic_pointer_cast<SObject>(camera))
		add(obj);
}

SStaticShaderLayer::SStaticShaderLayer(SCamera *camera, const string& v_shader, const string& f_shader)
	: SStaticShaderLayer(shared_ptr<SCamera>(camera), v_shader, f_shader)
{
}

void SStaticShaderLayer::draw()
{
	glUseProgram(linked_program);

	setProjection(camera->getProjection());
	setView(camera->getView());

	SListLayer<SObject>::draw();
}

shared_ptr<SCamera> SStaticShaderLayer::getCamera()
{
	return camera;
}

unsigned int SStaticShaderLayer::getActiveProgram()
{
	return linked_program;
}

const string SBasicColorLayer::v_shader(shaders_basiccolor_v);
const string SBasicColorLayer::f_shader(shaders_basiccolor_f);
const string SBasicObjectLayer::v_shader(shaders_basicobject_v);
const string SBasicObjectLayer::f_shader(shaders_basicobject_f);

bool SCircle::initialized = false;
vector<Coord2f> SCircle::vertices;

void SCircle::initialize()
{
	initialized = true;

	vertices.resize(POINTS);
	for (int i = 0; i < POINTS / 8; i++)
	{
		vertices[i].x = cos(i * step);
		vertices[i].y = sin(i * step);

		vertices[POINTS/4 - i - 1].x = vertices[i].y;
		vertices[POINTS/4 - i - 1].y = vertices[i].x;

		/* Define POINTS in second quadrant */
		vertices[POINTS/4 + i].x = -vertices[i].y;
		vertices[POINTS/4 + i].y =  vertices[i].x;

		vertices[POINTS/2 - i - 1].x = -vertices[i].x;
		vertices[POINTS/2 - i - 1].y =  vertices[i].y;

		/* Define POINTS in third quadrant */
		vertices[POINTS/2 + i].x = -vertices[i].x;
		vertices[POINTS/2 + i].y = -vertices[i].y;

		vertices[(POINTS*3)/4 - i - 1].x = -vertices[i].y;
		vertices[(POINTS*3)/4 - i - 1].y = -vertices[i].x;

		/* Define POINTS in fourth quadrant */
		vertices[(POINTS*3)/4 + i].x =  vertices[i].y;
		vertices[(POINTS*3)/4 + i].y = -vertices[i].x;

		vertices[POINTS - i - 1].x =  vertices[i].x;
		vertices[POINTS - i - 1].y = -vertices[i].y;
	}
}

void SCircle::draw(SLayer *layer)
{
	if (!initialized)
		initialize();

	vector<Color3f> colors(POINTS, color);

	int attrib_pos = layer->getAttrib("pos");
	int attrib_color = layer->getAttrib("color");
	int uniform_wvp = layer->getUniform("wvp");

	glUniformMatrix4fv(uniform_wvp, 1, GL_FALSE, value_ptr(layer->getWVP()));
	
	glEnableVertexAttribArray(attrib_pos);
	glVertexAttribPointer(attrib_pos, 2, GL_FLOAT, GL_FALSE, 0, &vertices.front());
	glEnableVertexAttribArray(attrib_color);
	glVertexAttribPointer(attrib_color, 3, GL_FLOAT, GL_FALSE, 0, &colors.front());

	/* Push each element in buffer_vertices to the vertex shader */
	glDrawArrays(GL_POLYGON, 0, POINTS);

	glDisableVertexAttribArray(attrib_pos);
	glDisableVertexAttribArray(attrib_color);
}

SCircle::SCircle(Color3f color)
	: color(color)
{}


}
