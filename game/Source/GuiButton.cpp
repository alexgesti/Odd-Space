#include "GuiButton.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
    this->bounds = bounds;
    this->text = text;
    this->id = id;
}

GuiButton::~GuiButton()
{
}

bool GuiButton::Update(Input* input, int buttonSelected, float dt)
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

            if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            // If mouse button pressed -> Generate event!
            if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_UP)
            {
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiButton::Draw(Render* render)
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
