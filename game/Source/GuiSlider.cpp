#include "GuiSlider.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text, Audio* audio) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
    this->audio = audio;

    hover = audio->LoadFx("audio/fx/hover_ui.wav");
    unavaliable = audio->LoadFx("audio/fx/unavaliable_ui.wav");
    press = audio->LoadFx("audio/fx/press_ui.wav");
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(Input* input, int buttonSelected, float dt)
{
    GamePad& pad = input->pads[0];

    /*int mouseX, mouseY;
    input->GetMousePosition(mouseX, mouseY);

    // Check collision between mouse and button bounds
    if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && 
        (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
    {
        state = GuiControlState::FOCUSED;

        percentage = (mouseX - bounds.x) / (bounds.w / 100);
        guiderender = mouseX;
    }
    else state = GuiControlState::NORMAL;*/

    if (id == buttonSelected)
    {
        state = GuiControlState::FOCUSED;

        if (soundReproduced == false)
        {
            audio->PlayFx(hover);
            soundReproduced = true;
        }

        if ((input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) && disabled)
            audio->PlayFx(unavaliable);

        if (input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT && !disabled)
        {
            state = GuiControlState::PRESSED;
            if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
            {
                NotifyObserver();
                audio->PlayFx(press);
            }
        }
    }
    else
    {
        state = GuiControlState::NORMAL;
        soundReproduced = false;
    }

    return false;
}

bool GuiSlider::Draw(Render* render, int slide, SDL_Texture* texture)
{
    // Draw the right button depending on state
    SDL_Rect rect = { 848, 32, 32, 32 };

    render->DrawRectangle({ -render->camera.x + bounds.x, -render->camera.y + bounds.y, bounds.w, bounds.h }, 255, 255, 255, 255);

    SDL_Rect colorRect = { -render->camera.x + bounds.x, -render->camera.y + bounds.y, (-render->camera.x + (bounds.x - rect.w / 2) + (bounds.w / 4) * (slide / 32)) - (-render->camera.x + bounds.x) + 16, bounds.h };
    SDL_Color color1 = { 255, 255, 200, 255 };
    SDL_Color color2 = { 255, 255, 0, 255 };
    render->DrawDegradedRectVertical(colorRect, color1, color2);

    if (state == GuiControlState::FOCUSED)
    {
        rect = { 880, 32, 32, 32 };
        render->DrawTexture(texture, -render->camera.x + (bounds.x - rect.w / 2) + (bounds.w / 4) * (slide / 32), -render->camera.y + bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
    }
    else if (state == GuiControlState::PRESSED) 
    {
        rect = { 912, 32, 32, 32 };
        render->DrawTexture(texture, -render->camera.x + (bounds.x - rect.w / 2) + (bounds.w / 4) * (slide / 32), -render->camera.y + bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
    }
    else
    {
        render->DrawTexture(texture, -render->camera.x + (bounds.x - rect.w / 2) + (bounds.w / 4) * (slide / 32), -render->camera.y + bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
    }

    return false;
}

bool GuiSlider::UnLoad()
{
    audio->UnloadFx(hover);
    audio->UnloadFx(unavaliable);
    audio->UnloadFx(press);

    return false;
}
