#include "Title.h"
#include "easings.h"

#include "SceneManager.h"


// Constructor
Title::Title(SceneManager* sceneManager) : Scene()
{
   this->sceneManager = sceneManager;
}
// Destructor
Title::~Title()
{
    Unload();
}



bool Title::Load()
{
    sceneManager->bgTitle = sceneManager->tex->Load("sprites/mainscreen/title_screen.png");
    titleName = sceneManager->tex->Load("sprites/mainscreen/odd_space_logo.png");
    optionsTex = sceneManager->tex->Load("sprites/ui/ui_menupause.png");

    sceneManager->audio->PlayMusic("audio/music/menu_music.ogg", 2);

    // Buttons
    buttons.buttonPlay = new GuiButton(1, { 92, 183, 224, 64 }, "New Game", sceneManager->audio);
    buttons.buttonPlay->SetObserver(this);
    buttons.buttonContinue = new GuiButton(2, { 100, 283, 224, 64 }, "Continue", sceneManager->audio);
    buttons.buttonContinue->SetObserver(this);
    if(!sceneManager->savedataexist) buttons.buttonContinue->disabled = true;
    buttons.buttonSettings = new GuiButton(3, { 100, 383, 224, 64 }, "Settings", sceneManager->audio);
    buttons.buttonSettings->SetObserver(this);
    buttons.buttonExit = new GuiButton(4, { 98, 483, 224, 64 }, "Exit", sceneManager->audio);
    buttons.buttonExit->SetObserver(this);

    finalPosY = sceneManager->render->camera.y / 2 + 226;
    return false;
}

bool Title::Update(float dt)
{
    bool ret = false;

    /*if (titlePosX > 500.0f)
    {
        titlePosX = EaseBounceOut(currentTime, (float)(1280 + 718), 500.0f - (float)(1280 + 718), 3);
        currentTime += dt;
    }*/

    if (titlePosY < finalPosY)
   {
       titlePosY = EaseBounceOut(currentTime, initPosY, finalPosY - initPosY, 2.3f);
       currentTime += dt;
   }

    GamePad& pad = sceneManager->input->pads[0];

    if(sceneManager->openOptions)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN 
            || sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN
            || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            sceneManager->options->Unload();
        else sceneManager->options->Update(dt);
    }
    else
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            controllerMenu[c++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            controllerMenu[c--];

        if (c > 3) c = 0;
        if (c < 0) c = 3;

        buttons.buttonPlay->Update(sceneManager->input, controllerMenu[c], dt);
        buttons.buttonContinue->Update(sceneManager->input, controllerMenu[c], dt);
        buttons.buttonSettings->Update(sceneManager->input, controllerMenu[c], dt);
        buttons.buttonExit->Update(sceneManager->input, controllerMenu[c], dt);
    }

    return ret;
}

bool Title::Draw()
{
    SDL_Rect rect = { sceneManager->pos1, 0, 1280, 720 };
    sceneManager->render->DrawTexture(sceneManager->bgTitle, -sceneManager->render->camera.x, -sceneManager->render->camera.y, &rect);
    sceneManager->render->DrawTexture(titleName, 445, titlePosY, NULL);
     
    rect = { 0, 720, 224, 64 };
    sceneManager->render->DrawTexture(sceneManager->bgTitle, 100, 183, &rect);
    buttons.buttonPlay->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(sceneManager->bgTitle, 100, 283, &rect);
    buttons.buttonContinue->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(sceneManager->bgTitle, 100, 383, &rect);
    buttons.buttonSettings->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(sceneManager->bgTitle, 100, 483, &rect);
    buttons.buttonExit->Draw(sceneManager->render, sceneManager->font);

    if (sceneManager->openOptions)
    {
        rect = { 0, 0, 830, 553 };
        sceneManager->render->DrawTexture(optionsTex, -sceneManager->render->camera.x + 344, -sceneManager->render->camera.y + 110, &rect);
        sceneManager->options->Draw();
    }

    return false;
}

bool Title::Unload()
{
    // Delete buttons and textures
    sceneManager->tex->UnLoad(titleName);

    if (sceneManager->openOptions) sceneManager->options->Unload();

    buttons.buttonPlay->UnLoad();
    RELEASE(buttons.buttonPlay);
    buttons.buttonContinue->UnLoad();
    RELEASE(buttons.buttonContinue);
    buttons.buttonSettings->UnLoad();
    RELEASE(buttons.buttonSettings);
    buttons.buttonExit->UnLoad();
    RELEASE(buttons.buttonExit);

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
        sceneManager->exitToMainMenu = false;
        sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = true;
        sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = false;
        sceneManager->ResetGame();
        TransitionToScene(SceneType::NAME_SELECTOR);
        //TransitionToScene(SceneType::EXTERIOR);
        break;
    case 2:
        sceneManager->exitToMainMenu = false;
        sceneManager->loadrequested = true;
        sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = true;
        sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = false;
        break;
    case 3:
        sceneManager->options->Load();
        sceneManager->openOptions = true;
        break;
    case 4:
        sceneManager->gameIsWorking = false;
        break;
    default: break;
    }
    return true;
}