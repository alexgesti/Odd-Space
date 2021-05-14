#include "OptionsMenu.h"

#include "SceneManager.h"

// Constructor
OptionsMenu::OptionsMenu(SceneManager* sceneManager)
{
    this->sceneManager = sceneManager;
}
// Destructor
OptionsMenu::~OptionsMenu()
{
}



bool OptionsMenu::Load()
{
    fullScreen = new GuiCheckBox(1, { 150, 109, 240, 81 }, "Fullscreen", sceneManager->audio);
    fullScreen->SetObserver(this);
    VSync = new GuiCheckBox(2, { 150, 109, 240, 81 }, "VSync", sceneManager->audio);
    VSync->SetObserver(this);
    music = new GuiSlider(3, { 150, 109, 240, 81 }, "Music", sceneManager->audio);
    music->SetObserver(this);
    fx = new GuiSlider(4, { 150, 109, 240, 81 }, "Fx ", sceneManager->audio);
    fx->SetObserver(this);

    f = 0;

    return true;
}

bool OptionsMenu::Update(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        f++;

    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        f--;

    //Establecer limites fila/columna botones
    if (f > 4) f = 0;
    if (f < 0) f = 4;

    fullScreen->Update(sceneManager->input, buttonOption[f], dt);
    VSync->Update(sceneManager->input, buttonOption[f], dt);
    music->Update(sceneManager->input, buttonOption[f], dt);
    fx->Update(sceneManager->input, buttonOption[f], dt);

    return true;
}

bool OptionsMenu::Draw()
{
    SDL_Rect options = { -sceneManager->render->camera.x + 345, -sceneManager->render->camera.y + 111, 830, 553 };
    sceneManager->render->DrawRectangle(options, 0, 0, 255, 255);

    fullScreen->Draw(sceneManager->render);
    VSync->Draw(sceneManager->render);
    music->Draw(sceneManager->render, sceneManager->volumeMusic);
    fx->Draw(sceneManager->render, sceneManager->volumeFx);

    return true;
}

bool OptionsMenu::Unload()
{
    sceneManager->tex->UnLoad(optionsText);

    sceneManager->openOptions = false;

    delete fullScreen;
    fullScreen = nullptr;
    delete VSync;
    VSync = nullptr;
    delete music;
    music = nullptr;
    delete fx;
    fx = nullptr;

    return true;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool OptionsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
    GamePad& pad = sceneManager->input->pads[0];

    switch (control->id)
    {
    case 1:
        sceneManager->win->ToggleFullscreen(sceneManager->win->window);
        break;
    case 2:
        sceneManager->capped = !sceneManager->capped;
        break;
    case 3:
        if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
            if (sceneManager->volumeMusic > 0) sceneManager->volumeMusic -= 32;
        if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
            if (sceneManager->volumeMusic < 128) sceneManager->volumeMusic += 32;
        Mix_VolumeMusic(sceneManager->volumeMusic);
        break;
    case 4:
        if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
            if (sceneManager->volumeFx > 0) sceneManager->volumeFx -= 32;
        if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
            if (sceneManager->volumeFx < 128) sceneManager->volumeFx += 32;
        Mix_Volume(-1, sceneManager->volumeFx);
        break;
    default: break;
    }

    return true;
}