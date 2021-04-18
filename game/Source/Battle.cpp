#include "Battle.h"

#include "SceneManager.h"
#include "Map.h"

#include "GuiButton.h"

#include <time.h> 
#include "Log.h"



// Constructor

Battle::Battle(SceneManager* sceneManager)
{
    this->sceneManager = sceneManager;

    map = new Map(sceneManager->tex);
    
    name.Create("battle");

    selected = sceneManager->audio->LoadFx("Assets/Audio/Fx/hover_ui.wav");
}
// Destructor
Battle::~Battle()
{
}



bool Battle::Load()
{
    if (sceneManager->toDrawX) sceneManager->toDrawX = false;

    sceneManager->render->camera = { 0, 0 };

    UI = sceneManager->tex->Load("assets/sprites/UI/UI_Text.png");

    if (*sceneManager->entityManager->previousScene == SceneType::CANTINA || *sceneManager->entityManager->previousScene == SceneType::WC)
    {
        if (map->Load("combat_cantina_interior.tmx") == true)
        {
            int w, h;
            uchar* data = NULL;

            RELEASE_ARRAY(data);
        }
    }
    else if (*sceneManager->entityManager->previousScene == SceneType::EXTERIOR)
    {
        if (map->Load("combat_cantina_exterior.tmx") == true)
        {
            int w, h;
            uchar* data = NULL;

            RELEASE_ARRAY(data);
        }
    }

    // Buttons Principal Menu
    buttons.buttonsMenu.buttonAttack = new GuiButton(1, { 10, 560, 160, 75 }, "Attack");
    buttons.buttonsMenu.buttonAttack->SetObserver(this);
    buttons.buttonsMenu.buttonGuard = new GuiButton(2, { 170, 560, 160, 75 }, "Guard");
    buttons.buttonsMenu.buttonGuard->SetObserver(this);
    buttons.buttonsMenu.buttonSkills = new GuiButton(3, { 330, 560, 160, 75 }, "Skill");
    buttons.buttonsMenu.buttonSkills->SetObserver(this);
    buttons.buttonsMenu.buttonItem = new GuiButton(4, { 10, 635, 160, 75 }, "Items");
    buttons.buttonsMenu.buttonItem->SetObserver(this);
    buttons.buttonsMenu.buttonRun = new GuiButton(5, { 170, 635, 160, 75 }, "Run");
    buttons.buttonsMenu.buttonRun->SetObserver(this);
    buttons.buttonsMenu.buttonBack = new GuiButton(6, { 330, 635, 160, 75 }, "Back");
    buttons.buttonsMenu.buttonBack->SetObserver(this);

    //Buttons Skills
    buttons.buttonsSkills.buttonSkill1 = new GuiButton(7, { 511, 560, 253, 75 }, "Skill 1");
    buttons.buttonsSkills.buttonSkill1->SetObserver(this);
    buttons.buttonsSkills.buttonSkill2 = new GuiButton(8, { 764, 560, 253, 75 }, "Skill 2");
    buttons.buttonsSkills.buttonSkill2->SetObserver(this);
    buttons.buttonsSkills.buttonSkill3 = new GuiButton(9, { 1017, 560, 253, 75 }, "Skill 3");
    buttons.buttonsSkills.buttonSkill3->SetObserver(this);
    buttons.buttonsSkills.buttonSkill4 = new GuiButton(10, { 511, 635, 253, 75 }, "Skill 4");
    buttons.buttonsSkills.buttonSkill4->SetObserver(this);
    buttons.buttonsSkills.buttonSkill5 = new GuiButton(11, { 764, 635, 253, 75 }, "Skill 5");
    buttons.buttonsSkills.buttonSkill5->SetObserver(this);
    buttons.buttonsSkills.buttonBack = new GuiButton(12, { 1017, 635, 253, 75 }, "Back");
    buttons.buttonsSkills.buttonBack->SetObserver(this);

    //Buttons & Generation Enemies
    srand(time(NULL));
    switch (totalEnemies = rand() % 3)
    {
    case 4:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->position = iPoint(850, 580);

        buttons.buttonsEnemies.buttonEnemy5 = new GuiButton(17, { 950, 580, 325, 75 }, "Enemy 4");
        buttons.buttonsEnemies.buttonEnemy5->text = sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy5->SetObserver(this);
        controllerEnemy[4] = 17;

    case 3:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->position = iPoint(850, 490);

        buttons.buttonsEnemies.buttonEnemy4 = new GuiButton(16, { 950, 490, 325, 75 }, "Enemy 3");
        buttons.buttonsEnemies.buttonEnemy4->text = sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy4->SetObserver(this);
        controllerEnemy[3] = 16;

    case 2:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->position = iPoint(850, 400);

        buttons.buttonsEnemies.buttonEnemy3 = new GuiButton(15, { 950, 400, 325, 75 }, "Enemy 2");
        buttons.buttonsEnemies.buttonEnemy3->text = sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy3->SetObserver(this);
        controllerEnemy[2] = 15;

    case 1:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->position = iPoint(850, 310);

        buttons.buttonsEnemies.buttonEnemy2 = new GuiButton(14, { 950, 310, 325, 75 }, "Enemy 1");
        buttons.buttonsEnemies.buttonEnemy2->text = sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy2->SetObserver(this);
        controllerEnemy[1] = 14;

    case 0:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies)->data->position = iPoint(850, 220);

        buttons.buttonsEnemies.buttonEnemy1 = new GuiButton(13, { 950, 220, 325, 75 }, "Enemy 0");
        buttons.buttonsEnemies.buttonEnemy1->text = sceneManager->entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy1->SetObserver(this);
        controllerEnemy[0] = 13;

    default:
        buttons.buttonsEnemies.buttonBack = new GuiButton(18, { 1150, 640, 100, 75 }, "Back");
        buttons.buttonsEnemies.buttonBack->SetObserver(this);
        controllerEnemy[totalEnemies + 1] = 18;
        break;
    }

    //Render Players
    sceneManager->entityManager->CreateEntity(EntityType::HERO)->position = iPoint(350, 250);
    sceneManager->entityManager->CreateEntity(EntityType::HERO)->inBattle = true;
    sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->position = iPoint(450, 350);
    sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = true;

    //Calculo de turno
    int playerSPD = 0;
    int enemySPD = 0;

    for (int p = 0; p < sceneManager->entityManager->entities[0].Count(); p++) playerSPD += sceneManager->entityManager->entities[0].At(p)->data->infoEntities.stats.SPD;
    for (int e = 0; e <= totalEnemies; e++) enemySPD += sceneManager->entityManager->entities[1].At(e)->data->infoEntities.stats.SPD;

    if (playerSPD >= enemySPD) playerMenu = true;
    else playerMenu = false;

    //Inicializar variables
    characterTurn = 0;
    chooseMenu = 1;
    f = 0;
    c = 0;

    //audio->PlayMusic("Assets/Audio/Music/battle_music.ogg", 2);

    return false;
}

