#include "Speak.h"
#include "Render.h"
#include "Font.h"
#include "Input.h"

Speak::Speak(Audio* audio, Render* render, Font* font, Input* input)
{
	this->audio = audio;
	this->render = render;
	this->font = font;
	this->input = input;

	letter_1 = this->audio->LoadFx("Assets/Audio/Fx/text_sound1.wav");
	letter_2 = this->audio->LoadFx("Assets/Audio/Fx/text_sound2.wav");
	letter_3 = this->audio->LoadFx("Assets/Audio/Fx/text_sound3.wav");
	letter_4 = this->audio->LoadFx("Assets/Audio/Fx/text_sound4.wav");
}

void Speak::Update(float dt)
{
	if (textSaid == false)
	{
		if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) Finish();

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
			textSaid = true;
			timeWaited = 0.0f;
			speaking = false;
		}

		timeWaited += dt;

		Draw();
	}

	else if (!speaking) Draw();
}

void Speak::Draw()
{
	SDL_Rect rect = { 0, 540, 1280, 180 };
	render->DrawRectangle(rect, 0, 0, 0, 255, true, false);

	std::string textToRender;

	for (int i = 0; i < letterAmount; i++)
	{
		textToRender.push_back(copText.GetString()[i]);
	}

	render->DrawText(font, textToRender.c_str(), 0, 610, 25, 0, { 255, 0, 255, 255 });
}

void Speak::SayText(SString text, bool slowly)
{
	this->text = text;
	copText = text.GetString();
	if (!slowly)
	{
		letterAmount = text.Length() + 1;
		textSaid = true;
		speaking = false;
	}

	else
	{
		letterAmount = 0;
		textSaid = false;
		speaking = true;
	}
}

void Speak::Finish()
{
	letterAmount = text.Length();
	speaking = false;
	textSaid = true;
}