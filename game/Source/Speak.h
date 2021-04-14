#ifndef __SPEAK_H__
#define __SPEAK_H__

#define LETTERSPEED 0.1f
#define LINELENGTH 50

#include "SString.h"
#include "Audio.h"

class Render;
class Font;
class Input;

class Speak
{
public:

	Speak(Audio* audio, Render* render, Font* font, Input* input);

	void Update(float dt);

	void Draw();

	void SayText(SString text, bool slowly);

	void Finish();

private:

	Audio* audio;
	Render* render;
	Font* font;
	Input* input;

	int letter_1 = 0;
	int letter_2 = 0;
	int letter_3 = 0;
	int letter_4 = 0;

	float timeWaited = LETTERSPEED;

	int letterAmount = 0;

	SString copText;

public:

	SString text = "/0";

	bool speaking = false;

	bool textSaid = false;
};

#endif // __SPEAK_H__