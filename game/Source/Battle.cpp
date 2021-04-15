#include "Battle.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "EntityManager.h"
#include "GuiButton.h"
#include "Map.h"

#include "Speak.h"

#include <time.h> 
#include "Log.h"



// Constructor
Battle::Battle(Window* win, Input* input, Render* render, Textures* tex, EntityManager* entityManager, Font* font, Speak* speak)
{
    this->win = win;
    this->input = input;
    this->render = render;
    this->tex = tex;
    this->entityManager = entityManager;

    this->speak = speak;

    this->font = font;

    map = new Map(tex);

    if (*entityManager->previousScene == SceneType::CANTINA)
    {
        if (map->Load("combat_cantina_interior.tmx") == true)
        {
            int w, h;
            uchar* data = NULL;

            RELEASE_ARRAY(data);
        }
    }
    else if (*entityManager->previousScene == SceneType::EXTERIOR)
    {
        if (map->Load("combat_cantina_exterior.tmx") == true)
        {
            int w, h;
            uchar* data = NULL;

            RELEASE_ARRAY(data);
        }
    }
    
    name.Create("battle");
}
// Destructor
Battle::~Battle()
{
}



bool Battle::Load()
{
    render->camera = { 0, 0 };

    UI = tex->Load("assets/sprites/UI/UI_Text.png");

    // Buttons Principal Menu
    buttons.buttonsMenu.buttonAttack = new GuiButton(1, { 0, 0, 300, 80 }, "Attack");
    buttons.buttonsMenu.buttonAttack->SetObserver(this);
    buttons.buttonsMenu.buttonGuard = new GuiButton(2, { 300, 0, 300, 80 }, "Guard");
    buttons.buttonsMenu.buttonGuard->SetObserver(this);
    buttons.buttonsMenu.buttonSkills = new GuiButton(3, { 600, 0, 300, 80 }, "Skill");
    buttons.buttonsMenu.buttonSkills->SetObserver(this);
    buttons.buttonsMenu.buttonItem = new GuiButton(4, { 0, 80, 300, 80 }, "Items");
    buttons.buttonsMenu.buttonItem->SetObserver(this);
    buttons.buttonsMenu.buttonRun = new GuiButton(5, { 300, 80, 300, 80 }, "Run");
    buttons.buttonsMenu.buttonRun->SetObserver(this);
    buttons.buttonsMenu.buttonBack = new GuiButton(6, { 600, 80, 300, 80 }, "Back");
    buttons.buttonsMenu.buttonBack->SetObserver(this);

    //Buttons Skills
    buttons.buttonsSkills.buttonSkill1 = new GuiButton(7, { 0, 160, 300, 80 }, "Skill 1");
    buttons.buttonsSkills.buttonSkill1->SetObserver(this);
    buttons.buttonsSkills.buttonSkill2 = new GuiButton(8, { 300, 160, 300, 80 }, "Skill 2");
    buttons.buttonsSkills.buttonSkill2->SetObserver(this);
    buttons.buttonsSkills.buttonSkill3 = new GuiButton(9, { 600, 160, 300, 80 }, "Skill 3");
    buttons.buttonsSkills.buttonSkill3->SetObserver(this);
    buttons.buttonsSkills.buttonSkill4 = new GuiButton(10, { 0, 240, 300, 80 }, "Skill 4");
    buttons.buttonsSkills.buttonSkill4->SetObserver(this);
    buttons.buttonsSkills.buttonSkill5 = new GuiButton(11, { 300, 240, 300, 80 }, "Skill 5");
    buttons.buttonsSkills.buttonSkill5->SetObserver(this);
    buttons.buttonsSkills.buttonBack = new GuiButton(12, { 600, 240, 300, 80 }, "Back");
    buttons.buttonsSkills.buttonBack->SetObserver(this);

    //Buttons & Generation Enemies
    srand(time(NULL));
    switch (totalEnemies = rand() % 3)
    {
    case 4:
        entityManager->CreateEntity(EntityType::ENEMY);
        entityManager->entities[1].At(totalEnemies - 4)->data->position = iPoint(300 * 5, 500);

        buttons.buttonsEnemies.buttonEnemy5 = new GuiButton(17, { 300 * 5, 320, 300, 80 }, "Enemy 4");
        buttons.buttonsEnemies.buttonEnemy5->SetObserver(this);
        controllerEnemy[4] = 17;

    case 3:
        entityManager->CreateEntity(EntityType::ENEMY);
        entityManager->entities[1].At(totalEnemies - 3)->data->position = iPoint(300 * 4, 500);

        buttons.buttonsEnemies.buttonEnemy4 = new GuiButton(16, { 300 * 4, 320, 300, 80 }, "Enemy 3");
        buttons.buttonsEnemies.buttonEnemy4->SetObserver(this);
        controllerEnemy[3] = 16;

    case 2:
        entityManager->CreateEntity(EntityType::ENEMY);
        entityManager->entities[1].At(totalEnemies - 2)->data->position = iPoint(300 * 3, 500);

        buttons.buttonsEnemies.buttonEnemy3 = new GuiButton(15, { 300 * 3, 320, 300, 80 }, "Enemy 2");
        buttons.buttonsEnemies.buttonEnemy3->SetObserver(this);
        controllerEnemy[2] = 15;

    case 1:
        entityManager->CreateEntity(EntityType::ENEMY);
        entityManager->entities[1].At(totalEnemies - 1)->data->position = iPoint(300 * 2, 500);

        buttons.buttonsEnemies.buttonEnemy2 = new GuiButton(14, { 300 * 2, 320, 300, 80 }, "Enemy 1");
        buttons.buttonsEnemies.buttonEnemy2->SetObserver(this);
        controllerEnemy[1] = 14;

    case 0:
        entityManager->CreateEntity(EntityType::ENEMY);
        entityManager->entities[1].At(totalEnemies)->data->position = iPoint(300, 500);

        buttons.buttonsEnemies.buttonEnemy1 = new GuiButton(13, { 300, 320, 300, 80 }, "Enemy 0");
        buttons.buttonsEnemies.buttonEnemy1->SetObserver(this);
        controllerEnemy[0] = 13;

    default:
        buttons.buttonsEnemies.buttonBack = new GuiButton(18, { 1000, 600, 300, 80 }, "Back");
        buttons.buttonsEnemies.buttonBack->SetObserver(this);
        controllerEnemy[totalEnemies + 1] = 18;
        break;
    }

    //Render Players
    entityManager->CreateEntity(EntityType::HERO)->position = iPoint(300 / 2, 500);
    entityManager->CreateEntity(EntityType::CAPTAIN)->position = iPoint(300, 500);

    //Calculo de turno
    int playerSPD = 0;
    int enemySPD = 0;

    for (int p = 0; p < entityManager->entities[0].Count(); p++) playerSPD += entityManager->entities[0].At(p)->data->infoEntities.stats.SPD;
    for (int e = 0; e <= totalEnemies; e++) enemySPD += entityManager->entities[1].At(e)->data->infoEntities.stats.SPD;

    if (playerSPD >= enemySPD) playerMenu = true;
    else playerMenu = false;

    //Inicializar variables
    characterTurn = 0;
    chooseMenu = 1;
    f = 0;
    c = 0;

    return false;
}

