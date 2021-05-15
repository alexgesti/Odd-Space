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
    pause = sceneManager->tex->Load("assets/sprites/UI/UI_MenuPause.png");

    buttonItems = new GuiButton(1, { 150, 109, 240, 81 }, "Items", sceneManager->audio);
    buttonItems->SetObserver(this);
    buttonSkills = new GuiButton(2, { 150, 203, 240, 81 }, "Skills", sceneManager->audio);
    buttonSkills->SetObserver(this);
    buttonSkills->state = GuiControlState::DISABLED;
    buttonEquip = new GuiButton(3, { 110, 297, 240, 81 }, "Equipment", sceneManager->audio);
    buttonEquip->SetObserver(this);
    buttonEquip->state = GuiControlState::DISABLED;
    buttonSettings = new GuiButton(4, { 120, 391, 240, 81 }, "Settings", sceneManager->audio);
    buttonSettings->SetObserver(this);
    buttonSave = new GuiButton(5, { 160, 485, 240, 81 }, "Save", sceneManager->audio);
    buttonSave->SetObserver(this);
    buttonLoad = new GuiButton(6, { 160, 579, 240, 81 }, "Load", sceneManager->audio);
    buttonLoad->SetObserver(this);

    f = 0;

    return true;
}

bool PauseMenu::Update(float dt)
{
    if (!sceneManager->pauseMusicFaded)
    {
        sceneManager->audio->FadeOutMusic(0.5f);
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

    if(sceneManager->openOptions == false) sceneManager->render->DrawText(sceneManager->font, "Pause", 560, 325, 100, 0, { 255, 255, 255, 255 });
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

    delete buttonItems;
    buttonItems = nullptr;
    delete buttonSkills;
    buttonSkills = nullptr;
    delete buttonEquip;
    buttonEquip = nullptr;
    delete buttonSettings;
    buttonSettings = nullptr;
    delete buttonSave;
    buttonSave = nullptr;
    delete buttonLoad;
    buttonLoad = nullptr;

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