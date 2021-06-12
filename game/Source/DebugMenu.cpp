#include "DebugMenu.h"

#include "SceneManager.h"


// Constructor
Debug::Debug(SceneManager * sceneManager) : Scene()
{
    this->sceneManager = sceneManager;
}
// Destructor
Debug::~Debug()
{
    Unload();
}

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

    debug.battle = new GuiButton(5, { 960, 0, 320, 60 }, "Start Battle", sceneManager->audio, false);
    debug.battle->SetObserver(this);
    controllerMenu[0][1] = 5;

    debug.item = new GuiButton(6, { 960, 60, 320, 60 }, "Obtain Item", sceneManager->audio, false);
    debug.item->SetObserver(this);
    controllerMenu[1][1] = 6;

    debug.scene = new GuiButton(7, { 960, 120, 120, 60 }, "Scenes", sceneManager->audio, false);
    debug.scene->SetObserver(this);
    controllerMenu[2][1] = 7;

    debug.particle = new GuiButton(8, { 960, 180, 180, 60 }, "Particles", sceneManager->audio, false);
    debug.particle->SetObserver(this);
    controllerMenu[3][1] = 8;

    // Scenes
    scene.exterior = new GuiButton(9, { 960, 0, 320, 60 }, "Exterior", sceneManager->audio, false);
    scene.exterior->SetObserver(this);
    controllerScene[0] = 9;

    scene.cantina = new GuiButton(10, { 960, 60, 320, 60 }, "Cantina", sceneManager->audio, false);
    scene.cantina->SetObserver(this);
    controllerScene[1] = 10;

    scene.wc = new GuiButton(11, { 960, 120, 320, 60 }, "WC", sceneManager->audio, false);
    scene.wc->SetObserver(this);
    controllerScene[2] = 11;

    scene.dungeonExt = new GuiButton(12, { 960, 180, 320, 60 }, "External Dungeon", sceneManager->audio, false);
    scene.dungeonExt->SetObserver(this);
    controllerScene[3] = 12;

    scene.dungeonF1 = new GuiButton(13, { 960, 240, 320, 60 }, "F1 Dungeon", sceneManager->audio, false);
    scene.dungeonF1->SetObserver(this);
    controllerScene[4] = 13;

    scene.dungeonF2 = new GuiButton(14, { 960, 300, 320, 60 }, "F2 Dungeon", sceneManager->audio, false);
    scene.dungeonF2->SetObserver(this);
    controllerScene[5] = 14;

    // Particles
    particle.smoke = new GuiButton(15, { 960, 0, 320, 60 }, "Smoke", sceneManager->audio, false);
    particle.smoke->SetObserver(this);
    controllerParticle[0] = 15;

    particle.heal = new GuiButton(16, { 960, 60, 320, 60 }, "Heal", sceneManager->audio, false);
    particle.heal->SetObserver(this);
    controllerParticle[1] = 16;

    particle.bless = new GuiButton(17, { 960, 120, 320, 60 }, "Bless", sceneManager->audio, false);
    particle.bless->SetObserver(this);
    controllerParticle[2] = 17;

    return false;
}

