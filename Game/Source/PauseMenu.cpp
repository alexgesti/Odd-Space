#include "PauseMenu.h"

#include "SceneManager.h"

// Constructor
PauseMenu::PauseMenu(SceneManager* sceneManager)
{
    this->sceneManager = sceneManager;
}
// Destructor
PauseMenu::~PauseMenu()
{
}



bool PauseMenu::Load()
{
    pause = sceneManager->tex->Load("sprites/ui/ui_menupause.png");
    pauseFx = sceneManager->audio->LoadFx("audio/fx/pause_ui.wav");
   

    buttonItems = new GuiButton(1, { 90, 109, 240, 81 }, "Items", sceneManager->audio);
    buttonItems->SetObserver(this);
    buttonSkills = new GuiButton(2, { 94, 203, 240, 81 }, "Skills", sceneManager->audio);
    buttonSkills->SetObserver(this);
    buttonSkills->disabled = true;
    buttonQuest = new GuiButton(3, { 86, 297, 240, 81 }, "Quest", sceneManager->audio);
    buttonQuest->SetObserver(this);
    buttonSettings = new GuiButton(4, { 88, 391, 240, 81 }, "Settings", sceneManager->audio);
    buttonSettings->SetObserver(this);
    buttonSaveLoad = new GuiButton(5, { 82, 485, 240, 81 }, "Save/Load", sceneManager->audio);
    buttonSaveLoad->SetObserver(this);
    buttonExitMenu = new GuiButton(6, { 90, 579, 240, 81 }, "Exit", sceneManager->audio);
    buttonExitMenu->SetObserver(this);

    buttonSave = new GuiButton(1, { 280, 109, 240, 81 }, "Save", sceneManager->audio);
    buttonSave->SetObserver(this);
    buttonLoad = new GuiButton(2, { 280, 203, 240, 81 }, "Load", sceneManager->audio);
    buttonLoad->SetObserver(this);
    buttonTitle = new GuiButton(1, { 460, 109, 240, 81 }, "Return to Title Screen", sceneManager->audio);
    buttonTitle->SetObserver(this);
    buttonExit = new GuiButton(2, { 330, 203, 240, 81 }, "Exit Game", sceneManager->audio);
    buttonExit->SetObserver(this);

    //if (!sceneManager->savedataexist) buttonSaveLoad->disabled = true;

    f = 0;
    f2 = 0;

    stepedAnimation = new StepedAnimation();
    stepedAnimation->speed = 40.0f;
    stepedAnimation->Pushback(83, 334, 476, 476, 334 - 83, 5);
    stepedAnimation->Pushback(334, 334, 476, 570, 5, 94);
    stepedAnimation->Pushback(339, 83, 570, 570, 334 - 83, 5);
    stepedAnimation->Pushback(83, 83, 570, 476, 5, 94);

    return true;
}

bool PauseMenu::Update(float dt)
{
    if (!sceneManager->pauseMusicFaded)
    {
        sceneManager->audio->PlayFx(pauseFx);
        sceneManager->audio->FadeOutMusic(0.5f, "audio/music/exterior_music.ogg");
        sceneManager->pauseMusicFaded = true;
    }

    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->openOptions)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN 
            || sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN 
            || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            sceneManager->options->Unload();
        else sceneManager->options->Update(dt);
    }
    else if (sceneManager->openItems)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN 
            || sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN 
            || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            sceneManager->items->Unload();
        else sceneManager->items->Update(dt);
    }
    else if (saveloadmenu)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            f++;

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            f--;

        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;

        buttonSave->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonLoad->Update(sceneManager->input, buttonMenuMax[f], dt);

        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN
            || sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN
            || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
        {
            saveloadmenu = !saveloadmenu;
            f = f2;
        }
    }
    else if (questmenu)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN 
            || sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN 
            || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            questmenu = !questmenu;
    }
    else if (exitmenu)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            f++;

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            f--;

        //Establecer limites fila/columna botones
        if (f > 1) f = 0;
        if (f < 0) f = 1;

        buttonTitle->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonExit->Update(sceneManager->input, buttonMenuMax[f], dt);

        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN
            || sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN
            || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
        {
            exitmenu = !exitmenu;
            f = f2;
        }
    }
    else
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            f++;

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            f--;

        //Establecer limites fila/columna botones
        if (f > 5) f = 0;
        if (f < 0) f = 5;

        buttonItems->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonSkills->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonQuest->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonSettings->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonSaveLoad->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonExitMenu->Update(sceneManager->input, buttonMenuMax[f], dt);
    }

    return true;
}

