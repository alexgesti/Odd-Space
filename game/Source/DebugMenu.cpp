#include "DebugMenu.h"

#include "SceneManager.h"


// Constructor
Debug::Debug(SceneManager * sceneManager) : Scene()
{
    this->sceneManager = sceneManager;
}
// Destructor
Debug::~Debug()
{}



bool Debug::Load()
{
    texture = sceneManager->tex->Load("sprites/ui/ui_menupause.png");

    // Debug
    debug.noClip = new GuiCheckBox(1, { 815, 0, 32, 60 }, "noClip", sceneManager->audio);
    debug.noClip->SetObserver(this);
    controllerMenu[0][0] = 1;

    debug.godMode = new GuiCheckBox(2, { 815, 60, 32, 60 }, "GodMode", sceneManager->audio);
    debug.godMode->SetObserver(this);
    controllerMenu[1][0] = 2;

    debug.dialogue = new GuiCheckBox(3, { 815, 120, 32, 60 }, "Dialogue", sceneManager->audio);
    debug.dialogue->SetObserver(this);
    controllerMenu[2][0] = 3;

    debug.colliders = new GuiCheckBox(4, { 815, 180, 32, 60 }, "Colliders", sceneManager->audio);
    debug.colliders->SetObserver(this);
    controllerMenu[3][0] = 4;

    debug.battle = new GuiButton(5, { 640, 240, 320, 60 }, "Start Battle", sceneManager->audio, false);
    debug.battle->SetObserver(this);
    controllerMenu[4][0] = 5;

    // Scene
    scene.exterior = new GuiButton(6, { 960, 0, 320, 60 }, "Exterior", sceneManager->audio, false);
    scene.exterior->SetObserver(this);
    controllerMenu[0][1] = 6;

    scene.cantina = new GuiButton(7, { 960, 60, 320, 60 }, "Cantina", sceneManager->audio, false);
    scene.cantina->SetObserver(this);
    controllerMenu[1][1] = 7;

    scene.wc = new GuiButton(8, { 960, 120, 320, 60 }, "WC", sceneManager->audio, false);
    scene.wc->SetObserver(this);
    controllerMenu[2][1] = 8;

    scene.dungeonExt = new GuiButton(9, { 960, 180, 320, 60 }, "External Dungeon", sceneManager->audio, false);
    scene.dungeonExt->SetObserver(this);
    controllerMenu[3][1] = 9;

    scene.dungeonF1 = new GuiButton(10, { 960, 240, 320, 60 }, "F1 Dungeon", sceneManager->audio, false);
    scene.dungeonF1->SetObserver(this);
    controllerMenu[4][1] = 10;

    scene.dungeonF2 = new GuiButton(11, { 960, 300, 320, 60 }, "F2 Dungeon", sceneManager->audio, false);
    scene.dungeonF2->SetObserver(this);
    controllerMenu[5][1] = 11;

    return false;
}

bool Debug::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
        controllerMenu[f][c++];

    if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
        controllerMenu[f][c--];

    if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
        controllerMenu[f++][c];

    if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
        controllerMenu[f--][c];

    if (c > 1) c = 0;
    if (c < 0) c = 1;
    switch (c)
    {
    case 0:
        if (f > 4) f = 0;
        if (f < 0) f = 4;
        break;
    case 1:
        if (f > 5) f = 0;
        if (f < 0) f = 5;
        break;
    default:break;
    }

    debug.noClip->Update(sceneManager->input, &sceneManager->entityManager->CreateEntity(EntityType::HERO)->noClip, controllerMenu[f][c], dt);
    debug.godMode->Update(sceneManager->input, &sceneManager->beGod, controllerMenu[f][c], dt);
    debug.dialogue->Update(sceneManager->input, &sceneManager->dialogueSystem->inConversation, controllerMenu[f][c], dt);
    debug.colliders->Update(sceneManager->input, &sceneManager->drawColliders, controllerMenu[f][c], dt);
    debug.battle->Update(sceneManager->input, controllerMenu[f][c], dt);
    scene.exterior->Update(sceneManager->input, controllerMenu[f][c], dt);
    scene.cantina->Update(sceneManager->input, controllerMenu[f][c], dt);
    scene.wc->Update(sceneManager->input, controllerMenu[f][c], dt);
    scene.dungeonExt->Update(sceneManager->input, controllerMenu[f][c], dt);
    scene.dungeonF1->Update(sceneManager->input, controllerMenu[f][c], dt);
    scene.dungeonF2->Update(sceneManager->input, controllerMenu[f][c], dt);

    return ret;
}

