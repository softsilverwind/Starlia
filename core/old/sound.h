#ifndef __SOUND_H__
#define __SOUND_H__

#include <SDL/SDL_mixer.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

namespace Starlia
{

class StarSound
{
	private:
		static map<string,Mix_Music *> musics;
		static map<string,vector<Mix_Music *> > playlists;
		static map<string,Mix_Chunk *> sounds;

		static void initialize();

	public:
		static void loadMusic(string alias, string filename);
		static void playMusic(string alias, int repeat);
		static void stopMusic();

		static void loadSound(string alias, string filename);
		static void playSound(string alias);

		// todo, unload music

	friend class StarCore;
};

}

#endif /* __SOUND_H__ */
