#include "Title.h"


#include "GuiButton.h"
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
    buttons.buttonPlay = new GuiButton(1, { 10, 560, 160, 75 }, "Play");
    buttons.buttonPlay->SetObserver(this);
    buttons.buttonContinue = new GuiButton(2, { 200, 560, 160, 75 }, "Continue");
    buttons.buttonContinue->SetObserver(this);
    buttons.buttonSettings = new GuiButton(3, { 400, 560, 160, 75 }, "Settings");
    buttons.buttonSettings->SetObserver(this);
    buttons.buttonExit = new GuiButton(4, { 600, 560, 160, 75 }, "Exit");
    buttons.buttonExit->SetObserver(this);


    return false;
}

bool Title::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN) controllerMenu[c++];
    if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN) controllerMenu[c--];
   
    buttons.buttonPlay->Update(sceneManager->input, controllerMenu[c], dt);
    buttons.buttonContinue->Update(sceneManager->input, controllerMenu[c], dt);
    buttons.buttonSettings->Update(sceneManager->input, controllerMenu[c], dt);
    buttons.buttonExit->Update(sceneManager->input, controllerMenu[c], dt);
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
    {
        TransitionToScene(SceneType::EXTERIOR);
        break;
    }
    case 2:
        break;
    case 3:
        break;
    case 4:
        
        break;
    default: break;
    }
    return true;
}