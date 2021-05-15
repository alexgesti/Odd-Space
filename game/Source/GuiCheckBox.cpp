#include "GuiCheckBox.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text, Audio* audio) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
    this->audio = audio;

    hover = audio->LoadFx("Assets/Audio/Fx/hover_ui.wav");
    unavaliable = audio->LoadFx("Assets/Audio/Fx/unavaliable_ui.wav");
    press = audio->LoadFx("Assets/Audio/Fx/press_ui.wav");
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(Input* input, int buttonSelected, float dt)
{
    GamePad& pad = input->pads[0];

    /*int mouseX, mouseY;
    input->GetMousePosition(mouseX, mouseY);

    // Check collision between mouse and button bounds
    if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && 
        (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
    {
        state = GuiControlState::FOCUSED;

        if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
        {
            state = GuiControlState::PRESSED;
        }

        // If mouse button pressed -> Generate event!
        if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
        {
            checked = !checked;
            NotifyObserver();
        }
    }*/

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
            else state = GuiControlState::PRESSED;
        }

        // If mouse button pressed -> Generate event!
        if (input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN && state == GuiControlState::DISABLED)
        {
            checked = !checked;
            NotifyObserver();
            audio->PlayFx(press);
        }
    }
    else
    {
        if (state != GuiControlState::DISABLED) state = GuiControlState::NORMAL;
        soundReproduced = false;
    }

    return false;
}

bool GuiCheckBox::Draw(Render* render, SDL_Texture* texture)
{
    // Draw the right button depending on state
    SDL_Rect rect = { 880, 0, 32, 32 }; //Check
    SDL_Rect rect2 = { 848, 0, 32, 32 }; //Nocheck
    SDL_Rect rect3 = { 912, 0, 32, 32 }; //NoCheckEncima
    SDL_Rect rect4 = { 944, 0, 32, 32 }; //checkEncima

    if (state == GuiControlState::FOCUSED)
    {
        if (checked) render->DrawTexture(texture, bounds.x + (bounds.w / 2) - (rect.w / 2), bounds.y + (bounds.h / 2) - (rect.h / 2), &rect4);
        else render->DrawTexture(texture, bounds.x + (bounds.w / 2) - (rect.w / 2), bounds.y + (bounds.h / 2) - (rect.h / 2), &rect3);
    }
    else
    {
        if (checked) render->DrawTexture(texture, bounds.x + (bounds.w / 2) - (rect.w / 2), bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
        else render->DrawTexture(texture, bounds.x + (bounds.w / 2) - (rect.w / 2), bounds.y + (bounds.h / 2) - (rect.h / 2), &rect2);
    }

    return false;
}
