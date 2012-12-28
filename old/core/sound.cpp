#include <SDL/SDL_mixer.h>
#include <vector>
#include <string>
#include <map>

#include "sound.h"

using namespace std;

namespace Starlia
{

map<string,Mix_Music *> StarSound::musics;
map<string,vector<Mix_Music *> > StarSound::playlists;
map<string,Mix_Chunk *> StarSound::sounds;

void StarSound::initialize()
{
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
}

void StarSound::loadMusic(string alias, string filename)
{
	musics[alias] = Mix_LoadMUS(filename.c_str()); // todo, moan if already used alias
}

void StarSound::playMusic(string alias, int repeat)
{
	map<string, Mix_Music *>::iterator it = musics.find(alias);
	if (it != musics.end())
		Mix_PlayMusic(it->second, repeat);
}


void StarSound::stopMusic()
{
	Mix_HaltMusic();
}

void StarSound::loadSound(string alias, string filename)
{
	sounds[alias] = Mix_LoadWAV(filename.c_str()); // same todo
}

void StarSound::playSound(string alias)
{
	map<string, Mix_Chunk *>::iterator it = sounds.find(alias);
	if (it != sounds.end())
		Mix_PlayChannel(-1, it->second, 0);
	else
		throw 42;
}

}
