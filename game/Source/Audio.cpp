#include "Audio.h"
#include "Assets.h"

#include "Defs.h"
#include "Log.h"

// NOTE: Recommended using: Additional Include Directories,
// instead of 'hardcoding' library location path in code logic
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL_mixer/libx86/SDL2_mixer.lib")



// Constructor
Audio::Audio(Assets* assets) : Module()
{
	for (int m = 0; m < MAX_STORED_MUSIC; m++) music[m] = NULL;

	name.Create("audio");

	this->assets = assets;
}
// Destructor
Audio::~Audio()
{}


// Called before render is available
bool Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// Load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	// Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	return ret;
}


// Called before quitting
bool Audio::CleanUp()
{
	if(!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	for (int m = 0; m < MAX_STORED_MUSIC; m++)
	{
		if (music[m] != NULL)
		{
			Mix_FreeMusic(music[m]);
		}
	}

	ListItem<Mix_Chunk*>* item;
	for(item = fx.start; item != NULL; item = item->next)
		Mix_FreeChunk(item->data);

	fx.Clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}


// Play a music file
bool Audio::PlayMusic(const char* path, float fadeTime)
{
	bool ret = true;

	if(!active)
		return false;

	bool found = false;

	for (int m = 0; m < MAX_STORED_MUSIC; m++)
	{
		if (prevpath[m] == path)
		{
			found = true;
			if (music[m] == NULL)
			{
				LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
				ret = false;
			}
			else
			{
				if (fadeTime > 0.0f)
				{
					if (Mix_FadeInMusic(music[m], -1, (int)(fadeTime * 1000.0f)) < 0)
					{
						LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
						ret = false;
					}
				}
				else
				{
					if (Mix_PlayMusic(music[m], -1) < 0)
					{
						LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
						ret = false;
					}
				}
			}
			LOG("Successfully playing %s", path);
			break;
		}
	}
	if (!found)
	{
		for (int m = 0; m < MAX_STORED_MUSIC; m++)
		{
			if (music[m] == NULL && path != NULL)
			{
				music[m] = Mix_LoadMUS_RW(assets->Load(path), 1);

				if (music[m] == NULL)
				{
					LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
					ret = false;
				}
				else
				{
					if (fadeTime > 0.0f)
					{
						if (Mix_FadeInMusic(music[m], -1, (int)(fadeTime * 1000.0f)) < 0)
						{
							LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
							ret = false;
						}
					}
					else
					{
						if (Mix_PlayMusic(music[m], -1) < 0)
						{
							LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
							ret = false;
						}
					}
				}
				prevpath[m] = path;
				LOG("Successfully playing %s", path);
				break;
			}
			else LOG("Could not stored it");
		}
	}

	return ret;
}

// Load WAV
unsigned int Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if(!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV_RW(assets->Load(path), 1);
	assets->DeleteBuffer();

	if(chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.Add(chunk);
		ret = fx.Count();
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id,int channel, int repeat)
{
	bool ret = false;

	if(!active)
		return false;

	int currentChannel = 0;

	if(id > 0 && id <= fx.Count())
	{
		currentChannel = Mix_PlayChannel(channel, fx[id - 1], repeat);

		Fx tempFx;
		tempFx.channel = currentChannel;
		tempFx.id = id;
		fxPlaying.Add(tempFx);
	}

	return ret;
}

bool Audio::UnloadFx(uint id)
{
	bool ret = false;

	if (fx[id - 1] != nullptr)
	{
		Mix_FreeChunk(fx[id - 1]);
		fx[id - 1] = nullptr;
		ret = true;
	}

	return ret;
}

bool Audio::IsPlaying(uint id)
{
	bool ret = false;

	for (int i = 0; i < fxPlaying.Count(); i++)
	{
		if (fxPlaying.At(i)->data.id == id)
		{
			if (Mix_Playing(fxPlaying.At(i)->data.channel)) ret = true;

			else
			{
				fxPlaying.Del(fxPlaying.At(i));
				ret = false;
			}
		}
	}

	return ret;
}

void Audio::FadeOutFx(int ms)
{
	for (int i = 0; i < fxPlaying.Count(); i++)
	{
		Mix_FadeOutChannel(fxPlaying.At(i)->data.channel, ms);
	}
}

void Audio::FadeOutMusic(float time, const char* path)
{
	bool fade = false;
	for (int m = 0; m < MAX_STORED_MUSIC; m++)
	{
		if (prevpath[m] == path && music[m] != NULL)
		{
			fade = true;
			if (time > 0.0f)
			{
				Mix_FadeOutMusic(int(time * 1000.0f));
			}
			break;
		}
	}
	if (fade) LOG("Could not load it");
}

void Audio::FadeInMusic(float time, const char* path)
{
	bool fade = false;
	for (int m = 0; m < MAX_STORED_MUSIC; m++)
	{
		if (prevpath[m] == path && music[m] != NULL)
		{
			fade = true;
			if (time > 0.0f)
			{
				Mix_FadeInMusic(music[m], -1, int(time * 1000.0f));
			}
			break;
		}
	}
	if(fade) LOG("Could not load it");
}