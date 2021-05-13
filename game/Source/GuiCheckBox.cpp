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
        if (input->GetKey(SDL_SCANCODE_X) == KEY_UP || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_UP && state == GuiControlState::DISABLED)
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

bool GuiCheckBox::Draw(Render* render)
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED:
    {
        if (checked) render->DrawRectangle(bounds, 100, 100, 100, 255);
        else render->DrawRectangle(bounds, 100, 100, 100, 255);
    } break;
    case GuiControlState::NORMAL: 
    {
        if (checked) render->DrawRectangle(bounds, 0, 255, 0, 255);
        else render->DrawRectangle(bounds, 0, 255, 0, 255);
    } break;
    case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 255, 255, 0, 255);
        break;
    case GuiControlState::PRESSED: render->DrawRectangle(bounds, 0, 255, 255, 255);
        break;
    case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
        break;
    default:
        break;
    }

    return false;
}
