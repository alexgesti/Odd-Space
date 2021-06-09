#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#include "List.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_STORED_MUSIC 5



class Assets;

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
	Audio(Assets* assets);
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
	bool PlayFx(unsigned int fx,int channel=-1, int repeat = 0);

	// FadeOut all audio
	void FadeOutFx(int ms);

	void FadeOutMusic(float time, const char* path);

	void FadeInMusic(float time, const char* path);

private:

	const char* storedPath[MAX_STORED_MUSIC];
	const char* prevPath;

	_Mix_Music* music[MAX_STORED_MUSIC];
	List<Mix_Chunk*> fx;
	List<Fx> fxPlaying;

	Assets* assets;
};

#endif // __AUDIO_H__