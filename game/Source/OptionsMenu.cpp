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
    /*explosion = sceneManager->tex->Load("sprites/ui/ui_explosion.png");

    explosionAnim->loop = false;
    explosionAnim->speed = 0.8f;
    explosionAnim->PushBack({ 208, 20, 158, 158 });
    explosionAnim->PushBack({ 399, 20, 158, 158 });
    explosionAnim->PushBack({ 591, 20, 158, 158 });
    explosionAnim->PushBack({ 782, 20, 158, 158 });
    explosionAnim->PushBack({ 208, 210, 158, 158 });
    explosionAnim->PushBack({ 16, 210,158, 158 });
    explosionAnim->PushBack({ 401, 210,158, 158 });
    explosionAnim->PushBack({ 590, 210,158, 158 });
    explosionAnim->PushBack({ 785, 210,158, 158 });
    explosionAnim->PushBack({ 16, 410, 158, 158 });
    explosionAnim->PushBack({ 204, 410,158, 158 });
    explosionAnim->PushBack({ 593, 410,158, 158 });
    explosionAnim->PushBack({ 783, 410,158, 158 });
    explosionAnim->PushBack({ 21, 608,158, 158 });
    explosionAnim->PushBack({ 400, 608, 158, 158 });
    explosionAnim->PushBack({ 784, 608,158, 158 });
    explosionAnim->PushBack({ 16, 802,158, 158 });
    explosionAnim->PushBack({ 209, 802,158, 158 });
    explosionAnim->PushBack({ 592, 802,158, 158 });
    explosionAnim->PushBack({ 783, 802, 158, 158 });*/

    fullScreen = new GuiCheckBox(1, { 400, 200, 32, 32 }, "Fullscreen", sceneManager->audio);
    fullScreen->SetObserver(this);
    VSync = new GuiCheckBox(2, { 400, 300, 32, 32 }, "VSync", sceneManager->audio);
    VSync->SetObserver(this);
    music = new GuiSlider(3, { 400, 400, 500, 16 }, "Music", sceneManager->audio);
    music->SetObserver(this);
    fx = new GuiSlider(4, { 400, 500, 500, 16 }, "Fx", sceneManager->audio);
    fx->SetObserver(this);

    stepedAnimation = new StepedAnimation();
    stepedAnimation->speed = 80.0f;

    if(sceneManager->currentscenetype == SceneType::TITLE)
    {
        stepedAnimation->Pushback(354, 1166, 120, 120, 1200 - 334, 5);
        stepedAnimation->Pushback(1161, 1161, 120, 650, 5, 572);
        stepedAnimation->Pushback(1166, 354, 650, 650, 1103 - 253, 5);
        stepedAnimation->Pushback(354, 354, 650, 120, 5, 622 - 476);
    }

    else
    {
        stepedAnimation->Pushback(83, 339, 382, 382, 1083, 5);
        stepedAnimation->Pushback(334, 334, 382, 100, 5, 282);
        stepedAnimation->Pushback(334, 1177, 100, 100, 1177 - 334, 5);
        stepedAnimation->Pushback(1177, 1177, 100, 665, 5, 572);
        stepedAnimation->Pushback(1182, 334, 665, 665, 1103 - 253, 5);
        stepedAnimation->Pushback(334, 334, 668, 476, 5, 622 - 476);
        stepedAnimation->Pushback(334, 83, 476, 476, 233, 5);
        stepedAnimation->Pushback(83, 83, 476, 382, 5, 94);
    }

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

    /*if (VSync->explode)
    {
        VSync->explode = false;
        playingExplosionVsync = true;
        explosionAnim->Reset();
    }

    if (fullScreen->explode)
    {
        VSync->explode = false;
        playingExplosionfullScreen = true;
        explosionAnim->Reset();
    }*/

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


    int amountDisapeared = 0;

    for (int i = 0; i < stepedAnimation->currentStep; i++)
    {
        SDL_Rect temp = stepedAnimation->GetStep(i);
        sceneManager->render->DrawRectangle(temp, 255, 255, 255, stepedAnimation->steps[i].alpha, true, false);
        if (stepedAnimation->steps[i].disapear) stepedAnimation->steps[i].alpha -= 3;
        if (stepedAnimation->steps[i].alpha <= 0)
        {
            stepedAnimation->steps[i].alpha = 0;
            stepedAnimation->steps[i].disapear = false;
        }

        if (!stepedAnimation->steps[i].disapear) amountDisapeared++;
    }

    if (!stepedAnimation->animationCompleted)
    {
        SDL_Rect temp = stepedAnimation->Update();
        sceneManager->render->DrawRectangle(temp, 255, 255, 255, 255, true, false);
    }

    else if(amountDisapeared >= stepedAnimation->stepAmount)
    {
        stepedAnimation->Reset();
        
        if (sceneManager->currentscenetype == SceneType::TITLE)
        {
            stepedAnimation->Pushback(354, 1166, 120, 120, 1200 - 334, 5);
            stepedAnimation->Pushback(1161, 1161, 120, 650, 5, 572);
            stepedAnimation->Pushback(1166, 354, 650, 650, 1103 - 253, 5);
            stepedAnimation->Pushback(354, 354, 650, 120, 5, 622 - 476);
        }

        else
        {
            stepedAnimation->Pushback(83, 339, 382, 382, 1083, 5);
            stepedAnimation->Pushback(334, 334, 382, 100, 5, 282);
            stepedAnimation->Pushback(334, 1177, 100, 100, 1177 - 334, 5);
            stepedAnimation->Pushback(1177, 1177, 100, 665, 5, 572);
            stepedAnimation->Pushback(1182, 334, 665, 665, 1103 - 253, 5);
            stepedAnimation->Pushback(334, 334, 668, 476, 5, 622 - 476);
            stepedAnimation->Pushback(334, 83, 476, 476, 233, 5);
            stepedAnimation->Pushback(83, 83, 476, 382, 5, 94);
        }
    }

    /*if (music->state == GuiControlState::PRESSED)
    {
        SDL_Rect rect = { 375, 160, 200, 300 };
        SDL_Color color1 = { 255, 0, 0, 255 };
        SDL_Color color2 = { 0, 255, 0, 255 };
        sceneManager->render->DrawDegradedRectVertical(rect, color1, color2);
    }*/

    /*if (playingExplosionVsync)
    {
        explosionAnim->Update();
        SDL_Rect rec = explosionAnim->GetCurrentFrame();
        sceneManager->render->DrawTexture(explosion, VSync->bounds.x - 125 / 2, VSync->bounds.y - 125 / 2, &rec);
        if (explosionAnim->HasFinished()) playingExplosionVsync = false;
    }

    if (playingExplosionfullScreen)
    {
        explosionAnim->Update();
        SDL_Rect rec = explosionAnim->GetCurrentFrame();
        sceneManager->render->DrawTexture(explosion, fullScreen->bounds.x - 125 / 2, fullScreen->bounds.y - 125 / 2, &rec);
        if (explosionAnim->HasFinished()) playingExplosionfullScreen = false;
    }*/

    return true;
}

bool OptionsMenu::Unload()
{
    //sceneManager->tex->UnLoad(explosion);
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

    RELEASE(stepedAnimation);

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

        if (showCursor)
        {
            SDL_ShowCursor(0);
            showCursor = false;
        }
        else if (!showCursor)
        {
            SDL_ShowCursor(1);
            showCursor = true;
        }
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