bool Battle::Update(float dt)
{
    bool ret = false;

    //Evitar el free movement del player
    entityManager->entities[0].At(0)->data->transitioning = true;

    //Player Turn
    if (playerMenu)
    {
        switch (characterTurn)
        {
        //Hero Turn
        case 0:
            PlayerMenu(dt);
            break;

        //Captain Turn
        case 1:
            PlayerMenu(dt);
            break;
        }
    }
    //Enemy Turn
    if (!playerMenu)
    {
        //Attack Players
        for (int p = 0; p < entityManager->entities[0].Count(); p++)
            if (entityManager->entities[0].At(p)->data->infoEntities.attack == true)
            {
                DamagePlayer(p);
                entityManager->entities[0].At(p)->data->infoEntities.attack = false;
            }

        //Enemy Turn
        for (int e = 0; e <= totalEnemies; e++)
        {
            switch (rand() % 3)
            {
                //Attack Hero
            case 0:
                if (entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0) characterTurn = 1;
                else characterTurn = 0;
                break;

                //Attack Captain
            case 1:
            case 2:
                if (entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0) characterTurn = 0;
                else characterTurn = 1;
                break;
            }

            if (entityManager->entities[1].At(e)->data->infoEntities.info.HP > 0) DamageEnemy(e);
        }

        //Death Hero
        if (entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0)
            entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0;
        //Death Captain
        if (entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
            entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0;

        LOG("HP Hero:%d\tHP Captain:%d\n", entityManager->entities[0].At(0)->data->infoEntities.info.HP, entityManager->entities[0].At(1)->data->infoEntities.info.HP);
        for (int e = 0; e <= totalEnemies; e++) 
            if (entityManager->entities[1].At(e)->data->infoEntities.info.HP > 0)
                LOG("HP Enemy %d: %d", totalEnemies - e, entityManager->entities[1].At(e)->data->infoEntities.info.HP);
        LOG("\n");

        //Lose
        if (entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0 &&
            entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
            TransitionToScene(*entityManager->previousScene);

        //Win
        int totalEnemiesHP = 0;
        for (int e = 0; e <= totalEnemies; e++)
        {
            totalEnemiesHP += entityManager->entities[1].At(e)->data->infoEntities.info.HP;
        }
        if (totalEnemiesHP <= 0) LOG("You Win");

        playerMenu = true;
    }

    return ret;
}

bool Battle::Draw()
{
    // BG
    map->Draw(render);

    //Menu
    SDL_Rect rect = { 0, 550, 500, 170 };
    render->DrawTexture(UI, 0, 550, &rect);

    /*rect = { 500, 550, 780, 170 };
    render->DrawTexture(UI, 500, 550, &rect);*/

    //Player
    rect = { 0, 433, 225, 117 };
    render->DrawTexture(UI, 0, 433, &rect);

    rect = { 225, 433, 225, 117 };
    render->DrawTexture(UI, 225, 433, &rect);

    //render->DrawTexture(UI, 0, 0, )

    entityManager->Draw();

    if (playerMenu)
    {
        switch (chooseMenu)
        {
            //Action Draw
        case 1:
            buttons.buttonsMenu.buttonAttack->Draw(render, font);
            buttons.buttonsMenu.buttonGuard->Draw(render, font);
            buttons.buttonsMenu.buttonSkills->Draw(render, font);
            buttons.buttonsMenu.buttonRun->Draw(render, font);
            buttons.buttonsMenu.buttonItem->Draw(render, font);
            buttons.buttonsMenu.buttonBack->Draw(render, font);
            break;

            //Skill Draw
        case 2:
            buttons.buttonsSkills.buttonSkill1->Draw(render, font);
            buttons.buttonsSkills.buttonSkill2->Draw(render, font);
            buttons.buttonsSkills.buttonSkill3->Draw(render, font);
            buttons.buttonsSkills.buttonSkill4->Draw(render, font);
            buttons.buttonsSkills.buttonSkill5->Draw(render, font);
            buttons.buttonsSkills.buttonBack->Draw(render, font);
            break;

            //Enemy Draw
        case 3:
            switch (totalEnemies)
            {
            case 4:
                if (entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.HP > 0)
                    buttons.buttonsEnemies.buttonEnemy5->Draw(render, font);

            case 3:
                if (entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.HP > 0)
                    buttons.buttonsEnemies.buttonEnemy4->Draw(render, font);

            case 2:
                if (entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.HP > 0)
                    buttons.buttonsEnemies.buttonEnemy3->Draw(render, font);

            case 1:
                if (entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.HP > 0)
                    buttons.buttonsEnemies.buttonEnemy2->Draw(render, font);

            case 0:
                if (entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.HP > 0)
                    buttons.buttonsEnemies.buttonEnemy1->Draw(render, font);

            default:
                buttons.buttonsEnemies.buttonBack->Draw(render, font);
                break;
            }
            break;
        }
    }

    return false;
}

bool Battle::Unload()
{
    // Delete buttons and textures
    entityManager->entities[1].Clear();
	
	map->Unload();
    delete map;
    map = nullptr;

    delete buttons.buttonsMenu.buttonAttack;
    buttons.buttonsMenu.buttonAttack = nullptr;
    delete buttons.buttonsMenu.buttonGuard;
    buttons.buttonsMenu.buttonGuard = nullptr;
    delete buttons.buttonsMenu.buttonSkills;
    buttons.buttonsMenu.buttonSkills = nullptr;
    delete buttons.buttonsMenu.buttonRun;
    buttons.buttonsMenu.buttonRun = nullptr;
    delete buttons.buttonsMenu.buttonItem;
    buttons.buttonsMenu.buttonItem = nullptr;
    delete buttons.buttonsMenu.buttonBack;
    buttons.buttonsMenu.buttonBack = nullptr;

    delete buttons.buttonsSkills.buttonSkill1;
    buttons.buttonsSkills.buttonSkill1 = nullptr;
    delete buttons.buttonsSkills.buttonSkill2;
    buttons.buttonsSkills.buttonSkill2 = nullptr;
    delete buttons.buttonsSkills.buttonSkill3;
    buttons.buttonsSkills.buttonSkill3 = nullptr;
    delete buttons.buttonsSkills.buttonSkill4;
    buttons.buttonsSkills.buttonSkill4 = nullptr;
    delete buttons.buttonsSkills.buttonSkill5;
    buttons.buttonsSkills.buttonSkill5 = nullptr;
    delete buttons.buttonsSkills.buttonBack;
    buttons.buttonsSkills.buttonBack = nullptr;

    delete buttons.buttonsEnemies.buttonEnemy5;
    buttons.buttonsEnemies.buttonEnemy5 = nullptr;
    delete buttons.buttonsEnemies.buttonEnemy4;
    buttons.buttonsEnemies.buttonEnemy4 = nullptr;
    delete buttons.buttonsEnemies.buttonEnemy3;
    buttons.buttonsEnemies.buttonEnemy3 = nullptr;
    delete buttons.buttonsEnemies.buttonEnemy2;
    buttons.buttonsEnemies.buttonEnemy2 = nullptr;
    delete buttons.buttonsEnemies.buttonEnemy1;
    buttons.buttonsEnemies.buttonEnemy1 = nullptr;
    delete buttons.buttonsEnemies.buttonBack;
    buttons.buttonsEnemies.buttonBack = nullptr;

    if (entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0)
        entityManager->entities[0].At(0)->data->infoEntities.info.HP = 1;

    if (entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
        entityManager->entities[0].At(1)->data->infoEntities.info.HP = 1;
    return false;
}


void Battle::PlayerMenu(float dt)
{
    GamePad& pad = input->pads[0];

    switch(chooseMenu)
    {
        //Choose Action Menu
    case 1:
        if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN) controllerSkill[f][c++];
        if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN) controllerSkill[f][c--];
        if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN) controllerSkill[f++][c];
        if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN) controllerSkill[f--][c];
        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;
        if (c > 2) c = 0;
        if (c < 0) c = 2;

        //Update Buttons
        buttons.buttonsMenu.buttonAttack->Update(input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonGuard->Update(input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonSkills->Update(input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonRun->Update(input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonItem->Update(input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonBack->Update(input, controllerMenu[f][c], dt);
        break;

        //Choose Skill Menu
    case 2:
        if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN) controllerSkill[f][c++];
        if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN) controllerSkill[f][c--];
        if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN) controllerSkill[f++][c];
        if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN) controllerSkill[f--][c];
        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;
        if (c > 2) c = 0;
        if (c < 0) c = 2;

        //Update Buttons
        buttons.buttonsSkills.buttonSkill1->Update(input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill2->Update(input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill3->Update(input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill4->Update(input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill5->Update(input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonBack->Update(input, controllerSkill[f][c], dt);
        break;

        //Choose Enemy Menu
    case 3:
        if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN) controllerSkill[f++][c];

        //Establecer limites fila/columna botones
        if (f < 0) f = totalEnemies + 1;
        if (f > totalEnemies + 1) f = 0;

        if (f <= totalEnemies && f >= 0 && entityManager->entities[1].At(totalEnemies - f)->data->infoEntities.info.HP <= 0) f++;

        if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        {
            controllerSkill[f--][c];

            if (f < 0) f = totalEnemies + 1;
            if (f > totalEnemies + 1) f = 0;

            if (f <= totalEnemies && f >= 0 && entityManager->entities[1].At(totalEnemies - f)->data->infoEntities.info.HP <= 0) f--;
        }
        
        //Update Buttons
        switch (totalEnemies)
        {
        case 4:
            if (entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy5->Update(input, controllerEnemy[f], dt);

        case 3:
            if (entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy4->Update(input, controllerEnemy[f], dt);

        case 2:
            if (entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy3->Update(input, controllerEnemy[f], dt);

        case 1:
            if (entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy2->Update(input, controllerEnemy[f], dt);

        case 0:
            if (entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy1->Update(input, controllerEnemy[f], dt);

        default:
            buttons.buttonsEnemies.buttonBack->Update(input, controllerEnemy[f], dt);
            break;
        }
        break;
    }
}

void Battle::BattleEscaped()
{
    if (rand() % 6 != 0) TransitionToScene(*entityManager->previousScene);
}

void Battle::DamagePlayer(int player)
{
    int damageDealt = entityManager->entities[0].At(player)->data->infoEntities.stats.ATK +
        rand() % (entityManager->entities[0].At(player)->data->infoEntities.info.LVL) -
        (entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.DEF / 4);

    if (damageDealt <= 0) damageDealt = 0;

    //Enemy Dodge
    if (((entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.SPD -
        entityManager->entities[0].At(player)->data->infoEntities.stats.SPD) /
        (rand() % (200 - entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.LCK) + 1)) >= 1);

    //Player Attack
    else
    {
        //Critical
        if ((((entityManager->entities[0].At(player)->data->infoEntities.stats.SPD / 2) -
            entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.SPD) /
            (rand() % (200 - entityManager->entities[0].At(player)->data->infoEntities.stats.LCK) + 1)) >= 1)
            entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP -= (damageDealt * 2);

        else entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP -= damageDealt;
    }

    entityManager->entities[0].At(player)->data->infoEntities.attack = false;
}

void Battle::ChangeTurns()
{
    chooseMenu = 1;
    switch (characterTurn)
    {
        //Hero Turn
    case 0:
        characterTurn = 1;
        break;

        //Captain Turn
    case 1:
        playerMenu = false;
        characterTurn = 0;
        break;
    }
}

void Battle::DamageEnemy(int enemy)
{
    int damageDealt = entityManager->entities[1].At(enemy)->data->infoEntities.stats.ATK +
        rand() % ((3 * entityManager->entities[1].At(enemy)->data->infoEntities.info.LVL) / 2) -
        (entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.DEF / 4);

    if (damageDealt <= 0) damageDealt = 0;

    //Player Dodge
    if ((((3 * entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.SPD) / 4 -
        entityManager->entities[1].At(enemy)->data->infoEntities.stats.SPD) /
        (rand() % (200 - entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.LCK) + 1)) >= 1);

    //Enemy Attack
    else
    {
        //Player Defense
        if (entityManager->entities[0].At(characterTurn)->data->infoEntities.defense == true) damageDealt = (3 * damageDealt) / 4;

        //Critical
        if ((((entityManager->entities[1].At(enemy)->data->infoEntities.stats.SPD / 2) -
            entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.SPD) /
            (rand() % (200 - entityManager->entities[1].At(enemy)->data->infoEntities.stats.LCK) + 1)) >= 1)
            entityManager->entities[0].At(characterTurn)->data->infoEntities.info.HP -= (damageDealt * 2);

        else entityManager->entities[0].At(characterTurn)->data->infoEntities.info.HP -= damageDealt;
    }
}


//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool Battle::OnGuiMouseClickEvent(GuiControl* control)
{
    //Menu Buttons
    switch (chooseMenu)
    {
    case 1:
        switch (control->id)
        {
        case 1:
            //Ataque
            chooseMenu = 3;
            break;

        case 2:
            //Defensa
            entityManager->entities[0].At(characterTurn)->data->infoEntities.defense = true;
            ChangeTurns();
            break;

        case 3:
            //Skill
            chooseMenu = 2;
            break;

        case 4:
            //Items
            break;

        case 5:
            //Run
            BattleEscaped();
            ChangeTurns();
            break;

        case 6:
            //Back
            switch (characterTurn)
            {
                //Hero Turn
            case 0:
                break;

                //Captain Turn
            case 1:
                characterTurn = 0;
                break;
            }
            break;

        default: break;
        }
        f = 0;
        c = 0;
        
    break;

    //Skills Buttons
    case 2:
        switch (control->id)
        {
        case 7:
            entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[0].picked = true;
            chooseMenu = 3;
            break;

        case 8:
            entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[1].picked = true;
            chooseMenu = 3;
            break;

        case 9:
            entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[2].picked = true;
            chooseMenu = 3;
            break;

        case 10:
            entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[3].picked = true;
            chooseMenu = 3;
            break;

        case 11:
            entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[4].picked = true;
            chooseMenu = 3;
            break;

        case 12:
            //Back
            chooseMenu = 1;
            break;

        default: break;
        }
        f = 0;
        c = 0;
    break;

        //Enemies Buttons
    case 3:
        switch (control->id)
        {
        case 13:
            selectedEnemies[characterTurn] = totalEnemies;
            ChangeTurns();
            entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 14:
            selectedEnemies[characterTurn] = totalEnemies - 1;
            ChangeTurns();
            entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 15:
            selectedEnemies[characterTurn] = totalEnemies - 2;
            ChangeTurns();
            entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 16:
            selectedEnemies[characterTurn] = totalEnemies - 3;
            ChangeTurns();
            entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 17:
            selectedEnemies[characterTurn] = totalEnemies - 4;
            ChangeTurns();
            entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 18:
            //Back
            {
            bool skillPicked = false;
            for (int s = 0; s < 5; s++)
            {
                if (entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked == true)
                    skillPicked = true;
                entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked = false;
            }
            if (skillPicked == true) chooseMenu = 2;
            else chooseMenu = 1;
            } 
            break;

        default: break;
        }
        f = 0;
        c = 0;
    break;

    }

    return true;
}