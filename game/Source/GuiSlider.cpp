#include "GuiSlider.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text, Audio* audio) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
    this->audio = audio;

    hover = audio->LoadFx("Assets/Audio/Fx/hover_ui.wav");
    unavaliable = audio->LoadFx("Assets/Audio/Fx/unavaliable_ui.wav");
    press = audio->LoadFx("Assets/Audio/Fx/press_ui.wav");
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
        if (state != GuiControlState::DISABLED) state = GuiControlState::FOCUSED;

        if (soundReproduced == false)
        {
            audio->PlayFx(hover);
            soundReproduced = true;
        }

        if (input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT)
        {
            if (state == GuiControlState::DISABLED) audio->PlayFx(unavaliable);
            else
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
    }
    else
    {
        if (state != GuiControlState::DISABLED) state = GuiControlState::NORMAL;
        soundReproduced = false;
    }

    return false;
}

bool GuiSlider::Draw(Render* render, int slide, SDL_Texture* texture)
{
    // Draw the right button depending on state
    SDL_Rect rec = { 848, 32, 32, 32 };
    SDL_Rect rec2 = { 880, 32, 32, 32 };
    SDL_Rect rec3 = { 912, 32, 32, 32 };

    render->DrawRectangle(bounds, 255, 255, 255, 255);
    if (state == GuiControlState::FOCUSED) render->DrawTexture(texture, (bounds.x - rec.w / 2) + (bounds.w / 4) * (slide / 32), bounds.y + (bounds.h / 2) - (rec.h / 2), &rec2);
    else if (state == GuiControlState::PRESSED) render->DrawTexture(texture, (bounds.x - rec.w / 2) + (bounds.w / 4) * (slide / 32), bounds.y + (bounds.h / 2) - (rec.h / 2), &rec3);
    else render->DrawTexture(texture, (bounds.x - rec.w / 2) + (bounds.w / 4) * (slide / 32), bounds.y + (bounds.h / 2) - (rec.h / 2), &rec);
    return false;
}
