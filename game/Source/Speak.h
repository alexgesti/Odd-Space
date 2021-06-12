#ifndef __SPEAK_H__
#define __SPEAK_H__

#define LETTERSPEED 0.05f
#define LINELENGTH 65

#include "SString.h"
#include "Audio.h"

class Render;
class Font;
class Input;
class Textures;
struct SDL_Texture;

class Speak
{
public:

	Speak(Audio* audio, Render* render, Font* font, Input* input, Textures* texture);

	void Update(float dt);

	void Draw();

	void SayText(SString text, bool slowly);

	void Finish();

private:

	Audio* audio;
	Render* render;
	Font* font;
	Input* input;
	Textures* texture;

	//Needed vars for showing letter individually with sounds
	int letter_1 = 0;
	int letter_2 = 0;
	int letter_3 = 0;
	int letter_4 = 0;

	float timeWaited = LETTERSPEED;

	int letterAmount = 0;

	SString copText;

	//Dialogue quad texture
	SDL_Texture* dialogueTex;

public:

	SString text = "/0";

	bool speaking = false;

	bool textSaid = false;

	bool paused = false;
};

#endif // __SPEAK_H__