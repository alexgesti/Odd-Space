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
    unPauseFx = sceneManager->audio->LoadFx("audio/fx/unpause_ui.wav");

    buttonItems = new GuiButton(1, { 90, 109, 240, 81 }, "Items", sceneManager->audio);
    buttonItems->SetObserver(this);
    buttonSkills = new GuiButton(2, { 90, 203, 240, 81 }, "Skills", sceneManager->audio);
    buttonSkills->SetObserver(this);
    buttonSkills->disabled = true;
    buttonEquip = new GuiButton(3, { 90, 297, 240, 81 }, "Equipment", sceneManager->audio);
    buttonEquip->SetObserver(this);
    buttonEquip->disabled = true;
    buttonSettings = new GuiButton(4, { 90, 391, 240, 81 }, "Settings", sceneManager->audio);
    buttonSettings->SetObserver(this);
    buttonSave = new GuiButton(5, { 90, 485, 240, 81 }, "Save", sceneManager->audio);
    buttonSave->SetObserver(this);
    buttonLoad = new GuiButton(6, { 90, 579, 240, 81 }, "Load", sceneManager->audio);
    buttonLoad->SetObserver(this);

    f = 0;

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
        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            sceneManager->options->Unload();
        else sceneManager->options->Update(dt);
    }
    else if (sceneManager->openItems)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            sceneManager->items->Unload();
        else sceneManager->items->Update(dt);
        //sceneManager->entityManager->CreateEntity(EntityType::RANDITEM);
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
        buttonEquip->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonSettings->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonSave->Update(sceneManager->input, buttonMenuMax[f], dt);
        buttonLoad->Update(sceneManager->input, buttonMenuMax[f], dt);
    }

    return true;
}

bool PauseMenu::Draw()
{
    SDL_Rect rect = { 1106, 0, 1105, 624 };
    sceneManager->render->DrawTexture(pause, -sceneManager->render->camera.x + 80, -sceneManager->render->camera.y + 50, &rect);

    if (sceneManager->openOptions == false && sceneManager->openItems == false)
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
    buttonEquip->Draw(sceneManager->render, sceneManager->font);
    buttonSettings->Draw(sceneManager->render, sceneManager->font);
    buttonSave->Draw(sceneManager->render, sceneManager->font);
    buttonLoad->Draw(sceneManager->render, sceneManager->font);

    if (sceneManager->openOptions) sceneManager->options->Draw();
    if (sceneManager->openItems) sceneManager->items->Draw();

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
    buttonEquip->UnLoad();
    RELEASE(buttonEquip);
    buttonSettings->UnLoad();
    RELEASE(buttonSettings);
    buttonSave->UnLoad();
    RELEASE(buttonSave);
    buttonLoad->UnLoad();
    RELEASE(buttonLoad);
    sceneManager->audio->UnloadFx(pauseFx);
    sceneManager->audio->UnloadFx(unPauseFx);
    return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control)
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
        break;
    case 4: 
        sceneManager->options->Load();
        sceneManager->openOptions = true;
        break;
    case 5: 
        sceneManager->saverequested = true;
        break;
    case 6: 
        sceneManager->loadrequested = true;
        break;
    default: break;
    }

    return true;
}