bool Battle::Update(float dt)
{
    bool ret = false;

    //Evitar el free movement del player
    sceneManager->entityManager->entities[0].At(0)->data->transitioning = true;

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
        for (int p = 0; p < sceneManager->entityManager->entities[0].Count(); p++)
            if (sceneManager->entityManager->entities[0].At(p)->data->infoEntities.attack == true)
            {
                DamagePlayer(p);
                sceneManager->entityManager->entities[0].At(p)->data->infoEntities.attack = false;
            }

        //Enemy Turn
        for (int e = 0; e <= totalEnemies; e++)
        {
            switch (rand() % 3)
            {
                //Attack Hero
            case 0:
                if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0) characterTurn = 1;
                else characterTurn = 0;
                break;

                //Attack Captain
            case 1:
            case 2:
                if (sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0) characterTurn = 0;
                else characterTurn = 1;
                break;
            }

            if (sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP > 0) DamageEnemy(e);
        }

        //Death Hero
        if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0)
            sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0;
        //Death Captain
        if (sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
            sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0;

        LOG("HP Hero:%d\tHP Captain:%d\n", sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP, sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP);
        for (int e = 0; e <= totalEnemies; e++) 
            if (sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP > 0)
                LOG("HP Enemy %d: %d", totalEnemies - e, sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP);
        LOG("\n");

        //Lose
        if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0 &&
            sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
            TransitionToScene(*sceneManager->entityManager->previousScene);

        //Win
        int totalEnemiesHP = 0;
        for (int e = 0; e <= totalEnemies; e++)
        {
            totalEnemiesHP += sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP;
        }
        if (totalEnemiesHP <= 0) LOG("You Win");

        playerMenu = true;
    }

    return ret;
}

