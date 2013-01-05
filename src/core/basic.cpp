#include <iostream>
#include <cstdio>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <core/basic.h>

namespace Starlia
{

using namespace std;
using namespace glm;

bool SBasicLayer::initialized = false;

const char *SBasicLayer::v_shader =
		"#version 120\n"
		"attribute vec3 pos;\n"
		"attribute vec3 color;\n"
		"\n"
		"uniform mat4 wvp;\n"
		"varying vec3 f_color;\n"
		"\n"
		"void main(void)\n"
		"{\n"
		"\t gl_Position = wvp * vec4(pos, 1.0);\n"
		"\tf_color = color;\n"
		"}\n";

const char *SBasicLayer::f_shader =
		"#version 120\n"
		"varying vec3 f_color;\n"
		"\n"
		"void main(void)\n"
		"{\n"
		"\tgl_FragColor = vec4(f_color, 1.0);\n"
		"}\n";

unsigned SBasicLayer::linked_program = 0;

void SBasicLayer::initialize()
{
	initialized = true;

	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &v_shader, NULL);
	glCompileShader(vs);

	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &f_shader, NULL);
	glCompileShader(fs);

	linked_program = glCreateProgram();
	glAttachShader(linked_program, vs);
	glAttachShader(linked_program, fs);
	glLinkProgram(linked_program);

	int link_ok = 0;
	glGetProgramiv(linked_program, GL_LINK_STATUS, &link_ok);

	if (!link_ok)
		cerr << "SBasicLayer failed to link shader" << endl;
}

SBasicLayer::SBasicLayer()
{
	if (!initialized)
		initialize();

	program = linked_program;
}

bool SCircle::initialized = false;
vector<Coord2d> SCircle::vertices;

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

void SCircle::draw()
{
	if (!initialized)
		initialize();

	vector<Color3f> colors(POINTS, color);

	layer->setWorld(scale(translate(mat4(1.0f), vec3(position.x, position.y, 0)), vec3(radius.x, radius.y, 1)));

	int attrib_pos = layer->getAttrib("pos");
	int attrib_color = layer->getAttrib("color");
	int uniform_wvp = layer->getUniform("wvp");

	glUniformMatrix4fv(uniform_wvp, 1, GL_FALSE, value_ptr(layer->getWVP()));
	
	glEnableVertexAttribArray(attrib_pos);
	glVertexAttribPointer(attrib_pos, 2, GL_DOUBLE, GL_FALSE, 0, &vertices.front());
	glEnableVertexAttribArray(attrib_color);
	glVertexAttribPointer(attrib_color, 3, GL_FLOAT, GL_FALSE, 0, &colors.front());

	/* Push each element in buffer_vertices to the vertex shader */
	glDrawArrays(GL_POLYGON, 0, POINTS);

	glDisableVertexAttribArray(attrib_pos);
	glDisableVertexAttribArray(attrib_color);
}

SCircle::SCircle(Coord2d position, Coord2d radius, Color3f color)
	: position(position), radius(radius), color(color)
{}

}
