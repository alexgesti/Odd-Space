#ifndef __SPEAK_H__
#define __SPEAK_H__

#define LETTERSPEED 0.1f

#include "SString.h"
#include "Audio.h"

class Render;
class Font;

class Speak
{
public:

	Speak(Audio* audio, Render* render, Font* font);

	void Update(float dt);

	void Draw();

	void SayText(SString text);

	void Finish();

private:

	Audio* audio;
	Render* render;
	Font* font;

	int letter_1 = 0;
	int letter_2 = 0;
	int letter_3 = 0;
	int letter_4 = 0;

	int textSaid = 1;

	float timeWaited = LETTERSPEED;

	int letterAmount = 0;

	bool finished = false;

	SString copText;

public:

	SString text = "/0";
};

#endif // __SPEAK_H__