bool Battle::Draw()
{
    // BG
    map->Draw(sceneManager->render);

    //Menu
    SDL_Rect rect = { 0, 550, 500, 170 };
    sceneManager->render->DrawTexture(UI, 0, 550, &rect);

    //Player
    rect = { 0, 433, 225, 117 };
    sceneManager->render->DrawTexture(UI, 0, 433, &rect);

    rect = { 225, 433, 225, 117 };
    sceneManager->render->DrawTexture(UI, 225, 433, &rect);

    //render->DrawTexture(UI, 0, 0, )

    sceneManager->entityManager->Draw();

    //Action Draw
    buttons.buttonsMenu.buttonAttack->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonGuard->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonSkills->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonRun->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonItem->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonBack->Draw(sceneManager->render, sceneManager->font);

    //Enemy Draw
    switch (totalEnemies)
    {
    case 4:
        if (sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.HP > 0)
            buttons.buttonsEnemies.buttonEnemy5->Draw(sceneManager->render, sceneManager->font);

    case 3:
        if (sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.HP > 0)
            buttons.buttonsEnemies.buttonEnemy4->Draw(sceneManager->render, sceneManager->font);

    case 2:
        if (sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.HP > 0)
            buttons.buttonsEnemies.buttonEnemy3->Draw(sceneManager->render, sceneManager->font);

    case 1:
        if (sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.HP > 0)
            buttons.buttonsEnemies.buttonEnemy2->Draw(sceneManager->render, sceneManager->font);

    case 0:
        if (sceneManager->entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.HP > 0)
            buttons.buttonsEnemies.buttonEnemy1->Draw(sceneManager->render, sceneManager->font);

    default:
        if(chooseMenu == 3) buttons.buttonsEnemies.buttonBack->Draw(sceneManager->render, sceneManager->font);
        break;
    }

    //Skill Draw
    if (playerMenu == true && chooseMenu == 2)
    {
        rect = { 500, 550, 780, 170 };
        sceneManager->render->DrawTexture(UI, 500, 550, &rect);
        buttons.buttonsSkills.buttonSkill1->Draw(sceneManager->render, sceneManager->font);
        buttons.buttonsSkills.buttonSkill2->Draw(sceneManager->render, sceneManager->font);
        buttons.buttonsSkills.buttonSkill3->Draw(sceneManager->render, sceneManager->font);
        buttons.buttonsSkills.buttonSkill4->Draw(sceneManager->render, sceneManager->font);
        buttons.buttonsSkills.buttonSkill5->Draw(sceneManager->render, sceneManager->font);
        buttons.buttonsSkills.buttonBack->Draw(sceneManager->render, sceneManager->font);
    }

    return false;
}

bool Battle::Unload()
{
    // Delete buttons and textures
    sceneManager->entityManager->DestroyEntity(1);
    sceneManager->entityManager->entities[1].Clear();

    sceneManager->tex->UnLoad(UI);
	
	map->Unload();
    delete map;
    map = nullptr;
    SDL_Color antiBug = { 0, 0, 0, 0 };

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

    switch (totalEnemies)
    {
    case 4:
        delete buttons.buttonsEnemies.buttonEnemy5;
        buttons.buttonsEnemies.buttonEnemy5 = nullptr;
    case 3:
        delete buttons.buttonsEnemies.buttonEnemy4;
        buttons.buttonsEnemies.buttonEnemy4 = nullptr;
    case 2:
        delete buttons.buttonsEnemies.buttonEnemy3;
        buttons.buttonsEnemies.buttonEnemy3 = nullptr;
    case 1:
        delete buttons.buttonsEnemies.buttonEnemy2;
        buttons.buttonsEnemies.buttonEnemy2 = nullptr;
    case 0:
        delete buttons.buttonsEnemies.buttonEnemy1;
        buttons.buttonsEnemies.buttonEnemy1 = nullptr;
    default:
        delete buttons.buttonsEnemies.buttonBack;
        buttons.buttonsEnemies.buttonBack = nullptr;
        break;
    }
    
    if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0)
        sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP = sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxHP;

    if (sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
        sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP = sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxHP;

    sceneManager->entityManager->CreateEntity(EntityType::HERO)->inBattle = false;
    sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = false;

    //*entityManager->previousScene = SceneType::BATTLE;

    return false;
}


