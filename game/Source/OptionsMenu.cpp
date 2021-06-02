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
    texture = sceneManager->tex->Load("sprites/ui/ui_menupause.png");

    fullScreen = new GuiCheckBox(1, { 400, 200, 32, 32 }, "Fullscreen", sceneManager->audio);
    fullScreen->SetObserver(this);
    VSync = new GuiCheckBox(2, { 400, 300, 32, 32 }, "VSync", sceneManager->audio);
    VSync->SetObserver(this);
    music = new GuiSlider(3, { 400, 400, 500, 16 }, "Music", sceneManager->audio);
    music->SetObserver(this);
    fx = new GuiSlider(4, { 400, 500, 500, 16 }, "Fx", sceneManager->audio);
    fx->SetObserver(this);
    exit = new GuiButton(5, { 350, 550, 240, 81 }, "Exit game", sceneManager->audio);
    exit->SetObserver(this);

    c = 0;

    return true;
}

bool OptionsMenu::Update(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        c++;

    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        c--;

    //Establecer limites fila/columna botones
    if (sceneManager->currentscenetype != SceneType::TITLE)
    {
        if (c > 4) c = 0;
        if (c < 0) c = 4;
    }
    else
    {
        if (c > 3) c = 0;
        if (c < 0) c = 3;
    }

    fullScreen->Update(sceneManager->input, &sceneManager->fullscreenCheck, buttonOption[c], dt);
    VSync->Update(sceneManager->input, &sceneManager->capped, buttonOption[c], dt);
    music->Update(sceneManager->input, buttonOption[c], dt);
    fx->Update(sceneManager->input, buttonOption[c], dt);
    exit->Update(sceneManager->input, buttonOption[c], dt);

    return true;
}

bool OptionsMenu::Draw()
{
    sceneManager->render->DrawText(sceneManager->font, "Fullscreen", 375, 160, 25, 0, { 255, 255, 255, 255 });
    fullScreen->Draw(sceneManager->render, texture);

    sceneManager->render->DrawText(sceneManager->font, "VSync", 375, 260, 25, 0, { 255, 255, 255, 255 });
    VSync->Draw(sceneManager->render, texture);

    sceneManager->render->DrawText(sceneManager->font, "Music", 375, 360, 25, 0, { 255, 255, 255, 255 });
    music->Draw(sceneManager->render, sceneManager->volumeMusic, texture);

    sceneManager->render->DrawText(sceneManager->font, "Fx", 375, 460, 25, 0, { 255, 255, 255, 255 });
    fx->Draw(sceneManager->render, sceneManager->volumeFx, texture);

    if(sceneManager->currentscenetype != SceneType::TITLE) exit->Draw(sceneManager->render, sceneManager->font);

    /*if (music->state == GuiControlState::PRESSED)
    {
        SDL_Rect rect = { 375, 160, 200, 300 };
        SDL_Color color1 = { 255, 0, 0, 255 };
        SDL_Color color2 = { 0, 255, 0, 255 };
        sceneManager->render->DrawDegradedRectVertical(rect, color1, color2);
    }*/

    return true;
}

bool OptionsMenu::Unload()
{
    sceneManager->tex->UnLoad(optionsText);
    sceneManager->tex->UnLoad(texture);

    sceneManager->openOptions = false;

    fullScreen->UnLoad();
    RELEASE(fullScreen);
    VSync->UnLoad();
    RELEASE(VSync);
    music->UnLoad();
    RELEASE(music);
    fx->UnLoad();
    RELEASE(fx);

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
    case 5: 
        sceneManager->gameIsWorking = false;
    default: break;
    }

    return true;
}