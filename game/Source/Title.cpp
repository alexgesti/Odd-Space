#include "Title.h"
#include "easings.h"

#include "SceneManager.h"


// Constructor
Title::Title(SceneManager* sceneManager) : Scene()
{
   this->sceneManager = sceneManager;

   temporalAppearTitle = sceneManager->audio->LoadFx("audio/fx/battle_strike.wav");
}
// Destructor
Title::~Title()
{
}



bool Title::Load()
{
    bgTitle = sceneManager->tex->Load("sprites/mainscreen/title_screen.png");
    titleName = sceneManager->tex->Load("sprites/mainscreen/odd_space_logo.png");
    optionsTex = sceneManager->tex->Load("sprites/ui/ui_menupause.png");

    sceneManager->audio->PlayMusic("audio/music/menu_music.ogg", 2);

    // Buttons
    buttons.buttonPlay = new GuiButton(1, { 100, 183, 224, 64 }, "New Game", sceneManager->audio);
    buttons.buttonPlay->SetObserver(this);
    buttons.buttonContinue = new GuiButton(2, { 100, 283, 224, 64 }, "Continue", sceneManager->audio);
    buttons.buttonContinue->SetObserver(this);
    if(!sceneManager->savedataexist) buttons.buttonContinue->disabled = true;
    buttons.buttonSettings = new GuiButton(3, { 100, 383, 224, 64 }, "Settings", sceneManager->audio);
    buttons.buttonSettings->SetObserver(this);
    buttons.buttonExit = new GuiButton(4, { 100, 483, 224, 64 }, "Exit", sceneManager->audio);
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
        if (sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
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

    if (pos1 <= 0)
    {
        pos1 = 2560;
        if (!once)
        {
            sceneManager->audio->PlayFx(temporalAppearTitle);
            once = true;
        }
    }
    else pos1 -= 1 * dt;

    return ret;
}

bool Title::Draw()
{
    SDL_Rect rect = { pos1, 0, 1280, 720 };
    sceneManager->render->DrawTexture(bgTitle, -sceneManager->render->camera.x, -sceneManager->render->camera.y, &rect);
    sceneManager->render->DrawTexture(titleName, 445, titlePosY, NULL);
     
    rect = { 0, 720, 224, 64 };
    sceneManager->render->DrawTexture(bgTitle, 100, 183, &rect);
    buttons.buttonPlay->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(bgTitle, 100, 283, &rect);
    buttons.buttonContinue->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(bgTitle, 100, 383, &rect);
    buttons.buttonSettings->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(bgTitle, 100, 483, &rect);
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
    sceneManager->tex->UnLoad(bgTitle);
    sceneManager->tex->UnLoad(titleName);

    if (sceneManager->openOptions) sceneManager->options->Unload();

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
        sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = true;
        sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->inBattle = false;
        TransitionToScene(SceneType::EXTERIOR);
        break;
    case 2:
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