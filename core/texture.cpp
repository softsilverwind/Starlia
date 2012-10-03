#include <SDL/SDL_image.h>
#include <GL/glu.h>
#include <cassert>
#include "texture.h"
#include "structs.h"

using namespace std;

namespace Starlia
{

unsigned int genTex(string filename)
{
	SDL_Surface *img = IMG_Load(filename.c_str());
	unsigned int texture;
	int mode;

	if (!img)
		return 0;

	if (img->format->BytesPerPixel == 3)
	{
		mode = GL_RGB;
	}
	else if (img->format->BytesPerPixel == 4)
	{
		mode = GL_RGBA;
	}
	else
	{
		SDL_FreeSurface(img);
		return 0;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, mode, img->w, img->h, mode, GL_UNSIGNED_BYTE, img->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(img);

	return texture;
}

}
