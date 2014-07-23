#version 120

attribute vec3 pos;
attribute vec3 color;

uniform mat4 wvp;
varying vec3 f_color;

void main(void)
{
	gl_Position = wvp * vec4(pos, 1.0);
	f_color = color;
}
