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
    buttonAttack = new GuiButton(1, { 0, 0, 300, 80 }, "menuBattle");
    buttonAttack->SetObserver(this);
    buttonGuard = new GuiButton(2, { 300, 0, 300, 80 }, "menuBattle");
    buttonGuard->SetObserver(this);
    buttonSkills = new GuiButton(3, { 600, 0, 300, 80 }, "menuBattle");
    buttonSkills->SetObserver(this);
    buttonRun = new GuiButton(4, { 0, 80, 300, 80 }, "menuBattle");
    buttonRun->SetObserver(this);
    buttonItem = new GuiButton(5, { 300, 80, 300, 80 }, "menuBattle");
    buttonItem->SetObserver(this);
    buttonBack1 = new GuiButton(6, { 600, 80, 300, 80 }, "menuBattle");
    buttonBack1->SetObserver(this);

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

    //Player Turn
    if (playerTurn)
    {
        if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || input->pads[0].right > 0) controllerMenuSupport[f][c++];
        if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || input->pads[0].left < 0) controllerMenuSupport[f][c--];
        if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || input->pads[0].down > 0) controllerMenuSupport[f++][c];
        if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->pads[0].up < 0) controllerMenuSupport[f--][c];
        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;
        if (c > 2) c = 0;
        if (c < 0) c = 2;

        LOG("%d", input->pads[0].right);

        //Skill Pickup
        /*if (chooseSkill)
        {
            if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) controllerSkillSupport[f][c++];
            if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) controllerSkillSupport[f][c--];
            if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) controllerSkillSupport[f++][c];
            if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) controllerSkillSupport[f--][c];
            //Establecer limites fila/columna botones
            if (f > 1) f = 0;
            if (f < 0) f = 1;
            if (c > 2) c = 0;
            if (c < 0) c = 2;

            buttonSkill1->Update(input, controllerMenuSupport[f][c], dt);
            buttonSkill2->Update(input, controllerMenuSupport[f][c], dt);
            buttonSkill3->Update(input, controllerMenuSupport[f][c], dt);
            buttonSkill4->Update(input, controllerMenuSupport[f][c], dt);
            buttonSkill5->Update(input, controllerMenuSupport[f][c], dt);
            buttonBack2->Update(input, controllerMenuSupport[f][c], dt);
        }
        //Enemy Pickup
        else if (chooseEnemy)
        {
            if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) controllerEnemySupport[f][c++];
            if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) controllerEnemySupport[f][c--];
            if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) controllerEnemySupport[f++][c];
            if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) controllerEnemySupport[f--][c];
            //Establecer limites fila/columna botones
            if (f > 1) f = 0;
            if (f < 0) f = 1;
            if (c > 2) c = 0;
            if (c < 0) c = 2;
            DamageCalculator();
        }
        else*/
        {
            buttonAttack->Update(input, controllerMenuSupport[f][c], dt);
            buttonGuard->Update(input, controllerMenuSupport[f][c], dt);
            buttonSkills->Update(input, controllerMenuSupport[f][c], dt);
            buttonRun->Update(input, controllerMenuSupport[f][c], dt);
            buttonItem->Update(input, controllerMenuSupport[f][c], dt);
            buttonBack1->Update(input, controllerMenuSupport[f][c], dt);
        }

    }
    //Enemy Turn
    if (!playerTurn)
    {
        playerTurn = true;
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
    buttonBack1->Draw(render);

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
                chooseEnemy = true;
                f = 0;
                c = 0;
                break;
            case 2:
                DamageCalculator();              
                break;
            case 3:
                chooseSkill = true;
                f = 0;
                c = 0;
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default: break;
            }
        }
        default: break;
    }
    return true;
}