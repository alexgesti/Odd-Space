#include "Title.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"

#include "SDL/include/SDL.h"


Title::Title()
{
    // GUI: Initialize required controls for the screen
}

Title::~Title()
{
}

bool Title::Load(Textures* tex)
{
    return false;
}

bool Title::Update(Input* input, float dt)
{
    if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) TransitionToScene(SceneType::CANTINA);
        bool ret = false;

    if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
        this->fullscreenChange = true;

    return ret;
}

bool Title::Draw(Render* render)
{
    render->DrawRectangle({ 0, 0, 1280, 720 }, 255, 255, 0, 255);
    return false;
}

bool Title::Unload(Textures* tex)
{
    // Delete buttons and textures
    return false;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
/*bool Title::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->type)
    {
    case GuiControlType::BUTTON:
    {
        if (control->id == 1) TransitionToScene(SceneType::GAMEPLAY);
        else if (control->id == 2) return false; // TODO: Exit request
    }
    default: break;
    }
    return true;
}*/