bool PauseMenu::Draw()
{
    SDL_Rect rect = { 1106, 0, 1105, 624 };
    sceneManager->render->DrawTexture(pause, -sceneManager->render->camera.x + 80, -sceneManager->render->camera.y + 50, &rect);

    if (sceneManager->openOptions == false 
        && sceneManager->openItems == false 
        && saveloadmenu == false
        && questmenu == false
        && exitmenu == false)
    {
        //Player
        SDL_Rect face = { 848, 64, 168, 224 };

        sceneManager->render->DrawTexture(pause, -sceneManager->render->camera.x + (rect.w / 3), -sceneManager->render->camera.y + (rect.h / 5), &face);

        std::string name = sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.name.GetString();
        sceneManager->render->DrawText(sceneManager->font, name.c_str(), 32 + rect.w / 2, 48 + (rect.h / 7), 30, 0, { 255, 255, 255, 255 });

        std::string level = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.LVL);
        sceneManager->render->DrawText(sceneManager->font, ("Level " + level).c_str(), 32 + (rect.w / 2), 48 + rect.h / 3.75f, 25, 0, { 255, 255, 255, 255 });

        sceneManager->render->DrawText(sceneManager->font, "Exp. 0 / 100", 32 + rect.w / 2, 48 + (rect.h / 2.5f), 25, 0, { 255, 255, 255, 255 });

        std::string HP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.HP);
        std::string maxHP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxHP);
        sceneManager->render->DrawText(sceneManager->font, ("HP " + HP + " / " + maxHP).c_str(), 32 + (rect.w / 1.25f), 48 + rect.h / 3.75f, 25, 0, { 255, 255, 255, 255 });

        std::string SP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.SP);
        std::string maxSP = std::to_string(sceneManager->entityManager->entities[0].At(0)->data->infoEntities.info.maxSP);
        sceneManager->render->DrawText(sceneManager->font, ("SP " + SP + " / " + maxSP).c_str(), 32 + (rect.w / 1.25f), 48 + rect.h / 2.5f, 25, 0, { 255, 255, 255, 255 });

        //Captain
        face = { 848, 288, 168, 208 };

        sceneManager->render->DrawTexture(pause, -sceneManager->render->camera.x + (rect.w / 3), -sceneManager->render->camera.y + (rect.h / 1.5f), &face);

        name = sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.name.GetString();
        sceneManager->render->DrawText(sceneManager->font, name.c_str(), 32 + rect.w / 2, 48 + (rect.h / 1.7f), 30, 0, { 255, 255, 255, 255 });

        level = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.LVL);
        sceneManager->render->DrawText(sceneManager->font, ("Level " + level).c_str(), 32 + rect.w / 2, 48 + (rect.h / 1.4f), 25, 0, { 255, 255, 255, 255 });

        sceneManager->render->DrawText(sceneManager->font, "Exp. 0 / 100", 32 + rect.w / 2, 48 + (rect.h / 1.2f), 25, 0, { 255, 255, 255, 255 });

        HP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.HP);
        maxHP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxHP);
        sceneManager->render->DrawText(sceneManager->font, ("HP " + HP + " / " + maxHP).c_str(), 32 + rect.w / 1.25f, 48 + (rect.h / 1.4f), 25, 0, { 255, 255, 255, 255 });

        SP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.SP);
        maxSP = std::to_string(sceneManager->entityManager->entities[0].At(1)->data->infoEntities.info.maxSP);
        sceneManager->render->DrawText(sceneManager->font, ("SP " + SP + " / " + maxSP).c_str(), 32 + rect.w / 1.25f, 48 + (rect.h / 1.2f), 25, 0, { 255, 255, 255, 255 });
    }
    sceneManager->render->DrawText(sceneManager->font, "Current", 145, 67, 25, 0, { 255, 255, 255, 255 });
   
    buttonItems->Draw(sceneManager->render, sceneManager->font);
    buttonSkills->Draw(sceneManager->render, sceneManager->font);
    buttonQuest->Draw(sceneManager->render, sceneManager->font);
    buttonSettings->Draw(sceneManager->render, sceneManager->font);
    buttonSaveLoad->Draw(sceneManager->render, sceneManager->font);
    buttonExitMenu->Draw(sceneManager->render, sceneManager->font);

    if (sceneManager->openOptions) sceneManager->options->Draw();
    if (sceneManager->openItems) sceneManager->items->Draw();
    if (saveloadmenu)
    {
        buttonSave->Draw(sceneManager->render, sceneManager->font);
        buttonLoad->Draw(sceneManager->render, sceneManager->font);
    }
    if (exitmenu)
    {
        buttonTitle->Draw(sceneManager->render, sceneManager->font);
        buttonExit->Draw(sceneManager->render, sceneManager->font);
    }
    if (questmenu) sceneManager->questSystem->Draw(sceneManager->render, sceneManager->font);

    if (saveAnimation)
    {
        for (int i = 0; i < stepedAnimation->currentStep; i++)
        {
            SDL_Rect temp = stepedAnimation->GetStep(i);
            sceneManager->render->DrawRectangle(temp, 255, 255, 255, alpha, true, false);
        }

        if (!stepedAnimation->animationCompleted)
        {
            SDL_Rect temp = stepedAnimation->Update();
            sceneManager->render->DrawRectangle(temp, 255, 255, 255, alpha, true, false);
        }

        else alpha -= 3;

        if (stepedAnimation->animationCompleted && alpha < 0)
        {
            saveAnimation = false;
            alpha = 255;
        }
    }

    if (loadAnimation)
    {
        for (int i = 0; i < stepedAnimation->currentStep; i++)
        {
            SDL_Rect temp = stepedAnimation->GetStep(i);
            sceneManager->render->DrawRectangle(temp, 255, 255, 255, alpha, true, false);
        }

        if (!stepedAnimation->animationCompleted)
        {
            SDL_Rect temp = stepedAnimation->Update();
            sceneManager->render->DrawRectangle(temp, 255, 255, 255, alpha, true, false);
        }

        else alpha -= 3;

        if (stepedAnimation->animationCompleted && alpha < 0)
        {
            loadAnimation = false;
            alpha = 255;
        }
    }

    return true;
}

