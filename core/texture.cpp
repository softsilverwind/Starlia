#include <cstdio>
#include <cstdlib>
#include <GL/glu.h>
#include <fstream>
#include <cassert>
#include "texture.h"
#include "structs.h"

using namespace std;

namespace Starlia
{

unsigned int genBMPTex(string filename)
{
	ifstream file(filename.c_str(), ios::binary);
	unsigned int sizex, sizey;
	char *img;
	unsigned short bpp;
	unsigned int siz;

	unsigned int texture;

	file.seekg(18, ios::cur);

	file.read((char *) &sizex, 4);
	file.read((char *) &sizey, 4);

	file.seekg(2, ios::cur);
	file.read((char *) &bpp, 2);

	file.seekg(24, ios::cur);

	siz = sizex * sizey * 3;

	img = new char[siz];

	file.read(img, siz);

	for (unsigned int i = 0; i < siz; i += 3)
		swap(img[i], img[i+2]);

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, sizex, sizey, GL_RGB, GL_UNSIGNED_BYTE, img );

	glBindTexture( GL_TEXTURE_2D, 0 );

	delete [] img;

	return texture;
}

}
