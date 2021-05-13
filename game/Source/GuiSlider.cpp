#include "GuiSlider.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text, Audio* audio) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
    this->audio = audio;

    selected = audio->LoadFx("Assets/Audio/Fx/hover_ui.wav");
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(Input* input, int buttonSelected, float dt)
{
    GamePad& pad = input->pads[0];

    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        input->GetMousePosition(mouseX, mouseY);

        // Check collision between mouse and button bounds
        /*if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && 
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
                audio->PlayFx(selected);
                soundReproduced = true;
            }

            if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
            {
                NotifyObserver();
                audio->PlayFx(selected);
            }
        }
        else
        {
            state = GuiControlState::NORMAL;
            soundReproduced = false;
        }
    }

    return false;
}

bool GuiSlider::Draw(Render* render, int slide)
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED: render->DrawRectangle(bounds, 100, 100, 100, 255);
        break;
    case GuiControlState::NORMAL: render->DrawRectangle(bounds, 0, 255, 0, 255);
        break;
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
