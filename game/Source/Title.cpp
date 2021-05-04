#include "Title.h"

#include "SceneManager.h"


// Constructor
Title::Title(SceneManager* sceneManager, Audio* audio) : Scene()
{
   this->sceneManager = sceneManager;
   this->audio = audio;

   temporalAppearTitle = audio->LoadFx("Assets/Audio/Fx/spells_fx.wav");
   selected = audio->LoadFx("Assets/Audio/Fx/hover_ui.wav");
}
// Destructor
Title::~Title()
{
}



bool Title::Load()
{
    bgTitle = sceneManager->tex->Load("assets/sprites/MainScreen/title_screen.png");
    titleName = sceneManager->tex->Load("assets/sprites/MainScreen/odd_space_logo.png");
    audio->PlayMusic("Assets/Audio/Music/menu_music1.ogg", 2);

    // Buttons
    buttons.buttonPlay = new GuiButton(1, { 150, 180, 160, 75 }, "New Game");
    buttons.buttonPlay->SetObserver(this);
    buttons.buttonContinue = new GuiButton(2, { 155, 280, 160, 75 }, "Continue");
    buttons.buttonContinue->SetObserver(this);
    buttons.buttonSettings = new GuiButton(3, { 155, 380, 160, 75 }, "Settings");
    buttons.buttonSettings->SetObserver(this);
    buttons.buttonExit = new GuiButton(4, { 195, 480, 160, 75 }, "Exit");
    buttons.buttonExit->SetObserver(this);


    return false;
}

bool Title::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    if (oneTime)
    {
        audio->PlayFx(temporalAppearTitle);
        oneTime = false;
    }

    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
    {
        controllerMenu[c++];
        audio->PlayFx(selected);
    }
    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
    {
        controllerMenu[c--];
        audio->PlayFx(selected);
    }

    if (c > 3) c = 0;
    if (c < 0) c = 3;

    buttons.buttonPlay->Update(sceneManager->input, controllerMenu[c], dt);
    buttons.buttonContinue->Update(sceneManager->input, controllerMenu[c], dt);
    buttons.buttonSettings->Update(sceneManager->input, controllerMenu[c], dt);
    buttons.buttonExit->Update(sceneManager->input, controllerMenu[c], dt);

    if (pos1 <= 0)
    {
        pos1 = 2560;
    }
    else pos1 -= 1 * dt;

    return ret;
}

bool Title::Draw()
{
    SDL_Rect rect = { pos1, 0, 1280, 720 };
    sceneManager->render->DrawTexture(bgTitle, sceneManager->render->camera.x, sceneManager->render->camera.y, &rect);
    sceneManager->render->DrawTexture(titleName, 500, sceneManager->render->camera.y / 2 + 226, NULL);
     
    SDL_Rect button = { 0, 720, 224, 64 };
    sceneManager->render->DrawTexture(bgTitle, 127, 183, &button);
    buttons.buttonPlay->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(bgTitle, 127, 283, &button);
    buttons.buttonContinue->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(bgTitle, 127, 383, &button);
    buttons.buttonSettings->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(bgTitle, 127, 483, &button);
    buttons.buttonExit->Draw(sceneManager->render, sceneManager->font);
    return false;
}

bool Title::Unload()
{
    // Delete buttons and textures
    sceneManager->tex->UnLoad(bgTitle);
    sceneManager->tex->UnLoad(titleName);

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
        audio->PlayFx(selected);
        sceneManager->audio->PlayMusic("Assets/Audio/Music/exterior_music.ogg");
        TransitionToScene(SceneType::EXTERIOR);
        break;
    case 2:
        audio->PlayFx(selected);
        sceneManager->loadrequested = true;
        sceneManager->audio->PlayMusic("Assets/Audio/Music/exterior_music.ogg");
        break;
    case 3:
        audio->PlayFx(selected);
        break;
    case 4:
        audio->PlayFx(selected);
        sceneManager->gameIsWorking = false;
        break;
    default: break;
    }
    return true;
}