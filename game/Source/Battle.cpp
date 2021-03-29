#include "Battle.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "GuiButton.h"
#include "Log.h"

#include "SDL/include/SDL.h"



// Constructor
Battle::Battle(Window* win, Input* input, Render* render, Textures* tex)
{
    this->win = win;
    this->input = input;
    this->render = render;
    this->tex = tex;

    // GUI: Initialize required controls for the screen
    buttonAttack = new GuiButton(1, { 0, 0, 300, 80 }, "MENU");
    buttonAttack->SetObserver(this);
    buttonGuard = new GuiButton(2, { 300, 0, 300, 80 }, "MENU");
    buttonGuard->SetObserver(this);
    buttonSkills = new GuiButton(3, { 0, 80, 300, 80 }, "MENU");
    buttonSkills->SetObserver(this);
    buttonRun = new GuiButton(4, { 600, 0, 300, 80 }, "MENU");
    buttonRun->SetObserver(this);
    buttonItem = new GuiButton(5, { 0, 160, 300, 80 }, "MENU");
    buttonItem->SetObserver(this);

}
// Destructor
Battle::~Battle()
{
}



bool Battle::Load()
{
    //Escogedor de textura
    /*switch (current)
    {
    case CANTINA:
    cantinaBattle = app->tex->Load("");
        break;
    }*/

    //Calculo de turno

    return false;
}

bool Battle::Update(float dt)
{
    bool ret = false;

    if (playerTurn)
    {
        if (input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) buttonSupport++;
        if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) buttonSupport =+ 3;
        if (buttonSupport > 6) buttonSupport = 1;
        if (buttonSupport < 1) buttonSupport = 6;

        switch (buttonSupport)
        {
        case 1:
            buttonAttack->state = GuiControlState::FOCUSED;
            break;
        case 2:
            buttonGuard->state = GuiControlState::FOCUSED;
            break;
        case 3:
            buttonSkills->state = GuiControlState::FOCUSED;
            break;
        case 4:
            buttonRun->state = GuiControlState::FOCUSED;
            break;
        case 5:
            buttonItem->state = GuiControlState::FOCUSED;
            break;
        }

        buttonAttack->Update(input, dt);
        buttonGuard->Update(input, dt);
        buttonSkills->Update(input, dt);
        buttonRun->Update(input, dt);
        buttonItem->Update(input, dt);
    }
    if (!playerTurn)
    {

        playerTurn = !playerTurn;
    }

    return ret;
}

bool Battle::Draw()
{
    render->DrawRectangle({ 0, 0, 1280, 720 }, 255, 255, 255, 255);
    //Menu
    render->DrawRectangle({ 0, 550, 500, 170 }, 255, 233, 0, 255);
    render->DrawRectangle({ 500, 550, 780, 170 }, 255, 150, 0, 255);
    //Player
    render->DrawRectangle({ 0, 475, 225, 75 }, 255, 0, 0, 255);
    render->DrawRectangle({ 225, 475, 225, 75 }, 0, 255, 0, 255);

    buttonAttack->Draw(render);
    buttonGuard->Draw(render);
    buttonSkills->Draw(render);
    buttonRun->Draw(render);
    buttonItem->Draw(render);
    return false;
}

bool Battle::Unload()
{
    // Delete buttons and textures
    return false;
}


int Battle::DamageCalculator()
{
    int damage = 0;

    return damage;
}


//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool Battle::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->type)
    {
        case GuiControlType::BUTTON:
        {
            switch (control->id)
            {
            case 1:
                DamageCalculator();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default: break;
            }
        }
        default: break;
    }
    return true;
}