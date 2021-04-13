#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#include "List.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f



struct _Mix_Music;
struct Mix_Chunk;

class Fx
{
public:
	uint id;
	int channel;
};

class Audio : public Module
{
public:

	// Constructor
	Audio();
	// Destructor
	virtual ~Audio();


	// Called before render is available
	bool Awake(pugi::xml_node&);


	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Unload a WAV
	bool UnloadFx(uint id);

	// Checks if a Fx sound is playing
	bool IsPlaying(uint id);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

private:

	_Mix_Music* music;
	List<Mix_Chunk*> fx;
	List<Fx> fxPlaying;
};

#endif // __AUDIO_H__