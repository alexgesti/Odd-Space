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

bool GuiButton::Draw(Render* render, Font* font, bool camera)
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED: render->DrawRectangle(bounds, 0, 0, 100, 255, true, camera);
        break;
    case GuiControlState::NORMAL:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x, bounds.y, bounds.h / 3, 1, { 0, 0, 0, 255 });
        }
        //render->DrawRectangle(bounds, 0, 255, 0, 255, true, camera);
        break;
    case GuiControlState::FOCUSED:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x, bounds.y, bounds.h / 3, 1, { 255, 0, 0, 255 });
        }
        //render->DrawRectangle(bounds, 255, 255, 0, 255, true, camera);
        break;
    case GuiControlState::PRESSED:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x, bounds.y, bounds.h / 3, 1, { 0, 255, 0, 255 });
        }
        //render->DrawRectangle(bounds, 0, 255, 255, 255, true, camera);
        break;
    case GuiControlState::SELECTED:
        if (font != nullptr)
        {
            render->DrawText(font, text.GetString(), bounds.x, bounds.y, bounds.h / 3, 1, { 0, 0, 255, 255 });
        }
        //render->DrawRectangle(bounds, 0, 255, 0, 255, true, camera);
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
