#include "Title.h"

#include "SceneManager.h"


// Constructor
Title::Title(SceneManager* sceneManager) : Scene()
{
   this->sceneManager = sceneManager;

    // GUI: Initialize required controls for the screen
}
// Destructor
Title::~Title()
{
}



bool Title::Load()
{
    bgTitle = sceneManager->tex->Load("assets/sprites/MainScreen/title_screen.png");

    // Buttons
    buttons.buttonPlay = new GuiButton(1, { 400, 480, 160, 75 }, "New Game");
    buttons.buttonPlay->SetObserver(this);
    buttons.buttonContinue = new GuiButton(2, { 680, 480, 160, 75 }, "Continue");
    buttons.buttonContinue->SetObserver(this);
    buttons.buttonSettings = new GuiButton(3, { 405, 560, 160, 75 }, "Settings");
    buttons.buttonSettings->SetObserver(this);
    buttons.buttonExit = new GuiButton(4, { 720, 560, 160, 75 }, "Exit");
    buttons.buttonExit->SetObserver(this);


    return false;
}

bool Title::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN) controllerMenu[c++];
    if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN) controllerMenu[c--];
    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN) controllerMenu[f++][c];
    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN) controllerMenu[f--][c];

    if (f > 1) f = 0;
    if (f < 0) f = 1;
    if (c > 1) c = 0;
    if (c < 0) c = 1;

    buttons.buttonPlay->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonContinue->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonSettings->Update(sceneManager->input, controllerMenu[f][c], dt);
    buttons.buttonExit->Update(sceneManager->input, controllerMenu[f][c], dt);
    return ret;
}

bool Title::Draw()
{
    sceneManager->render->DrawTexture(bgTitle, sceneManager->render->camera.x, sceneManager->render->camera.y);

    buttons.buttonPlay->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonContinue->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonSettings->Draw(sceneManager->render, sceneManager->font);
    buttons.buttonExit->Draw(sceneManager->render, sceneManager->font);
    return false;
}

bool Title::Unload()
{
    // Delete buttons and textures
    sceneManager->tex->UnLoad(bgTitle);

    delete buttons.buttonPlay;
    buttons.buttonPlay = nullptr;
    delete buttons.buttonContinue;
    buttons.buttonContinue = nullptr;
    delete buttons.buttonSettings;
    buttons.buttonSettings = nullptr;
    delete buttons.buttonExit;
    buttons.buttonExit = nullptr;
    return false;
}



//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool Title::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->id)
    {
    case 1:
        TransitionToScene(SceneType::EXTERIOR);
        break;
    case 2:
        sceneManager->loadrequested = true;
        break;
    case 3:
        break;
    case 4:
        sceneManager->gameIsWorking = false;
        break;
    default: break;
    }
    return true;
}