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

    if (*sceneManager->entityManager->previousScene == SceneType::CANTINA || *sceneManager->entityManager->previousScene == SceneType::WC)
    {
        if (map->Load("combat_cantina_interior.tmx") == true)
        {
            /*int w, h;
            uchar* data = NULL;

            RELEASE_ARRAY(data);*/
        }
    }
    else if (*sceneManager->entityManager->previousScene == SceneType::EXTERIOR)
    {
        if (map->Load("combat_cantina_exterior.tmx") == true)
        {
            /*int w, h;
            uchar* data = NULL;

            RELEASE_ARRAY(data);*/
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
    fx.loseFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_lose.wav");
    fx.winFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_win.wav");
    fx.strikeFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_strike.wav");
    fx.hurtFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_hurt.wav");
    fx.deathFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_death.wav");
    fx.hpRecoverFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_hp_recover.wav");
    fx.guardFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_guard.wav");
    fx.runFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_run.wav");
    fx.reviveFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_revive.wav");
    fx.spRecoverFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_sp_recover.wav");
    fx.debuffFx = sceneManager->audio->LoadFx("assets/audio/fx/battle_debuff.wav");

    if (sceneManager->toDrawX) sceneManager->toDrawX = false;

    sceneManager->render->camera = { 0, 0 };

    UI = sceneManager->tex->Load("assets/sprites/UI/UI_Text.png");
    VorL = sceneManager->tex->Load("assets/sprites/UI/UI_StateBattle.png");

    // Buttons Principal Menu
    buttons.buttonsMenu.buttonAttack = new GuiButton(1, { 10, 560, 160, 75 }, "Attack", sceneManager->audio);
    buttons.buttonsMenu.buttonAttack->SetObserver(this);
    buttons.buttonsMenu.buttonGuard = new GuiButton(2, { 170, 560, 160, 75 }, "Guard", sceneManager->audio);
    buttons.buttonsMenu.buttonGuard->SetObserver(this);
    buttons.buttonsMenu.buttonSkills = new GuiButton(3, { 330, 560, 160, 75 }, "Skill", sceneManager->audio);
    buttons.buttonsMenu.buttonSkills->SetObserver(this);
    buttons.buttonsMenu.buttonItem = new GuiButton(4, { 10, 635, 160, 75 }, "Items", sceneManager->audio);
    buttons.buttonsMenu.buttonItem->SetObserver(this);
    buttons.buttonsMenu.buttonRun = new GuiButton(5, { 170, 635, 160, 75 }, "Run", sceneManager->audio);
    buttons.buttonsMenu.buttonRun->SetObserver(this);
    buttons.buttonsMenu.buttonBack = new GuiButton(6, { 330, 635, 160, 75 }, "Back", sceneManager->audio);
    buttons.buttonsMenu.buttonBack->SetObserver(this);

    //Buttons Skills
    buttons.buttonsSkills.buttonSkill[0] = new GuiButton(7, { 511, 560, 253, 75 }, "Skill 1", sceneManager->audio);
    buttons.buttonsSkills.buttonSkill[0]->SetObserver(this);
    buttons.buttonsSkills.buttonSkill[1] = new GuiButton(8, { 764, 560, 253, 75 }, "Skill 2", sceneManager->audio);
    buttons.buttonsSkills.buttonSkill[1]->SetObserver(this);
    buttons.buttonsSkills.buttonSkill[2] = new GuiButton(9, { 1017, 560, 253, 75 }, "Skill 3", sceneManager->audio);
    buttons.buttonsSkills.buttonSkill[2]->SetObserver(this);
    buttons.buttonsSkills.buttonSkill[3] = new GuiButton(10, { 511, 635, 253, 75 }, "Skill 4", sceneManager->audio);
    buttons.buttonsSkills.buttonSkill[3]->SetObserver(this);
    buttons.buttonsSkills.buttonSkill[4] = new GuiButton(11, { 764, 635, 253, 75 }, "Skill 5", sceneManager->audio);
    buttons.buttonsSkills.buttonSkill[4]->SetObserver(this);
    buttons.buttonsSkills.buttonBack = new GuiButton(12, { 1017, 635, 253, 75 }, "Back", sceneManager->audio);
    buttons.buttonsSkills.buttonBack->SetObserver(this);

    //Buttons & Generation Enemies
    srand(time(NULL));
    switch (totalEnemies = rand() % 3)
    {
    case 4:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->position = iPoint(850, 580);

        buttons.buttonsEnemies.buttonEnemy[4] = new GuiButton(17, { 950, 580, 325, 75 }, "Enemy 4", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[4]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[4]->SetObserver(this);
        controllerEnemy[4] = 17;

    case 3:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->position = iPoint(850, 490);

        buttons.buttonsEnemies.buttonEnemy[3] = new GuiButton(16, { 950, 490, 325, 75 }, "Enemy 3", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[3]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[3]->SetObserver(this);
        controllerEnemy[3] = 16;

    case 2:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->position = iPoint(850, 400);

        buttons.buttonsEnemies.buttonEnemy[2] = new GuiButton(15, { 950, 400, 325, 75 }, "Enemy 2", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[2]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[2]->SetObserver(this);
        controllerEnemy[2] = 15;

    case 1:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->position = iPoint(850, 310);

        buttons.buttonsEnemies.buttonEnemy[1] = new GuiButton(14, { 950, 310, 325, 75 }, "Enemy 1", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[1]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[1]->SetObserver(this);
        controllerEnemy[1] = 14;

    case 0:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies)->data->position = iPoint(850, 220);

        buttons.buttonsEnemies.buttonEnemy[0] = new GuiButton(13, { 950, 220, 325, 75 }, "Enemy 0", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[0]->text = sceneManager->entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[0]->SetObserver(this);
        controllerEnemy[0] = 13;

    default:
        buttons.buttonsEnemies.buttonBack = new GuiButton(18, { 1150, 640, 100, 75 }, "Back", sceneManager->audio);
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

    for (int p = 0; p < sceneManager->entityManager->entities[0].Count(); p++)
    {
        playerSPD += sceneManager->entityManager->entities[0].At(p)->data->infoEntities.stats.SPD;
        selectedEnemies[p] = totalEnemies;
    }
    for (int e = 0; e <= totalEnemies; e++)
    {
        enemySPD += sceneManager->entityManager->entities[1].At(e)->data->infoEntities.stats.SPD;
        selectedCharacters[e] = -1;
    }

    if (playerSPD >= enemySPD) playerMenu = true;
    else playerMenu = false;

    //Inicializar variables
    characterTurn = 0;
    actualCharacterAnim = 0;
    actualEnemyAnim = 0;
    chooseMenu = 1;
    f = 0;
    c = 0;

    //sceneManager ->audio->PlayMusic("Assets/Audio/Music/battle_music.ogg", 2);

    return false;
}

bool Battle::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    //Evitar el free movement del player
    //sceneManager->entityManager->entities[0].At(0)->data->transitioning = true;

    //Player Turn
    if (playerMenu && win == false && lose == false)
    {
        switch (characterTurn)
        {
        //Hero Turn
        case 0:
            if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0) characterTurn = 1;
            if(!sceneManager->openItems) PlayerMenu(dt);

            if (sceneManager->openItems) sceneManager->items->Update(dt);

            break;

        //Captain Turn
        case 1:
            if (sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0) characterTurn = 0;
            if (!sceneManager->openItems) PlayerMenu(dt);

            if (sceneManager->openItems) sceneManager->items->Update(dt);

            break;
        }
    }
    //Enemy Turn
    if (!playerMenu)
    {
        if (!animation)
        {
            for (int e = 0; e <= totalEnemies; e++)
            {
                if (sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP > 0)
                {
                    switch (rand() % 3)
                    {
                        //Attack Hero
                    case 0:
                        if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0)  selectedCharacters[e] = 1;
                        else  selectedCharacters[e] = 0;
                        break;

                        //Attack Captain
                    case 1:
                    case 2:
                        if (sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)  selectedCharacters[e] = 0;
                        else  selectedCharacters[e] = 1;
                        break;
                    }

                    sceneManager->entityManager->entities[1].At(e)->data->infoEntities.attack = true;
                }
            }

            animation = true;
        }
        else
        {
            //Animation Players
            if (actualCharacterAnim < 2 &&
                sceneManager->entityManager->entities[0].At(actualCharacterAnim)->data->infoEntities.attack == true &&
                sceneManager->entityManager->entities[0].At(actualCharacterAnim)->data->infoEntities.info.HP > 0)
            {
                sceneManager->entityManager->entities[1].At(selectedEnemies[actualCharacterAnim])->data->hurtAnim->Update();
                if (!fx.playOnce)
                {
                    sceneManager->audio->PlayFx(fx.strikeFx, 2);
                    fx.playOnce = true;
                }

                if (sceneManager->entityManager->entities[1].At(selectedEnemies[actualCharacterAnim])->data->hurtAnim->HasFinished() == true)
                {
                    DamagePlayer(actualCharacterAnim);
                    fx.playOnce = false;
                    sceneManager->entityManager->entities[0].At(actualCharacterAnim)->data->infoEntities.attack = false;
                    sceneManager->entityManager->entities[1].At(selectedEnemies[actualCharacterAnim])->data->hurtAnim->Reset();
                    actualCharacterAnim++;
                }
            }
            else if (actualCharacterAnim < 2) actualCharacterAnim++;

            //Animation Enemies
            if (actualEnemyAnim < totalEnemies + 1 && actualCharacterAnim == 2 &&
                sceneManager->entityManager->entities[1].At(actualEnemyAnim)->data->infoEntities.attack == true &&
                sceneManager->entityManager->entities[1].At(actualEnemyAnim)->data->infoEntities.info.HP > 0)
            {
                sceneManager->entityManager->entities[0].At(selectedCharacters[actualEnemyAnim])->data->hurtAnim->Update();
                if (!fx.playOnce)
                {
                    sceneManager->audio->PlayFx(fx.strikeFx, 2);
                    fx.playOnce = true;
                }

                if (sceneManager->entityManager->entities[0].At(selectedCharacters[actualEnemyAnim])->data->hurtAnim->HasFinished() == true)
                {
                    DamageEnemy(actualEnemyAnim);
                    fx.playOnce = false;
                    sceneManager->entityManager->entities[1].At(actualEnemyAnim)->data->infoEntities.attack = false;
                    sceneManager->entityManager->entities[0].At(selectedCharacters[actualEnemyAnim])->data->hurtAnim->Reset();
                    actualEnemyAnim++;
                }
            }
            else if (actualEnemyAnim < totalEnemies + 1 && actualCharacterAnim == 2) actualEnemyAnim++;

            if (actualEnemyAnim == (totalEnemies + 1) && actualCharacterAnim == 2)
            {
                actualCharacterAnim = 0;
                actualEnemyAnim = 0;
                sceneManager->entityManager->entities[0].At(0)->data->infoEntities.defense = false;
                sceneManager->entityManager->entities[0].At(1)->data->infoEntities.defense = false;

                //Console Read
                LOG("HP Hero:%d\tHP Captain:%d\n", sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP, sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP);
                for (int e = 0; e <= totalEnemies; e++)
                    LOG("HP Enemy %d: %d", totalEnemies - e, sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP);
                LOG("\n");

                //Lose Condition
                if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0 &&
                    sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
                {
                    sceneManager->audio->PlayFx(fx.loseFx);
                    sceneManager->wasBattle = true;
                    lose = true;
                }

                //Win Condition
                int totalEnemiesHP = 0;
                for (int e = 0; e <= totalEnemies; e++)
                {
                    totalEnemiesHP += sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP;
                    if (sceneManager->entityManager->entities[1].At(e)->data->infoEntities.info.HP > 0) break;
                }
                if (totalEnemiesHP <= 0)
                {
                    sceneManager->audio->PlayFx(fx.winFx);
                    sceneManager->wasBattle = true;
                    sceneManager->entityManager->CreateEntity(EntityType::ITEM);
                    win = true;
                }

                animation = false;
                playerMenu = true;
            }
        }
    }

    if (sceneManager->wasBattle == true)
    {
        LOG("%f", preparetochange);
        preparetochange += dt;
        if (preparetochange >= 6)
        {
            TransitionToScene(*sceneManager->entityManager->previousScene);
        }
    }

    return ret;
}

bool Battle::Draw()
{
    // BG
    map->Draw(sceneManager->render);

    sceneManager->entityManager->Draw();

    //Menu
    SDL_Rect rect = { 0, 550, 500, 170 };
    sceneManager->render->DrawTexture(UI, 0, 550, &rect);

    rect = { 500, 550, 780, 170 };
    sceneManager->render->DrawTexture(UI, 500, 550, &rect);

    //Player
    rect = { 0, 433, 225, 117 };
    sceneManager->render->DrawTexture(UI, 0, 433, &rect);

    rect = { 225, 433, 225, 117 };
    sceneManager->render->DrawTexture(UI, 225, 433, &rect);

    for (int p = 0; p < sceneManager->entityManager->entities[0].Count(); p++)
    {
        //NAME
        std::string name = sceneManager->entityManager->entities[0].At(p)->data->infoEntities.info.name.GetString();
        sceneManager->render->DrawText(sceneManager->font, name.c_str(), 15 + (225 * p), 448, 25, 0, { 255, 255, 255, 255 });
        //HP
        std::string HP = std::to_string(sceneManager->entityManager->entities[0].At(p)->data->infoEntities.info.HP);
        std::string maxHP = std::to_string(sceneManager->entityManager->entities[0].At(p)->data->infoEntities.info.maxHP);
        sceneManager->render->DrawText(sceneManager->font, ("HP: " + HP + " / " + maxHP).c_str(), 15 + (225 * p), 493, 20, 0, { 255, 255, 255, 255 });
        //SP
        std::string SP = std::to_string(sceneManager->entityManager->entities[0].At(p)->data->infoEntities.info.SP);
        std::string maxSP = std::to_string(sceneManager->entityManager->entities[0].At(p)->data->infoEntities.info.maxSP);
        sceneManager->render->DrawText(sceneManager->font, ("SP: " + SP + " / " + maxSP).c_str(), 15 + (225 * p), 518, 20, 0, { 255, 255, 255, 255 });

    }

    //Action Draw
    buttons.buttonsMenu.buttonAttack->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonGuard->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonSkills->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonRun->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonItem->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonsMenu.buttonBack->Draw(sceneManager->render, sceneManager->font);

    //Enemy Draw
    for (int be = 0; be <= totalEnemies; be++)
        if (sceneManager->entityManager->entities[1].At(totalEnemies - be)->data->infoEntities.info.HP > 0)
            buttons.buttonsEnemies.buttonEnemy[be]->Draw(sceneManager->render, sceneManager->font);
    if (chooseMenu == 3) buttons.buttonsEnemies.buttonBack->Draw(sceneManager->render, sceneManager->font);

    //Draw text aux window
    if (playerMenu == true)
    {
        //Skill Draw
        if (chooseMenu == 2)
        {
            for (int bs = 0; bs < 5; bs++)
                buttons.buttonsSkills.buttonSkill[bs]->Draw(sceneManager->render, sceneManager->font);
            buttons.buttonsSkills.buttonBack->Draw(sceneManager->render, sceneManager->font);
        }
        //Draw update text
        else
        {
            std::string name = sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.info.name.GetString();
            sceneManager->render->DrawText(sceneManager->font, ("What will do " + name + " ?").c_str(), 530, 625, 25, 0, { 255, 255, 255, 255 });
        }
    }
    else
    {
        if (actualCharacterAnim < 2 && actualEnemyAnim == 0)
        {
            std::string namePlayer = sceneManager->entityManager->entities[0].At(actualCharacterAnim)->data->infoEntities.info.name.GetString();
            std::string nameEnemy = sceneManager->entityManager->entities[1].At(selectedEnemies[actualCharacterAnim])->data->infoEntities.info.name.GetString();
            sceneManager->render->DrawText(sceneManager->font, (namePlayer + " has attacked " + nameEnemy).c_str(), 530, 625, 25, 0, { 255, 255, 255, 255 });
        }
        else if (actualCharacterAnim == 2 && actualEnemyAnim < totalEnemies + 1)
        {
            std::string nameEnemy = sceneManager->entityManager->entities[1].At(actualEnemyAnim)->data->infoEntities.info.name.GetString();
            std::string namePlayer = sceneManager->entityManager->entities[0].At(selectedCharacters[actualEnemyAnim])->data->infoEntities.info.name.GetString();
            sceneManager->render->DrawText(sceneManager->font, (nameEnemy + " has attacked " + namePlayer).c_str(), 530, 625, 25, 0, { 255, 255, 255, 255 });
        }
    }

    if (sceneManager->openItems) sceneManager->items->Draw();

    if (win)
    {
        rect = {0, 0, 480, 240};
        sceneManager->render->DrawTexture(VorL, 640 - (rect.w / 2), 0, &rect);
    }
    else if (lose)
    {
        rect = {0, 240, 480, 192};
        sceneManager->render->DrawTexture(VorL, 640 - (rect.w / 2) + 70, 0, &rect);
    }

    return false;
}

bool Battle::Unload()
{
    // Delete buttons and textures
    sceneManager->entityManager->DestroyEntity(1);
    sceneManager->entityManager->entities[1].Clear();

    sceneManager->tex->UnLoad(UI);

    if (sceneManager->openItems) sceneManager->items->Unload();
	
	map->Unload();
    RELEASE(map);
    //delete map;
    //map = nullptr;

    //delete buttons.buttonsMenu.buttonAttack;
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonAttack->hover);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonAttack->press);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonAttack->unavaliable);
    RELEASE(buttons.buttonsMenu.buttonAttack);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonGuard->hover);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonGuard->press);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonGuard->unavaliable);
    RELEASE(buttons.buttonsMenu.buttonGuard);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonSkills->hover);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonSkills->press);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonSkills->unavaliable);
    RELEASE(buttons.buttonsMenu.buttonSkills);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonRun->hover);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonRun->press);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonRun->unavaliable);
    RELEASE(buttons.buttonsMenu.buttonRun);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonItem->hover);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonItem->press);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonItem->unavaliable);
    RELEASE(buttons.buttonsMenu.buttonItem);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonBack->hover);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonBack->press);
    sceneManager->audio->UnloadFx(buttons.buttonsMenu.buttonBack->unavaliable);
    RELEASE(buttons.buttonsMenu.buttonBack);
    //buttons.buttonsMenu.buttonAttack = nullptr;
    //delete buttons.buttonsMenu.buttonGuard;
    //buttons.buttonsMenu.buttonGuard = nullptr;
    //delete buttons.buttonsMenu.buttonSkills;
    //buttons.buttonsMenu.buttonSkills = nullptr;
    //delete buttons.buttonsMenu.buttonRun;
    //buttons.buttonsMenu.buttonRun = nullptr;
    //delete buttons.buttonsMenu.buttonItem;
    //buttons.buttonsMenu.buttonItem = nullptr;
    //delete buttons.buttonsMenu.buttonBack;
    //buttons.buttonsMenu.buttonBack = nullptr;

    for (int bs = 0; bs < 5; bs++)
    {
        //delete buttons.buttonsSkills.buttonSkill[bs];
        //buttons.buttonsSkills.buttonSkill[bs] = nullptr;
        sceneManager->audio->UnloadFx(buttons.buttonsSkills.buttonSkill[bs]->hover);
        sceneManager->audio->UnloadFx(buttons.buttonsSkills.buttonSkill[bs]->press);
        sceneManager->audio->UnloadFx(buttons.buttonsSkills.buttonSkill[bs]->unavaliable);
        RELEASE(buttons.buttonsSkills.buttonSkill[bs]);
    }
    sceneManager->audio->UnloadFx(buttons.buttonsSkills.buttonBack->hover);
    RELEASE(buttons.buttonsSkills.buttonBack);
    //delete buttons.buttonsSkills.buttonBack;
    //buttons.buttonsSkills.buttonBack = nullptr;

    for (int be = 0; be <= totalEnemies; be++)
    {
        //delete buttons.buttonsEnemies.buttonEnemy[be];
        //buttons.buttonsEnemies.buttonEnemy[be] = nullptr;
        sceneManager->audio->UnloadFx(buttons.buttonsEnemies.buttonEnemy[be]->hover);
        sceneManager->audio->UnloadFx(buttons.buttonsEnemies.buttonEnemy[be]->press);
        sceneManager->audio->UnloadFx(buttons.buttonsEnemies.buttonEnemy[be]->unavaliable);
        RELEASE(buttons.buttonsEnemies.buttonEnemy[be]);
    }
    sceneManager->audio->UnloadFx(buttons.buttonsEnemies.buttonBack->hover);
    RELEASE(buttons.buttonsEnemies.buttonBack);
    //delete buttons.buttonsEnemies.buttonBack;
    //buttons.buttonsEnemies.buttonBack = nullptr;
    
    if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0)
        sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP = sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxHP;

    if (sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0)
        sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP = sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxHP;

    sceneManager->entityManager->CreateEntity(EntityType::HERO)->inBattle = false;
    sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = false;
	
    //*entityManager->previousScene = SceneType::BATTLE;

    sceneManager->audio->UnloadFx(fx.deathFx);
    sceneManager->audio->UnloadFx(fx.runFx);
    sceneManager->audio->UnloadFx(fx.strikeFx);
    sceneManager->audio->UnloadFx(fx.loseFx);
    sceneManager->audio->UnloadFx(fx.winFx);
    sceneManager->audio->UnloadFx(fx.guardFx);
    sceneManager->audio->UnloadFx(fx.hurtFx);
    sceneManager->audio->UnloadFx(fx.reviveFx);
    sceneManager->audio->UnloadFx(fx.hpRecoverFx);

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
            controllerSkill[f][c++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
            controllerSkill[f][c--];

        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            controllerSkill[f++][c];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            controllerSkill[f--][c];

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
            controllerSkill[f][c++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
            controllerSkill[f][c--];

        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            controllerSkill[f++][c];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            controllerSkill[f--][c];

        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;
        if (c > 2) c = 0;
        if (c < 0) c = 2;

        //Rename Buttons
        for (int bs = 0; bs < 5; bs++)
            buttons.buttonsSkills.buttonSkill[bs]->text = sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[bs].name;

        //Update Buttons
        for (int bs = 0; bs < 5; bs++)
            buttons.buttonsSkills.buttonSkill[bs]->Update(sceneManager->input, controllerSkill[f][c], dt);
        buttons.buttonsSkills.buttonBack->Update(sceneManager->input, controllerSkill[f][c], dt);
        break;

        //Choose Enemy Menu
    case 3:
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            controllerSkill[f++][c];

        //Establecer limites fila/columna botones
        if (f < 0) f = totalEnemies + 1;
        if (f > totalEnemies + 1) f = 0;

        if (f <= totalEnemies && f >= 0 && sceneManager->entityManager->entities[1].At(totalEnemies - f)->data->infoEntities.info.HP <= 0) f++;

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        {
            controllerSkill[f--][c];

            if (f < 0) f = totalEnemies + 1;
            if (f > totalEnemies + 1) f = 0;

            if (f <= totalEnemies && f >= 0 && sceneManager->entityManager->entities[1].At(totalEnemies - f)->data->infoEntities.info.HP <= 0) f--;
        }
        
        //Update Buttons
        for (int be = 0; be <= totalEnemies; be++)
            buttons.buttonsEnemies.buttonEnemy[be]->Update(sceneManager->input, controllerEnemy[f], dt);
        buttons.buttonsEnemies.buttonBack->Update(sceneManager->input, controllerEnemy[f], dt);
        break;
    }
}

