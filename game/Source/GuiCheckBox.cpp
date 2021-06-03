#include "GuiCheckBox.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text, Audio* audio) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
    this->audio = audio;

    hover = audio->LoadFx("audio/fx/hover_ui.wav");
    unavaliable = audio->LoadFx("audio/fx/unavaliable_ui.wav");
    press = audio->LoadFx("audio/fx/press_ui.wav");
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(Input* input, bool* checked, int buttonSelected, float dt)
{
    GamePad& pad = input->pads[0];

    check = *checked;

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
        state = GuiControlState::FOCUSED;

        if (soundReproduced == false)
        {
            audio->PlayFx(hover);
            soundReproduced = true;
        }

         if (input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT ||
            input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN)
        {
            if (disabled) audio->PlayFx(unavaliable);
            else state = GuiControlState::PRESSED;
        }

        // If mouse button pressed -> Generate event!
        if ((input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) && !disabled)
        {
            *checked = !*checked;
            check = *checked;
            NotifyObserver();
            audio->PlayFx(press);
            //explode = true;
        }
    }
    else
    {
        state = GuiControlState::NORMAL;
        soundReproduced = false;
    }

    return false;
}

bool GuiCheckBox::Draw(Render* render, SDL_Texture* texture)
{
    // Draw the right button depending on state
    SDL_Rect rect = { 848, 0, 32, 32 };

    if (state == GuiControlState::FOCUSED)
    {
        if (check)
        {
            rect = { 944, 0, 32, 32 };
            render->DrawTexture(texture, -render->camera.x + bounds.x + (bounds.w / 2) - (rect.w / 2), -render->camera.y + bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
        }
        else
        {
            rect = { 912, 0, 32, 32 };
            render->DrawTexture(texture, -render->camera.x + bounds.x + (bounds.w / 2) - (rect.w / 2), -render->camera.y + bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
        }
    }
    else
    {
        if (check)
        {
            rect = { 880, 0, 32, 32 };
            render->DrawTexture(texture, -render->camera.x + bounds.x + (bounds.w / 2) - (rect.w / 2), -render->camera.y + bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
        }
        else
        {
            render->DrawTexture(texture, -render->camera.x + bounds.x + (bounds.w / 2) - (rect.w / 2), -render->camera.y + bounds.y + (bounds.h / 2) - (rect.h / 2), &rect);
        }
    }

    return false;
}

bool GuiCheckBox::UnLoad()
{
    audio->UnloadFx(hover);
    audio->UnloadFx(unavaliable);
    audio->UnloadFx(press);

    return false;
}
