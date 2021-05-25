#include "EndDemo.h"

#include "SceneManager.h"


// Constructor
EndDemo::EndDemo(SceneManager * sceneManager) : Scene()
{
    this->sceneManager = sceneManager;
}
// Destructor
EndDemo::~EndDemo()
{
}



bool EndDemo::Load()
{
    bgTitle = sceneManager->tex->Load("sprites/mainscreen/title_screen.png");
    titleName = sceneManager->tex->Load("sprites/mainscreen/odd_space_logo.png");
    sceneManager->render->camera = { 0, 0 };

    sceneManager->audio->PlayMusic("audio/music/menu_music.ogg", 2);

    if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->infoEntities.info.HP <= 0)
        sceneManager->entityManager->CreateEntity(EntityType::HERO)->infoEntities.info.HP = sceneManager->entityManager->CreateEntity(EntityType::HERO)->infoEntities.info.maxHP;

    if (sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->infoEntities.info.HP <= 0)
        sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->infoEntities.info.HP = sceneManager->entityManager->CreateEntity(EntityType::CAPTAIN)->infoEntities.info.maxHP;

    // Buttons
    buttons.buttonPlay = new GuiButton(1, { (1280 / 2) - 244 - 100, (720 / 2) + 64 + 150, 224, 64 }, "Retry", sceneManager->audio);
    buttons.buttonPlay->SetObserver(this);
    buttons.buttonExit = new GuiButton(2, { (1280 / 2) + 100, (720 / 2) + 64 + 150, 224, 64 }, "Exit", sceneManager->audio);
    buttons.buttonExit->SetObserver(this);

    return false;
}

bool EndDemo::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
        controllerMenu[c++];

    if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
        controllerMenu[c--];

    if (c > 1) c = 0;
    if (c < 0) c = 1;

    buttons.buttonPlay->Update(sceneManager->input, controllerMenu[c], dt);
    buttons.buttonExit->Update(sceneManager->input, controllerMenu[c], dt);

    if (pos1 <= 0)
    {
        pos1 = 2560;
    }
    else pos1 -= 1 * dt;

    return ret;
}

bool EndDemo::Draw()
{
    SDL_Rect rect = { pos1, 0, 1280, 720 };
    sceneManager->render->DrawTexture(bgTitle, -sceneManager->render->camera.x, -sceneManager->render->camera.y, &rect);
    sceneManager->render->DrawTexture(titleName, (1280 / 2) - (718 / 2) + 20, (720 / 2) - 286, NULL);
    sceneManager->render->DrawText(sceneManager->font, "End Demo", (1280 / 2) - 150, (720 / 2) + 30, 40, 0, { 255, 255, 255, 255 });
    sceneManager->render->DrawText(sceneManager->font, "Thanks for playing!", (1280 / 2) - 225, (720 / 2) + 90, 30, 0, { 255, 255, 255, 255 });

    rect = { 0, 720, 224, 64 };
    sceneManager->render->DrawTexture(bgTitle, (1280 / 2) - 244 - 100, (720 / 2) + 64 + 150, &rect);
    buttons.buttonPlay->Draw(sceneManager->render, sceneManager->font);
    sceneManager->render->DrawTexture(bgTitle, (1280 / 2) + 100, (720 / 2) + 64 + 150, &rect);
    buttons.buttonExit->Draw(sceneManager->render, sceneManager->font);

    return false;
}

bool EndDemo::Unload()
{
    // Delete buttons and textures
    sceneManager->tex->UnLoad(bgTitle);
    sceneManager->tex->UnLoad(titleName);

    buttons.buttonPlay->UnLoad();
    RELEASE(buttons.buttonPlay);
    buttons.buttonExit->UnLoad();
    RELEASE(buttons.buttonExit);
    return false;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool EndDemo::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->id)
    {
    case 1:
        TransitionToScene(SceneType::EXTERIOR);
        break;
    case 2:
        sceneManager->gameIsWorking = false;
        break;
    default: break;
    }
    return true;
}