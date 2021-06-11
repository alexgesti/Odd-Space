#include "Battle.h"

#include "SceneManager.h"
#include "Map.h"

#include "GuiButton.h"

#include "ParticleSystem.h"
#include "Particle.h"

#include <time.h> 
#include "Log.h"

// Constructor
Battle::Battle(SceneManager* sceneManager)
{
    this->sceneManager = sceneManager;

    map = new Map(sceneManager->tex);
    
    name.Create("battle");
}
// Destructor
Battle::~Battle()
{
    Unload();

    map = nullptr;
    sceneManager = nullptr;
    UI = nullptr;
    VorL = nullptr;
    stepedAnimation = nullptr;
}

bool Battle::Load()
{
    sceneManager->entityManager->CreateEntity(EntityType::HERO)->prevPos = sceneManager->entityManager->CreateEntity(EntityType::HERO)->position;
    sceneManager->render->prevCam.x = sceneManager->render->camera.x;
    sceneManager->render->prevCam.y = sceneManager->render->camera.y;

    switch (*sceneManager->entityManager->previousScene)
    {
    case SceneType::CANTINA:
    case SceneType::WC:
        map->Load("combat_cantina_interior.tmx") == true;
        break;
    case SceneType::EXTERIOR:
        map->Load("combat_cantina_exterior.tmx") == true;
        break;
    case SceneType::DUNGEON_EXT:
    case SceneType::DUNGEON_F1:
    case SceneType::DUNGEON_F2:
        map->Load("combat_dungeon.tmx") == true;
        break;
    default: break;
    }

    fx.loseFx = sceneManager->audio->LoadFx("audio/fx/battle_lose.wav");
    fx.winFx = sceneManager->audio->LoadFx("audio/fx/battle_win.wav");
    fx.strikeFx = sceneManager->audio->LoadFx("audio/fx/battle_strike.wav");
    fx.hurtFx = sceneManager->audio->LoadFx("audio/fx/battle_hurt.wav");
    fx.deathFx = sceneManager->audio->LoadFx("audio/fx/battle_death.wav");
    fx.guardFx = sceneManager->audio->LoadFx("audio/fx/battle_guard.wav");
    fx.runFx = sceneManager->audio->LoadFx("audio/fx/battle_run.wav");
    fx.debuffFx = sceneManager->audio->LoadFx("audio/fx/battle_debuff.wav");

    sceneManager->audio->PlayMusic("audio/music/battle_music.ogg", 2);

    if (sceneManager->toDrawX) sceneManager->toDrawX = false;

    sceneManager->render->camera = { 0, 0 };
    sceneManager->render->camera.w = sceneManager->win->screenSurface->w;
    sceneManager->render->camera.h = sceneManager->win->screenSurface->h;

    UI = sceneManager->tex->Load("sprites/ui/ui_text.png");
    VorL = sceneManager->tex->Load("sprites/ui/ui_statebattle.png");

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
        sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->position = iPoint(750, 335);

        buttons.buttonsEnemies.buttonEnemy[4] = new GuiButton(17, { 915, 340, 325, 75 }, "Enemy 4", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[4]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 4)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[4]->SetObserver(this);
        controllerEnemy[4] = 17;

    case 3:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->position = iPoint(750, 205);

        buttons.buttonsEnemies.buttonEnemy[3] = new GuiButton(16, { 915, 210, 325, 75 }, "Enemy 3", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[3]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 3)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[3]->SetObserver(this);
        controllerEnemy[3] = 16;

    case 2:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->position = iPoint(875, 400);

        buttons.buttonsEnemies.buttonEnemy[2] = new GuiButton(15, { 950, 405, 325, 75 }, "Enemy 2", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[2]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 2)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[2]->SetObserver(this);
        controllerEnemy[2] = 15;

    case 1:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->position = iPoint(875, 270);

        buttons.buttonsEnemies.buttonEnemy[1] = new GuiButton(14, { 950, 275, 325, 75 }, "Enemy 1", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[1]->text = sceneManager->entityManager->entities[1].At(totalEnemies - 1)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[1]->SetObserver(this);
        controllerEnemy[1] = 14;

    case 0:
        sceneManager->entityManager->CreateEntity(EntityType::ENEMY);
        sceneManager->entityManager->entities[1].At(totalEnemies)->data->position = iPoint(875, 140);

        buttons.buttonsEnemies.buttonEnemy[0] = new GuiButton(13, { 950, 145, 325, 75 }, "Enemy 0", sceneManager->audio);
        buttons.buttonsEnemies.buttonEnemy[0]->text = sceneManager->entityManager->entities[1].At(totalEnemies)->data->infoEntities.info.name;
        buttons.buttonsEnemies.buttonEnemy[0]->SetObserver(this);
        controllerEnemy[0] = 13;

    default:
        buttons.buttonsEnemies.buttonBack = new GuiButton(18, { 1150, 490, 100, 75 }, "Back", sceneManager->audio);
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

    buttons.buttonsMenu.buttonSkills->disabled = true;

    // Animaciones extras
    stepedAnimation = new StepedAnimation();
    stepedAnimation->speed = 60.0f;
    stepedAnimation->Pushback(7, 486, 557, 557, 1083, 5);
    stepedAnimation->Pushback(486, 486, 557, 708, 5, 572);
    stepedAnimation->Pushback(491, 7, 708, 708, 1103 - 253, 5);
    stepedAnimation->Pushback(7, 7, 708, 557, 5, 94);

    return false;
}

bool Battle::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
    {
        LOG("Smoke emitter init");
        sceneManager->particleSystem->AddEmitter({ 350, 250 }, EmitterData::EmitterType::SMOKE, sceneManager->render);
    }

    if (sceneManager->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
    {
        LOG("Heal emitter init");
        sceneManager->particleSystem->AddEmitter({ 350, 250 }, EmitterData::EmitterType::HEAL, sceneManager->render);
    }

    if (sceneManager->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
    {
        LOG("Smoke emitter init");
        sceneManager->particleSystem->AddEmitter({ 350, 250 }, EmitterData::EmitterType::BLESS, sceneManager->render);
    }


    //Player Turn
    if (playerMenu && !sceneManager->wasBattle)
    {
        switch (characterTurn)
        {
        //Hero Turn
        case 0:
            if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0) characterTurn = 1;
            if (!sceneManager->openItems) PlayerMenu(dt);
            else
            {
                if (sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
                    sceneManager->items->Unload();
                else sceneManager->items->Update(dt);
            }

            break;

        //Captain Turn
        case 1:
            if (sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP <= 0) characterTurn = 0;
            if (!sceneManager->openItems) PlayerMenu(dt);
            else
            {
                if (sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
                    sceneManager->items->Unload();
                else sceneManager->items->Update(dt);
            }

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
                if (sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP <= 0)
                {
                    sceneManager->audio->FadeOutMusic(0.1f, "audio/music/battle_music.ogg");
                    sceneManager->audio->PlayFx(fx.loseFx);
                    sceneManager->wasBattle = true;
                    lose = true;
                    timerequired = 6;
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
                    sceneManager->audio->FadeOutMusic(0.1f, "audio/music/battle_music.ogg");
                    sceneManager->audio->PlayFx(fx.winFx);
                    sceneManager->wasBattle = true;
                    sceneManager->entityManager->CreateEntity(EntityType::RANDITEM);
                    win = true;
                    timerequired = 3;
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
        if (preparetochange >= timerequired)
        {
            if (lose)
            {
                sceneManager->wasBattle = false;
                TransitionToScene(SceneType::ENDDEMO);
            }
            else TransitionToScene(*sceneManager->entityManager->previousScene);
        }
    }

    return ret;
}

bool Battle::Draw()
{
    // BG
    map->Draw(sceneManager->render, sceneManager->drawColliders);

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

    /*for (int i = 0; i < stepedAnimation->currentStep; i++)
    {
        SDL_Rect temp = stepedAnimation->GetStep(i);
        sceneManager->render->DrawRectangle(temp, 255, 255, 255, alpha, true, false);
    }*/

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
            sceneManager->render->DrawText(sceneManager->font, ("What will " + name + " do?").c_str(), 530, 625, 25, 0, { 255, 255, 255, 255 });
        }

        int amountDisapeared = 0;

        for (int i = 0; i < stepedAnimation->currentStep; i++)
        {
            SDL_Rect temp = stepedAnimation->GetStep(i);
            sceneManager->render->DrawRectangle(temp, 255, 255, 255, stepedAnimation->steps[i].alpha, true, false);
            if (stepedAnimation->steps[i].disapear) stepedAnimation->steps[i].alpha -= 3;
            if (stepedAnimation->steps[i].alpha <= 0)
            {
                stepedAnimation->steps[i].alpha = 0;
                stepedAnimation->steps[i].disapear = false;
            }

            if (!stepedAnimation->steps[i].disapear) amountDisapeared++;
        }

        if (!stepedAnimation->animationCompleted)
        {
            SDL_Rect temp = stepedAnimation->Update();
            sceneManager->render->DrawRectangle(temp, 255, 255, 255, 255, true, false);
        }

        else if (amountDisapeared >= stepedAnimation->stepAmount)
        {
            stepedAnimation->Reset();
            stepedAnimation->Pushback(7, 486, 557, 557, 1083, 5);
            stepedAnimation->Pushback(486, 486, 557, 708, 5, 572);
            stepedAnimation->Pushback(491, 7, 708, 708, 1103 - 253, 5);
            stepedAnimation->Pushback(7, 7, 708, 557, 5, 94);
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
    if (lose)
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

    sceneManager->audio->UnloadFx(fx.loseFx);
    sceneManager->audio->UnloadFx(fx.winFx);
    sceneManager->audio->UnloadFx(fx.strikeFx);
    sceneManager->audio->UnloadFx(fx.hurtFx);
    sceneManager->audio->UnloadFx(fx.deathFx);
    sceneManager->audio->UnloadFx(fx.guardFx);
    sceneManager->audio->UnloadFx(fx.runFx);
    sceneManager->audio->UnloadFx(fx.debuffFx);

    buttons.buttonsMenu.buttonAttack->UnLoad();
    RELEASE(buttons.buttonsMenu.buttonAttack);
    buttons.buttonsMenu.buttonGuard->UnLoad();
    RELEASE(buttons.buttonsMenu.buttonGuard);
    buttons.buttonsMenu.buttonSkills->UnLoad();
    RELEASE(buttons.buttonsMenu.buttonSkills);
    buttons.buttonsMenu.buttonRun->UnLoad();
    RELEASE(buttons.buttonsMenu.buttonRun);
    buttons.buttonsMenu.buttonItem->UnLoad();
    RELEASE(buttons.buttonsMenu.buttonItem);
    buttons.buttonsMenu.buttonBack->UnLoad();
    RELEASE(buttons.buttonsMenu.buttonBack);

    for (int bs = 0; bs < 5; bs++)
    {
        buttons.buttonsSkills.buttonSkill[bs]->UnLoad();
        RELEASE(buttons.buttonsSkills.buttonSkill[bs]);
    }
    buttons.buttonsSkills.buttonBack->UnLoad();
    RELEASE(buttons.buttonsSkills.buttonBack);

    for (int be = 0; be <= totalEnemies; be++)
    {
        buttons.buttonsEnemies.buttonEnemy[be]->UnLoad();
        RELEASE(buttons.buttonsEnemies.buttonEnemy[be]);
    }
    buttons.buttonsEnemies.buttonBack->UnLoad();
    RELEASE(buttons.buttonsEnemies.buttonBack);

    sceneManager->entityManager->CreateEntity(EntityType::HERO)->inBattle = false;
    sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = false;
	
    sceneManager->particleSystem->RemoveAllEmitters();

    RELEASE(stepedAnimation);

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

        //Back
        if (sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
        {
            characterTurn = 0;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.attack = false;
            sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.defense = false;
        }

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

        //Back
        if (sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) chooseMenu = 1;

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

        if (sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
        {
            chooseMenu = 1;
            for (int s = 0; s < 5; s++)
            {
                if (sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked == true)
                    chooseMenu = 2;

                sceneManager->entityManager->entities[0].At(characterTurn)->data->infoEntities.skills[s].picked = false;
            }
        }

        break;
    }
}

void Battle::BattleEscaped()
{
    if (rand() % 6 != 0)
    {
        sceneManager->audio->FadeOutMusic(0.1f, "audio/music/battle_music.ogg");
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
            sceneManager->audio->PlayFx(fx.debuffFx);
            sceneManager->particleSystem->AddEmitter({ (float)sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->position.x, (float)sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->position.y }, 
                EmitterData::EmitterType::HEAL, sceneManager->render);
        }

        else
        {
            sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->infoEntities.info.HP -= damageDealt;
            sceneManager->audio->PlayFx(fx.hurtFx);
            sceneManager->particleSystem->AddEmitter({(float)sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->position.x, (float)sceneManager->entityManager->entities[1].At(selectedEnemies[player])->data->position.y }, 
                EmitterData::EmitterType::SMOKE, sceneManager->render);
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
            sceneManager->audio->PlayFx(fx.debuffFx);
            sceneManager->particleSystem->AddEmitter({ (float)sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->position.x, (float)sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->position.y },
                EmitterData::EmitterType::HEAL, sceneManager->render);
        }

        else
        {
            sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->infoEntities.info.HP -= damageDealt;
            sceneManager->audio->PlayFx(fx.hurtFx);
            sceneManager->particleSystem->AddEmitter({ (float)sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->position.x, (float)sceneManager->entityManager->entities[0].At(selectedCharacters[enemy])->data->position.y },
                EmitterData::EmitterType::SMOKE, sceneManager->render);
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
            sceneManager->particleSystem->AddEmitter({ (float)sceneManager->entityManager->entities[0].At(characterTurn)->data->position.x, (float)sceneManager->entityManager->entities[0].At(characterTurn)->data->position.y },
                EmitterData::EmitterType::BLESS, sceneManager->render);
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