void Battle::BattleEscaped()
{
    if (rand() % 6 != 0)
    {
        sceneManager->audio->PlayFx(fx.runFx);
        sceneManager->entityManager->entities[0].At(0)->data->infoEntities.defense = false;
        sceneManager->entityManager->entities[0].At(1)->data->infoEntities.defense = false;
        sceneManager->wasBattle = true;
        TransitionToScene(*sceneManager->entityManager->previousScene);
    }
    else ChangeTurns();
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
        {
            sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP -= (damageDealt * 2);
            sceneManager->audio->PlayFx(fx.spRecoverFx);
        }

        else
        {
            sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP -= damageDealt;
            sceneManager->audio->PlayFx(fx.hurtFx);

        }
    }

    if (sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP <= 0)
	{
        sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP = 0;
		sceneManager->audio->PlayFx(fx.deathFx);
	}
}

void Battle::ChangeTurns()
{
    chooseMenu = 1;
    switch (characterTurn)
    {
        //Hero Turn
    case 0:
        if(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0) playerMenu = false;
        else characterTurn = 1;
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
        (sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.stats.DEF / 4);

    if (damageDealt <= 0) damageDealt = 0;

    //Player Dodge
    if ((((3 * sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.stats.SPD) / 4 -
        sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.stats.SPD) /
        (rand() % (200 - sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.stats.LCK) + 1)) >= 1);

    //Enemy Attack
    else
    {
        //Player Defense
        if (sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.defense == true) damageDealt = (3 * damageDealt) / 4;

        //Critical
        if ((((sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.stats.SPD / 2) -
            sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.stats.SPD) /
            (rand() % (200 - sceneManager->entityManager->entities[1].At(enemy)->data->infoEntities.stats.LCK) + 1)) >= 1)
        {
            sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.info.HP -= (damageDealt * 2);
            sceneManager->audio->PlayFx(fx.spRecoverFx);

        }

        else
        {
            sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.info.HP -= damageDealt;
            sceneManager->audio->PlayFx(fx.hurtFx);
        }

    }

    if (sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.info.HP <= 0)
    {
        sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.info.HP = 0;
        sceneManager->audio->PlayFx(fx.deathFx);
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
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.defense = true;
            sceneManager->audio->PlayFx(fx.guardFx);
            ChangeTurns();
            break;

        case 3:
            //Skill
            chooseMenu = 2;
            break;

        case 4:
            //Items
            sceneManager->items->Load();
            sceneManager->openItems = true;
            break;

        case 5:
            //Run
            BattleEscaped();
            break;

        case 6:
            //Back
            characterTurn = 0;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = false;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.defense = false;
            break;

        default: break;
        }
        f = 0;
        c = 0;
        break;

    //Skills Buttons
    case 2:
        switch (characterTurn)
        {
        case 0:
            switch (control->id)
            {
            case 7://debuff
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[0].picked = true;
                chooseMenu = 3;
                sceneManager->audio->PlayFx(fx.debuffFx);
                break;

            case 8:
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[1].picked = true;
                chooseMenu = 3;
                break;

            case 9://hp recover
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[2].picked = true;
                chooseMenu = 3;
                sceneManager->audio->PlayFx(fx.hpRecoverFx);
                break;

            case 10:
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[3].picked = true;
                chooseMenu = 3;
                break;

            case 11://revive
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[4].picked = true;
                chooseMenu = 3;
                sceneManager->audio->PlayFx(fx.reviveFx);
                break;

            case 12:
                //Back
                chooseMenu = 1;
                break;

            default: break;
            }
            break;

        case 1:
            switch (control->id)
            {
            case 7:
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[0].picked = true;
                chooseMenu = 3;
                break;

            case 8:
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[1].picked = true;
                chooseMenu = 3;
                break;

            case 9:
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[2].picked = true;
                chooseMenu = 3;
                break;

            case 10:
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[3].picked = true;
                chooseMenu = 3;
                break;

            case 11:
                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[4].picked = true;
                chooseMenu = 3;
                break;

            case 12:
                //Back
                chooseMenu = 1;
                break;

            default: break;
            }
            break;
        f = 0;
        c = 0;
        break;
        }

        //Enemies Buttons
    case 3:
        switch (control->id)
        {
        case 13:
            selectedEnemies[characterTurn] = totalEnemies;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            ChangeTurns();
            break;

        case 14:
            selectedEnemies[characterTurn] = totalEnemies - 1;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            ChangeTurns();
            break;

        case 15:
            selectedEnemies[characterTurn] = totalEnemies - 2;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            ChangeTurns();
            break;

        case 16:
            selectedEnemies[characterTurn] = totalEnemies - 3;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            ChangeTurns();
            break;

        case 17:
            selectedEnemies[characterTurn] = totalEnemies - 4;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = true;
            ChangeTurns();
            break;

        case 18:
            //Back
            chooseMenu = 1;
            for (int s = 0; s < 5; s++)
            {
                if (sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked == true)
                    chooseMenu = 2;

                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked = false;
            }
            break;

        default: break;
        }
        f = -1;

        //Update buttons to make them white again
        for (int be = 0; be <= totalEnemies; be++)
            buttons.buttonsEnemies.buttonEnemy[be]->Update(sceneManager->input, controllerEnemy[f], 0.016f);
        f = 0;
        c = 0;
        break;
    }

    return true;
}