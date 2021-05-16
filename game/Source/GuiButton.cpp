#include "GuiButton.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text, Audio* audio, bool sorted) : GuiControl(GuiControlType::BUTTON, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
    this->audio = audio;
    this->sorted = sorted;

    hover = audio->LoadFx("Assets/Audio/Fx/hover_ui.wav");
    unavaliable = audio->LoadFx("Assets/Audio/Fx/unavaliable_ui.wav");
    press = audio->LoadFx("Assets/Audio/Fx/press_ui.wav");
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
        if (state != GuiControlState::DISABLED) state = GuiControlState::FOCUSED;

        if (soundReproduced == false)
        {
            audio->PlayFx(hover);
            soundReproduced = true;
        }

        if (input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN)
        {
            if (state == GuiControlState::DISABLED) audio->PlayFx(unavaliable);
            else state = GuiControlState::PRESSED;
        }

        // If mouse button pressed -> Generate event!
        if ((input->GetKey(SDL_SCANCODE_X) == KEY_UP || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_UP) && state != GuiControlState::DISABLED)
        {
            NotifyObserver();
            if (state != GuiControlState::DISABLED) audio->PlayFx(press);
        }
    }
    else
    {
        if (state != GuiControlState::DISABLED) state = GuiControlState::NORMAL;
        soundReproduced = false;
    }

    return false;
}

bool GuiButton::Draw(Render* render, Font* font)
{
    // Draw the right button depending on state

    int centerPoint;

    if (!sorted) centerPoint = 5;
    else centerPoint = (bounds.w / 2) - ((text.Length() * (bounds.h / 4)) / 2);

    switch (state)
    {
    case GuiControlState::DISABLED: 
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 100, 100, 100, 255 });
        }
        break;
    case GuiControlState::NORMAL:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 255, 255, 255, 255 });
        }
        break;
    case GuiControlState::FOCUSED:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 255, 0, 0, 255 });
        }
        break;
    case GuiControlState::PRESSED:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 0, 255, 0, 255 });
        }
        break;
    case GuiControlState::SELECTED:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x + centerPoint, bounds.y + (bounds.h / 2) - ((bounds.h / 3) / 2), bounds.h / 3, 1, { 0, 0, 255, 255 });
        }
        break;
    default:
        break;
    }

    if (font != nullptr)
    {
        /*const char* name = text.GetString();
        float textWidth = 0.0f;

        float scale = (float)bounds.h / font->GetCharRec(32).h;

        for (int i = 0; name[i] != 0; i++)
        {
            textWidth += font->GetCharRec(name[i]).w * scale;
        }

        int positionX = bounds.x + (bounds.w / 2) - ((int)textWidth / 2);

        render->DrawText(font, text.GetString(), positionX, bounds.y, bounds.h/3, 1, { 255, 255, 255, 255 });*/
        //render->DrawText(font, text.GetString(), bounds.x, bounds.y, bounds.h / 3, 1, { 255, 255, 255, 255 });
    }

    return false;
}
