#include "GuiButton.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text, Audio* audio, bool sorted) : GuiControl(GuiControlType::BUTTON, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
    this->audio = audio;
    this->sorted = sorted;

    hover = audio->LoadFx("audio/fx/hover_ui.wav");
    unavaliable = audio->LoadFx("audio/fx/unavaliable_ui.wav");
    press = audio->LoadFx("audio/fx/press_ui.wav");
}

GuiButton::~GuiButton()
{
}

bool GuiButton::Update(Input* input, int buttonSelected, float dt)
{
    GamePad& pad = input->pads[0];

    /*int mouseX, mouseY;
    input->GetMousePosition(mouseX, mouseY);

    // Check collision between mouse and button bounds
    if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && 
        (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
    {
        buttonSelected = id;
        
        state = GuiControlState::FOCUSED;
         
        if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
        {
            state = GuiControlState::PRESSED;
        }

        // If mouse button pressed -> Generate event!
        if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
        {
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

        if ((input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) && disabled)
           audio->PlayFx(unavaliable);

        if (input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT && !disabled)
            state = GuiControlState::PRESSED;

        // If mouse button pressed -> Generate event!
        if ((input->GetKey(SDL_SCANCODE_X) == KEY_UP || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_UP) && !disabled)
        {
            state = GuiControlState::SELECTED;
            red = 0;
            green = 0;
            blue = 0;
            NotifyObserver();
            audio->PlayFx(press);
        }
    }
    else
    {
        state = GuiControlState::NORMAL;
        red = 0;
        green = 0;
        blue = 0;
        soundReproduced = false;
    }

    if (GuiButton::state == GuiControlState::FOCUSED)
    {
        if (green >= 255) colorSpectrum = true;
        else if (green <= 0) colorSpectrum = false;

        if (colorSpectrum)
        {
            green -= 5;
            blue -= 5;
        }
        else
        {
            green += 5;
            blue += 5;
        }
    }

    if (GuiButton::state == GuiControlState::PRESSED)
    {
        if (blue >= 255) colorSpectrum = true;
        else if (blue <= 0) colorSpectrum = false;

        if (colorSpectrum) blue -= 5;
        else blue += 5;
    }

    return false;
}

bool GuiButton::Draw(Render* render, Font* font)
{
    // Draw the right button depending on state

    int centerPoint;

    if (!sorted) centerPoint = 5;
    else centerPoint = (bounds.w / 2) - ((text.Length() * (bounds.h / 4)) / 2);

    if (disabled)
    {
        switch (state)
        {
        case GuiControlState::NORMAL:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 100, 100, 100, 255 });
            }
            break;
        case GuiControlState::FOCUSED:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 200, 200, 200, 255 });
            }
            break;
        case GuiControlState::PRESSED:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 200, 200, 200, 255 });
            }
            break;
        case GuiControlState::SELECTED:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 200, 200, 200, 255 });
            }
            break;
        default: break;
        }
    }
    else
    {
        switch (state)
        {
        case GuiControlState::NORMAL:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 255, 255, 255, 255 });
            }
            break;
        case GuiControlState::FOCUSED:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 255, green, blue, 255 });
            }
            break;
        case GuiControlState::PRESSED:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 255, 255, blue, 255 });
            }
            break;
        case GuiControlState::SELECTED:
            if (font != nullptr)
            {
                render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 0, 255, 0, 255 });
            }
            break;
        default: break;
        }
    }

    return false;
}

bool GuiButton::UnLoad()
{
    audio->UnloadFx(hover);
    audio->UnloadFx(unavaliable);
    audio->UnloadFx(press);

    return false;
}
