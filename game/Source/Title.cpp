#include "Title.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"






// Constructor
Title::Title(Window* win, Input* input, Render* render, Textures* tex)
{
    this->win = win;
    this->input = input;
    this->render = render;
    this->tex = tex;

    // GUI: Initialize required controls for the screen
}
// Destructor
Title::~Title()
{
}



bool Title::Load()
{
    bgTitle = tex->Load("assets/sprites/MainScreen/title_screen.png");
    return false;
}

bool Title::Update(float dt)
{
    if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) TransitionToScene(SceneType::CANTINA);
        bool ret = false;

        if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
            win->ToggleFullscreen(win->window);

    return ret;
}

bool Title::Draw()
{
    render->DrawTexture(bgTitle, render->camera.x, render->camera.y);
    return false;
}

bool Title::Unload()
{
    // Delete buttons and textures
    tex->UnLoad(bgTitle);
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