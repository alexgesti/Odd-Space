#include "Speak.h"
#include "Render.h"
#include "Font.h"

Speak::Speak(Audio* audio, Render* render, Font* font)
{
	this->audio = audio;
	this->render = render;
	this->font = font;

	letter_1 = this->audio->LoadFx("Assets/Audio/Fx/text_sound1.wav");
	letter_2 = this->audio->LoadFx("Assets/Audio/Fx/text_sound2.wav");
	letter_3 = this->audio->LoadFx("Assets/Audio/Fx/text_sound3.wav");
	letter_4 = this->audio->LoadFx("Assets/Audio/Fx/text_sound4.wav");
}

void Speak::Update(float dt)
{
	if (textSaid == 0)
	{
		if (timeWaited >= LETTERSPEED)
		{
			switch (rand() % 4)
			{
			case 0:
				audio->PlayFx(letter_1);
				break;
			case 1:
				audio->PlayFx(letter_2);
				break;
			case 2:
				audio->PlayFx(letter_3);
				break;
			case 3:
				audio->PlayFx(letter_4);
				break;
			default: break;
			}

			letterAmount++;

			timeWaited = 0.0f;
		}

		if (letterAmount >= text.Length() + 1)
		{
			textSaid++;
			timeWaited = 0.0f;
			finished = true;
		}

		timeWaited += dt;

		Draw();
	}

	else if (finished) Draw();
}

void Speak::Draw()
{
	std::string textToRender;

	for (int i = 0; i < letterAmount; i++)
	{
		textToRender.push_back(copText.GetString()[i]);
	}

	render->DrawText(font, textToRender.c_str(), 0, 60, 50, 0, { 255, 0, 255, 255 });
}

void Speak::SayText(SString text)
{
	this->text = text;
	copText = text.GetString();
	letterAmount = 0;
	textSaid = 0;
	finished = false;
}

void Speak::Finish()
{
	letterAmount = text.Length();
}