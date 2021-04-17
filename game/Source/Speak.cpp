#include "Speak.h"
#include "Render.h"
#include "Font.h"
#include "Input.h"
#include "Textures.h"

Speak::Speak(Audio* audio, Render* render, Font* font, Input* input, Textures* texture)
{
	this->audio = audio;
	this->render = render;
	this->font = font;
	this->input = input;
	this->texture = texture;

	letter_1 = this->audio->LoadFx("Assets/Audio/Fx/text_sound1.wav");
	letter_2 = this->audio->LoadFx("Assets/Audio/Fx/text_sound2.wav");
	letter_3 = this->audio->LoadFx("Assets/Audio/Fx/text_sound3.wav");
	letter_4 = this->audio->LoadFx("Assets/Audio/Fx/text_sound4.wav");

	dialogueTex = texture->Load("assets/sprites/UI/UI_Text.png");
}

void Speak::Update(float dt)
{
	if (textSaid == false)
	{
		//if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) Finish();

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
	//SDL_Rect rect = { 0, 540, 1280, 180 };
	//render->DrawRectangle(rect, 0, 0, 0, 255, true, false);
	SDL_Rect rect = { 0, 0, 1280, 174 };
	render->DrawTexture(dialogueTex, -render->camera.x, -render->camera.y + 546, &rect);

	std::string textToRender;
	std::string textToRender2 = "";

	bool nextLine = false;

	for (int i = 0; i < letterAmount; i++)
	{
		if (i <= LINELENGTH) textToRender.push_back(copText.GetString()[i]);

		// Only skip to the next line if the current word has been completely written
		else if (i > LINELENGTH && !nextLine)
		{
			// 32 is ASCII code for space
			if (int(copText.GetString()[i]) == 32) nextLine = true;
			textToRender.push_back(copText.GetString()[i]);
		}

		else if (nextLine) textToRender2.push_back(copText.GetString()[i]);
	}

	render->DrawText(font, textToRender.c_str(), 15, 600, 21, 0, { 255, 255, 255, 255 });
	if(textToRender2 != "") render->DrawText(font, textToRender2.c_str(), 15, 645, 21, 0, { 255, 255, 255, 255 });
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