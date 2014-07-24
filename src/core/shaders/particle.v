#version 120

attribute vec3 pos;
attribute vec2 texcoord;

varying vec2 f_texcoord;

uniform mat4 wvp;

void main(void)
{
	gl_Position = wvp * vec4(pos, 1.0);
	f_texcoord = texcoord;
}