void Battle::PlayerMenu(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    switch (chooseMenu)
    {
        //Choose Action Menu
    case 1:
        if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
        {
            controllerSkill[f][c++];
            sceneManager->audio->PlayFx(selected);
        }
        if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
        {
            controllerSkill[f][c--];
            sceneManager->audio->PlayFx(selected);
        }
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        {
            controllerSkill[f++][c];
            sceneManager->audio->PlayFx(selected);
        }
        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        {
            controllerSkill[f--][c];
            sceneManager->audio->PlayFx(selected);
        }
        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;
        if (c > 2) c = 0;
        if (c < 0) c = 2;

        //Update Buttons
        buttons.buttonsMenu.buttonAttack->Update(sceneManager->input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonGuard->Update(sceneManager->input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonSkills->Update(sceneManager->input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonRun->Update(sceneManager->input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonItem->Update(sceneManager->input, controllerMenu[f][c], dt);
        buttons.buttonsMenu.buttonBack->Update(sceneManager->input, controllerMenu[f][c], dt);
        break;

        //Choose Skill Menu
    case 2:
        if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
        {
            controllerSkill[f][c++];
            sceneManager->audio->PlayFx(selected);
        }
        if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
        {
            controllerSkill[f][c--];
            sceneManager->audio->PlayFx(selected);
        }
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        {
            controllerSkill[f++][c];
            sceneManager->audio->PlayFx(selected);
        }
        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        {
            controllerSkill[f--][c];
            sceneManager->audio->PlayFx(selected);
        }
        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;
        if (c > 2) c = 0;
        if (c < 0) c = 2;

        //Rename Buttons
        buttons.buttonsSkills.buttonSkill1->text = sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[0].name;
        buttons.buttonsSkills.buttonSkill2->text = sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[1].name;
        buttons.buttonsSkills.buttonSkill3->text = sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[2].name;
        buttons.buttonsSkills.buttonSkill4->text = sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[3].name;
        buttons.buttonsSkills.buttonSkill5->text = sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[4].name;

        //Update Buttons
        buttons.buttonsSkills.buttonSkill1->Update(sceneManager->input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill2->Update(sceneManager->input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill3->Update(sceneManager->input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill4->Update(sceneManager->input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonSkill5->Update(sceneManager->input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonBack->Update(sceneManager->input, controllerSkill[f][c], dt);
        break;

        //Choose Enemy Menu
    case 3:
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        {
            controllerSkill[f++][c];
            sceneManager->audio->PlayFx(selected);
        }
        //Establecer limites fila/columna botones
        if (f < 0) f = totalEnemies + 1;
        if (f > totalEnemies + 1) f = 0;

        if (f <= totalEnemies && f >= 0 && sceneManager->entityManager->entities[1].At(totalEnemies - f)->data->infoEntities.info.HP <= 0) f++;

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        {
            controllerSkill[f--][c];
            sceneManager->audio->PlayFx(selected);

            if (f < 0) f = totalEnemies + 1;
            if (f > totalEnemies + 1) f = 0;

            if (f <= totalEnemies && f >= 0 && sceneManager->entityManager->entities[1].At(totalEnemies - f)->data->infoEntities.info.HP <= 0) f--;
        }
        
        //Update Buttons
        switch (totalEnemies)
        {
        case 4:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy5->Update(sceneManager->input, controllerEnemy[f], dt);

        case 3:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy4->Update(sceneManager->input, controllerEnemy[f], dt);

        case 2:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy3->Update(sceneManager->input, controllerEnemy[f], dt);

        case 1:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy2->Update(sceneManager->input, controllerEnemy[f], dt);

        case 0:
            if (sceneManager->entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy1->Update(sceneManager->input, controllerEnemy[f], dt);

        default:
            buttons.buttonsEnemies.buttonBack->Update(sceneManager->input, controllerEnemy[f], dt);
            break;
        }
        break;
    }
}

void Battle::BattleEscaped()
{
    if (rand() % 6 != 0) TransitionToScene(*sceneManager->entityManager->previousScene);
}

void Battle::DamagePlayer(int player)
{
    int damageDealt = sceneManager->entityManager->entities[0].At(player)->data->infoEntities.stats.ATK +
        rand() % (sceneManager->entityManager->entities[0].At(player)->data->infoEntities.info.LVL) -
        (sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.DEF / 4);

    if (damageDealt <= 0) damageDealt = 0;

    //Enemy Dodge
    if (((sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.SPD -
        sceneManager->entityManager->entities[0].At(player)->data->infoEntities.stats.SPD) /
        (rand() % (200 - sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.LCK) + 1)) >= 1);

    //Player Attack
    else
    {
        //Critical
        if ((((sceneManager->entityManager->entities[0].At(player)->data->infoEntities.stats.SPD / 2) -
            sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.stats.SPD) /
            (rand() % (200 - sceneManager->entityManager->entities[0].At(player)->data->infoEntities.stats.LCK) + 1)) >= 1)
            sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP -= (damageDealt * 2);

        else sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP -= damageDealt;
    }

    sceneManager->entityManager->entities[0].At(player)->data->infoEntities.attack = false;
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
    int damageDealt = sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.stats.ATK +
        rand() % ((3 * sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.info.LVL) / 2) -
        (sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.DEF / 4);

    if (damageDealt <= 0) damageDealt = 0;

    //Player Dodge
    if ((((3 * sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.SPD) / 4 -
        sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.stats.SPD) /
        (rand() % (200 - sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.LCK) + 1)) >= 1);

    //Enemy Attack
    else
    {
        //Player Defense
        if (sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.defense == true) damageDealt = (3 * damageDealt) / 4;

        //Critical
        if ((((sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.stats.SPD / 2) -
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.stats.SPD) /
            (rand() % (200 - sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.stats.LCK) + 1)) >= 1)
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.info.HP -= (damageDealt * 2);

        else sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.info.HP -= damageDealt;
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
            sceneManager->audio->PlayFx(selected);
            chooseMenu = 3;
            break;

        case 2:
            //Defensa
            sceneManager->audio->PlayFx(selected);
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.defense = true;
            ChangeTurns();
            break;

        case 3:
            //Skill
            sceneManager->audio->PlayFx(selected);
            chooseMenu = 2;
            break;

        case 4:
            //Items
            sceneManager->audio->PlayFx(selected);
            break;

        case 5:
            //Run
            sceneManager->audio->PlayFx(selected);
            BattleEscaped();
            ChangeTurns();
            break;

        case 6:
            //Back
            sceneManager->audio->PlayFx(selected);
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
            sceneManager->audio->PlayFx(selected);
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[0].picked = true;
            chooseMenu = 3;
            break;

        case 8:
            sceneManager->audio->PlayFx(selected);
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[1].picked = true;
            chooseMenu = 3;
            break;

        case 9:
            sceneManager->audio->PlayFx(selected);
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[2].picked = true;
            chooseMenu = 3;
            break;

        case 10:
            sceneManager->audio->PlayFx(selected);
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[3].picked = true;
            chooseMenu = 3;
            break;

        case 11:
            sceneManager->audio->PlayFx(selected);
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[4].picked = true;
            chooseMenu = 3;
            break;

        case 12:
            //Back
            sceneManager->audio->PlayFx(selected);
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
            sceneManager->audio->PlayFx(selected);
            selectedEnemies[characterTurn] = totalEnemies;
            ChangeTurns();
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 14:
            sceneManager->audio->PlayFx(selected);
            selectedEnemies[characterTurn] = totalEnemies - 1;
            ChangeTurns();
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 15:
            sceneManager->audio->PlayFx(selected);
            selectedEnemies[characterTurn] = totalEnemies - 2;
            ChangeTurns();
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 16:
            sceneManager->audio->PlayFx(selected);
            selectedEnemies[characterTurn] = totalEnemies - 3;
            ChangeTurns();
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 17:
            sceneManager->audio->PlayFx(selected);
            selectedEnemies[characterTurn] = totalEnemies - 4;
            ChangeTurns();
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            break;

        case 18:
            //Back
            {
            sceneManager->audio->PlayFx(selected);
            bool skillPicked = false;
            for (int s = 0; s < 5; s++)
            {
                if (sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked == true)
                    skillPicked = true;
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked = false;
            }
            if (skillPicked == true) chooseMenu = 2;
            else chooseMenu = 1;
            } 
            break;

        default: break;
        }
        f = -1;

        //Update Buttons
        switch (totalEnemies)
        {
        case 4:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy5->Update(sceneManager->input, controllerEnemy[f], 0.016f);

        case 3:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy4->Update(sceneManager->input, controllerEnemy[f], 0.016f);

        case 2:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy3->Update(sceneManager->input, controllerEnemy[f], 0.016f);

        case 1:
            if (sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy2->Update(sceneManager->input, controllerEnemy[f], 0.016f);

        case 0:
            if (sceneManager->entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.HP > 0)
                buttons.buttonsEnemies.buttonEnemy1->Update(sceneManager->input, controllerEnemy[f], 0.016f);
        default:
            buttons.buttonsEnemies.buttonBack->Update(sceneManager->input, controllerEnemy[f], 0.016f);
            break;
        }
        f = 0;
        c = 0;
    break;
    }

    return true;
}