bool PauseMenu::Unload()
{
    sceneManager->tex->UnLoad(pause);

    if (sceneManager->openOptions) sceneManager->options->Unload();
    if (sceneManager->openItems) sceneManager->items->Unload();

    buttonItems->UnLoad();
    RELEASE(buttonItems);
    buttonSkills->UnLoad();
    RELEASE(buttonSkills);
    buttonSettings->UnLoad();
    RELEASE(buttonSettings);
    buttonQuest->UnLoad();
    RELEASE(buttonQuest);
    buttonSaveLoad->UnLoad();
    RELEASE(buttonSaveLoad);
    buttonExitMenu->UnLoad();
    RELEASE(buttonExitMenu);
    buttonSave->UnLoad();
    RELEASE(buttonSave);
    buttonLoad->UnLoad();
    RELEASE(buttonLoad);
    buttonTitle->UnLoad();
    RELEASE(buttonTitle);
    buttonExit->UnLoad();
    RELEASE(buttonExit);
    sceneManager->audio->UnloadFx(pauseFx);
  

    RELEASE(stepedAnimation);

    return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control)
{
    if (saveloadmenu == false && exitmenu == false)
    {
        switch (control->id)
        {
        case 1:
            sceneManager->items->Load();
            sceneManager->openItems = true;
            break;
        case 2:
            break;
        case 3:
            questmenu = true;
            break;
        case 4:
            sceneManager->options->Load();
            sceneManager->openOptions = true;
            break;
        case 5:
            saveloadmenu = true;
            f2 = f;
            break;
        case 6:
            exitmenu = true;
            f2 = f;
            break;
        default: break;
        }
    }
    else if (saveloadmenu)
    {
        switch (control->id)
        {
        case 1:
           sceneManager->saverequested = true;
           saveAnimation = true;
           loadAnimation = false;
           stepedAnimation->Reset();
           stepedAnimation->Pushback(83, 334, 476, 476, 334 - 83, 5);
           stepedAnimation->Pushback(334, 334, 476, 570, 5, 94);
           stepedAnimation->Pushback(339, 83, 570, 570, 334 - 83, 5);
           stepedAnimation->Pushback(83, 83, 570, 476, 5, 94);
           alpha = 255;
            break;
        case 2:
            sceneManager->loadrequested = true;
            saveAnimation = false;
            loadAnimation = true;
            stepedAnimation->Reset();
            stepedAnimation->Pushback(83, 334, 476, 476, 334 - 83, 5);
            stepedAnimation->Pushback(334, 334, 476, 570, 5, 94);
            stepedAnimation->Pushback(339, 83, 570, 570, 334 - 83, 5);
            stepedAnimation->Pushback(83, 83, 570, 476, 5, 94);
            alpha = 255;
            break;
        default:

            break;
        }
    }
    else
    {
        switch (control->id)
        {
        case 1:
            sceneManager->saverequested = true;
            sceneManager->isPause = false;
            sceneManager->current->TransitionToScene(SceneType::TITLE);
            sceneManager->render->camera.x = 0;
            sceneManager->render->camera.y = 0;
            break;
        case 2:

            break;
        default:
            break;
        }
    }

    return true;
}