bool Debug::Update(float dt)
{
    bool ret = false;

    GamePad& pad = sceneManager->input->pads[0];

    if (debugscene == false && debugparticle == false)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            controllerMenu[f++][c];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            controllerMenu[f--][c];

        if (sceneManager->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
            controllerMenu[f][c++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
            controllerMenu[f][c--];

        if (c > 1) c = 0;
        if (c < 0) c = 1;
        switch (c)
        {
        case 0:
            if (f > 3) f = 0;
            if (f < 0) f = 3;
            break;
        case 1:
            if (f > 3) f = 0;
            if (f < 0) f = 3;
            break;
        default:break;
        }
    }
    else if (debugscene)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            controllerScene[f++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            controllerScene[f--];

        if (f > 5) f = 0;
        if (f < 0) f = 5;

        if (sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN || 
            sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || 
            sceneManager->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN ||
            sceneManager->input->GetKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            debugscene = false;
    }
    else if (debugparticle)
    {
        if (sceneManager->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN)
            controllerParticle[f++];

        if (sceneManager->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN)
            controllerParticle[f--];

        if (f > 2) f = 0;
        if (f < 0) f = 2;

        if (sceneManager->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN ||
            sceneManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN ||
            sceneManager->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN ||
            sceneManager->input->GetKey(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN)
            debugparticle = false;
    }

    if (debugscene == false && debugparticle == false)
    {
        debug.noClip->Update(sceneManager->input, &sceneManager->entityManager->CreateEntity(EntityType::HERO)->noClip, controllerMenu[f][c], dt);
        debug.godMode->Update(sceneManager->input, &sceneManager->beGod, controllerMenu[f][c], dt);
        debug.dialogue->Update(sceneManager->input, &sceneManager->dialogueSystem->inConversation, controllerMenu[f][c], dt);
        debug.colliders->Update(sceneManager->input, &sceneManager->drawColliders, controllerMenu[f][c], dt);
        debug.battle->Update(sceneManager->input, controllerMenu[f][c], dt);
        debug.item->Update(sceneManager->input, controllerMenu[f][c], dt);
        debug.scene->Update(sceneManager->input, controllerMenu[f][c], dt);
        debug.particle->Update(sceneManager->input, controllerMenu[f][c], dt);
    }
    else if (debugscene)
    {
        scene.exterior->Update(sceneManager->input, controllerScene[f], dt);
        scene.cantina->Update(sceneManager->input, controllerScene[f], dt);
        scene.wc->Update(sceneManager->input, controllerScene[f], dt);
        scene.dungeonExt->Update(sceneManager->input, controllerScene[f], dt);
        scene.dungeonF1->Update(sceneManager->input, controllerScene[f], dt);
        scene.dungeonF2->Update(sceneManager->input, controllerScene[f], dt);
    }
    else if (debugparticle)
    {
        particle.smoke->Update(sceneManager->input, controllerParticle[f], dt);
        particle.heal->Update(sceneManager->input, controllerParticle[f], dt);
        particle.bless->Update(sceneManager->input, controllerParticle[f], dt);
    }

    if (sceneManager->entityManager->CreateEntity(EntityType::HERO)->inBattle == false)
        debug.particle->disabled = true;
    else debug.particle->disabled = false;

    return ret;
}

bool Debug::Draw()
{
    

    if (debugscene == false && debugparticle == false)
    {
        sceneManager->render->DrawRectangle({ -sceneManager->render->camera.x + 615, -sceneManager->render->camera.y - (240 / 2), 675, 360 }, 0, 0, 0, 175);

        sceneManager->render->DrawText(sceneManager->font, "noClip", 645, 22, 60 / 3, 0, { 255, 255, 255, 255 });
        debug.noClip->Draw(sceneManager->render, texture);

        sceneManager->render->DrawText(sceneManager->font, "GodMode", 645, 82, 60 / 3, 0, { 255, 255, 255, 255 });
        debug.godMode->Draw(sceneManager->render, texture);

        sceneManager->render->DrawText(sceneManager->font, "Dialogue", 645, 142, 60 / 3, 0, { 255, 255, 255, 255 });
        debug.dialogue->Draw(sceneManager->render, texture);

        sceneManager->render->DrawText(sceneManager->font, "Colliders", 645, 202, 60 / 3, 0, { 255, 255, 255, 255 });
        debug.colliders->Draw(sceneManager->render, texture);

        debug.battle->Draw(sceneManager->render, sceneManager->font);
        debug.item->Draw(sceneManager->render, sceneManager->font);
        debug.scene->Draw(sceneManager->render, sceneManager->font);
        debug.particle->Draw(sceneManager->render, sceneManager->font);
    }
    else if (debugscene)
    {
        sceneManager->render->DrawRectangle({ -sceneManager->render->camera.x + 615 + (670 / 2), -sceneManager->render->camera.y, 675, 360 }, 0, 0, 0, 175);

        scene.exterior->Draw(sceneManager->render, sceneManager->font);
        scene.cantina->Draw(sceneManager->render, sceneManager->font);
        scene.wc->Draw(sceneManager->render, sceneManager->font);
        scene.dungeonExt->Draw(sceneManager->render, sceneManager->font);
        scene.dungeonF1->Draw(sceneManager->render, sceneManager->font);
        scene.dungeonF2->Draw(sceneManager->render, sceneManager->font);
    }
    else if (debugparticle)
    {
        sceneManager->render->DrawRectangle({ -sceneManager->render->camera.x + 615 + (670 / 2), -sceneManager->render->camera.y - (370 / 2), 675, 360 }, 0, 0, 0, 175);

        particle.smoke->Draw(sceneManager->render, sceneManager->font);
        particle.heal->Draw(sceneManager->render, sceneManager->font);
        particle.bless->Draw(sceneManager->render, sceneManager->font);
    }

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

    debug.item->UnLoad();
    RELEASE(debug.item);

    debug.scene->UnLoad();
    RELEASE(debug.scene);

    debug.particle->UnLoad();
    RELEASE(debug.particle);

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

    particle.smoke->UnLoad();
    RELEASE(particle.smoke);

    particle.heal->UnLoad();
    RELEASE(particle.heal);
    
    particle.bless->UnLoad();
    RELEASE(particle.bless);

    return false;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool Debug::OnGuiMouseClickEvent(GuiControl* control)
{
    if (debugparticle == false && debugscene == false)
    {
        switch (control->id)
        {
        case 5:
            TransitionToScene(SceneType::BATTLE);
            break;
        case 6:
            sceneManager->entityManager->CreateEntity(EntityType::RANDITEM);
            break;
        case 7:
            debugscene = true;
            f = 0;
            c = 0;
            break;
        case 8:
            debugparticle = true;
            f = 0;
            c = 0;
            break;
        default: break;
        }
    }
    else if (debugscene)
    {
        switch (control->id)
        {
        case 9:
            TransitionToScene(SceneType::EXTERIOR);
            break;
        case 10:
            TransitionToScene(SceneType::CANTINA);
            break;
        case 11:
            TransitionToScene(SceneType::WC);
            break;
        case 12:
            TransitionToScene(SceneType::DUNGEON_EXT);
            break;
        case 13:
            TransitionToScene(SceneType::DUNGEON_F1);
            break;
        case 14:
            TransitionToScene(SceneType::DUNGEON_F2);
            break;
        }
    }
    else if (debugparticle)
    {
        switch (control->id)
        {
        case 15:
            // Smoke
            sceneManager->particleSystem->AddEmitter({ 375, 250 }, EmitterData::EmitterType::SMOKE, sceneManager->render);
            break;
        case 16:
            // Heal
            sceneManager->particleSystem->AddEmitter({ 365, 250 }, EmitterData::EmitterType::HEAL, sceneManager->render);
            break;
        case 17:
            // Bless
            sceneManager->particleSystem->AddEmitter({ 365, 250 }, EmitterData::EmitterType::BLESS, sceneManager->render);
            break;
        default:
            break;
        }
    }

    return true;
}