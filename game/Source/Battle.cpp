#include "Battle.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "GuiButton.h"
#include "EntityManager.h"
#include <time.h> 
#include "Log.h"

#include "SDL/include/SDL.h"



// Constructor
Battle::Battle(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager)
{
    this->win = win;
    this->input = input;
    this->render = render;
    this->tex = tex;
    this->entityManager = entityManager;

    // GUI: Initialize required controls for the screen
    buttonsMenu.buttonAttack = new GuiButton(1, { 0, 0, 300, 80 }, "menuBattle");
    buttonsMenu.buttonAttack->SetObserver(this);
    buttonsMenu.buttonGuard = new GuiButton(2, { 300, 0, 300, 80 }, "menuBattle");
    buttonsMenu.buttonGuard->SetObserver(this);
    buttonsMenu.buttonSkills = new GuiButton(3, { 600, 0, 300, 80 }, "menuBattle");
    buttonsMenu.buttonSkills->SetObserver(this);
    buttonsMenu.buttonRun = new GuiButton(4, { 0, 80, 300, 80 }, "menuBattle");
    buttonsMenu.buttonRun->SetObserver(this);
    buttonsMenu.buttonItem = new GuiButton(5, { 300, 80, 300, 80 }, "menuBattle");
    buttonsMenu.buttonItem->SetObserver(this);
    buttonsMenu.buttonBack = new GuiButton(6, { 600, 80, 300, 80 }, "menuBattle");
    buttonsMenu.buttonBack->SetObserver(this);
    
    buttonsSkills.buttonSkill1 = new GuiButton(7, { 0, 160, 300, 80 }, "skillsBattle");
    buttonsSkills.buttonSkill1->SetObserver(this);
    buttonsSkills.buttonSkill2 = new GuiButton(8, { 300, 160, 300, 80 }, "skillsBattle");
    buttonsSkills.buttonSkill2->SetObserver(this);
    buttonsSkills.buttonSkill3 = new GuiButton(9, { 600, 160, 300, 80 }, "skillsBattle");
    buttonsSkills.buttonSkill3->SetObserver(this);
    buttonsSkills.buttonSkill4 = new GuiButton(10, { 0, 240, 300, 80 }, "skillsBattle");
    buttonsSkills.buttonSkill4->SetObserver(this);
    buttonsSkills.buttonSkill5 = new GuiButton(11, { 300, 240, 300, 80 }, "skillsBattle");
    buttonsSkills.buttonSkill5->SetObserver(this);
    buttonsSkills.buttonBack = new GuiButton(12, { 600, 240, 300, 80 }, "skillsBattle");
    buttonsSkills.buttonBack->SetObserver(this);

    srand(time(NULL));
    random = rand() % 3 + 1;
    for (int enemies = 0; enemies < random; enemies++)
    {
        switch (enemies)
        {
        case 0:
            buttonsEnemies.buttonEnemy1 = new GuiButton(13, { 0 + (300 * enemies), 320, 300, 80 }, "skillsBattle");
            buttonsEnemies.buttonEnemy1->SetObserver(this);
            break;
        case 1:
            buttonsEnemies.buttonEnemy2 = new GuiButton(14, { 0 + (300 * enemies), 320, 300, 80 }, "skillsBattle");
            buttonsEnemies.buttonEnemy2->SetObserver(this);
            break;
        case 2:
            buttonsEnemies.buttonEnemy3 = new GuiButton(15, { 0 + (300 * enemies), 320, 300, 80 }, "skillsBattle");
            buttonsEnemies.buttonEnemy3->SetObserver(this);
            break;
        case 3:
            buttonsEnemies.buttonEnemy4 = new GuiButton(16, { 0 + (300 * enemies), 320, 300, 80 }, "skillsBattle");
            buttonsEnemies.buttonEnemy4->SetObserver(this);
            break;
        case 4:
            buttonsEnemies.buttonEnemy5 = new GuiButton(17, { 0 + (300 * enemies), 320, 300, 80 }, "skillsBattle");
            buttonsEnemies.buttonEnemy5->SetObserver(this);
            break;
        default:break;
        }
       controllerEnemy[enemies] = { 13 + (1 * enemies) };
    }
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

    //LOG("%d\t%d\t%d", f, c, controllerSkill[f][c]);

    //Player Turn
    if (playerTurn)
    {
        if (chooseAction)
        {
            if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || input->pads[0].right > 0) controllerMenu[f][c++];
            if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || input->pads[0].left < 0) controllerMenu[f][c--];
            if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || input->pads[0].down > 0) controllerMenu[f++][c];
            if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->pads[0].up < 0) controllerMenu[f--][c];
            //Establecer limites fila/columna botones
            if (f > 1) f = 0;
            if (f < 0) f = 1;
            if (c > 2) c = 0;
            if (c < 0) c = 2;

            //LOG("%d", input->pads[0].right);

            buttonsMenu.buttonAttack->Update(input, controllerMenu[f][c], dt);
            buttonsMenu.buttonGuard->Update(input, controllerMenu[f][c], dt);
            buttonsMenu.buttonSkills->Update(input, controllerMenu[f][c], dt);
            buttonsMenu.buttonRun->Update(input, controllerMenu[f][c], dt);
            buttonsMenu.buttonItem->Update(input, controllerMenu[f][c], dt);
            buttonsMenu.buttonBack->Update(input, controllerMenu[f][c], dt);
        }
        //Skill Pickup
        else if (chooseSkill)
        {
            if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || input->pads[0].right > 0) controllerSkill[f][c++];
            if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || input->pads[0].left < 0) controllerSkill[f][c--];
            if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || input->pads[0].down > 0) controllerSkill[f++][c];
            if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->pads[0].up < 0) controllerSkill[f--][c];
            //Establecer limites fila/columna botones
            if (f > 1) f = 0;
            if (f < 0) f = 1;
            if (c > 2) c = 0;
            if (c < 0) c = 2;

            buttonsSkills.buttonSkill1->Update(input, controllerSkill[f][c], dt);
            buttonsSkills.buttonSkill2->Update(input, controllerSkill[f][c], dt);
            buttonsSkills.buttonSkill3->Update(input, controllerSkill[f][c], dt);
            buttonsSkills.buttonSkill4->Update(input, controllerSkill[f][c], dt);
            buttonsSkills.buttonSkill5->Update(input, controllerSkill[f][c], dt);
            buttonsSkills.buttonBack->Update(input, controllerSkill[f][c], dt);
        }
        //Enemy Pickup
        else if (chooseEnemy)
        {
            if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) controllerEnemy[f++];
            if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) controllerEnemy[f--];
            //Establecer limites fila/columna botones
            if (f > random - 1) f = 0;
            if (f < 0) f = random - 1;

            LOG("%d", random);

            switch (random)
            {
            case 5:
                buttonsEnemies.buttonEnemy5->Update(input, controllerEnemy[f], dt);
            case 4:
                buttonsEnemies.buttonEnemy4->Update(input, controllerEnemy[f], dt);
            case 3:
                buttonsEnemies.buttonEnemy3->Update(input, controllerEnemy[f], dt);
            case 2:
                buttonsEnemies.buttonEnemy2->Update(input, controllerEnemy[f], dt);
            case 1:
                buttonsEnemies.buttonEnemy1->Update(input, controllerEnemy[f], dt);
                break;
            default:break;
            }
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
    
    //Action Pickup
    if (chooseAction)
    {
        buttonsMenu.buttonAttack->Draw(render);
        buttonsMenu.buttonGuard->Draw(render);
        buttonsMenu.buttonSkills->Draw(render);
        buttonsMenu.buttonRun->Draw(render);
        buttonsMenu.buttonItem->Draw(render);
        buttonsMenu.buttonBack->Draw(render);
    }
    //Skill Pickup
    else if (chooseSkill)
    {
        buttonsSkills.buttonSkill1->Draw(render);
        buttonsSkills.buttonSkill2->Draw(render);
        buttonsSkills.buttonSkill3->Draw(render);
        buttonsSkills.buttonSkill4->Draw(render);
        buttonsSkills.buttonSkill5->Draw(render);
        buttonsSkills.buttonBack->Draw(render);
    }
    //Enemy Pickup
    else if (chooseEnemy)
    {
        switch (random)
        {
        case 5:
            buttonsEnemies.buttonEnemy5->Draw(render);
        case 4:
            buttonsEnemies.buttonEnemy4->Draw(render);
        case 3:
            buttonsEnemies.buttonEnemy3->Draw(render);
        case 2:
            buttonsEnemies.buttonEnemy2->Draw(render);
        case 1:
            buttonsEnemies.buttonEnemy1->Draw(render);
            break;
        default:break;
        }
    }

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
    //Menu Buttons
    if (chooseAction)
    {
        switch (control->id)
        {
        case 1:
            chooseAction = false;
            chooseEnemy = true;
            break;
        case 2:
            break;
        case 3:
            chooseAction = false;
            chooseSkill = true;
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default: break;
        }
        f = 0;
        c = 0;
    }

    //Skills Buttons
    if (chooseSkill)
    {
        switch (control->id)
        {
        case 7:
            chooseSkill = false;
            chooseEnemy = true;
            break;
        case 8:
            chooseSkill = false;
            chooseEnemy = true;
            break;
        case 9:
            chooseSkill = false;
            chooseEnemy = true;
            break;
        case 10:
            chooseSkill = false;
            chooseEnemy = true;
            break;
        case 11:
            chooseSkill = false;
            chooseEnemy = true;
            break;
        case 12:
            chooseSkill = false;
            chooseAction = true;
            break;
        default: break;
        }
        f = 0;
        c = 0;
    }

    //Enemies Buttons
    if (chooseEnemy)
    {
        switch (control->id)
        {
        case 13:

            break;
        case 14:

            break;
        case 15:

            break;
        case 16:

            break;
        case 17:

            break;
        case 18:

            break;
        default: break;
        }
        f = 0;
        c = 0;
    }

    return true;
}