bool Debug::Draw()
{
    sceneManager->render->DrawRectangle({ -sceneManager->render->camera.x + 615, -sceneManager->render->camera.y, 675, 360 }, 0, 0, 0, 175);

    sceneManager->render->DrawText(sceneManager->font, "noClip", 645, 22, 60 / 3, 0, { 255, 255, 255, 255 });
    debug.noClip->Draw(sceneManager->render, texture);

    sceneManager->render->DrawText(sceneManager->font, "GodMode", 645, 82, 60 / 3, 0, { 255, 255, 255, 255 });
    debug.godMode->Draw(sceneManager->render, texture);

    sceneManager->render->DrawText(sceneManager->font, "Dialogue", 645, 142, 60 / 3, 0, { 255, 255, 255, 255 });
    debug.dialogue->Draw(sceneManager->render, texture);

    sceneManager->render->DrawText(sceneManager->font, "Colliders", 645, 202, 60 / 3, 0, { 255, 255, 255, 255 });
    debug.colliders->Draw(sceneManager->render, texture);

    debug.battle->Draw(sceneManager->render, sceneManager->font);

    scene.exterior->Draw(sceneManager->render, sceneManager->font);

    scene.cantina->Draw(sceneManager->render, sceneManager->font);

    scene.wc->Draw(sceneManager->render, sceneManager->font);

    scene.dungeonExt->Draw(sceneManager->render, sceneManager->font);

    scene.dungeonF1->Draw(sceneManager->render, sceneManager->font);

    scene.dungeonF2->Draw(sceneManager->render, sceneManager->font);

    return false;
}

bool Debug::Unload()
{
    sceneManager->tex->UnLoad(texture);

    // Delete buttons and textures
    debug.noClip->UnLoad();
    RELEASE(debug.noClip);

    debug.godMode->UnLoad();
    RELEASE(debug.godMode);

    debug.dialogue->UnLoad();
    RELEASE(debug.dialogue);

    debug.colliders->UnLoad();
    RELEASE(debug.colliders);

    debug.battle->UnLoad();
    RELEASE(debug.battle);

    scene.exterior->UnLoad();
    RELEASE(scene.exterior);

    scene.cantina->UnLoad();
    RELEASE(scene.cantina);

    scene.wc->UnLoad();
    RELEASE(scene.wc);

    scene.dungeonExt->UnLoad();
    RELEASE(scene.dungeonExt);

    scene.dungeonF1->UnLoad();
    RELEASE(scene.dungeonF1);

    scene.dungeonF2->UnLoad();
    RELEASE(scene.dungeonF2);

    return false;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool Debug::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->id)
    {
    case 5:
        TransitionToScene(SceneType::BATTLE);
        break;
    case 6:
        TransitionToScene(SceneType::EXTERIOR);
        break;
    case 7:
        TransitionToScene(SceneType::CANTINA);
        break;
    case 8:
        TransitionToScene(SceneType::WC);
        break;
    case 9:
        TransitionToScene(SceneType::DUNGEON_EXT);
        break;
    case 10:
        TransitionToScene(SceneType::DUNGEON_F1);
        break;
    case 11:
        TransitionToScene(SceneType::DUNGEON_F2);
        break;
    default: break;
    }
    return true;
}