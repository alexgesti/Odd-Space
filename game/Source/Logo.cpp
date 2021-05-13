#include "Logo.h"

#include "SceneManager.h"

#define LOGO_FADE_SPEED 1.0f

// Constructor
Logo::Logo(SceneManager* sceneManager)
{
    this->sceneManager = sceneManager;

    state = 0;
    timeCounter = 0.0f;
    logoAlpha = 0.0f;

}
// Destructor
Logo::~Logo()
{
}



bool Logo::Load()
{
    logo = sceneManager->tex->Load("assets/sprites/Logo/logo_chaoticevil.png");

    temporalLogoSound = sceneManager->audio->LoadFx("Assets/Audio/Fx/battle_win_music.wav");
    return true;
}

bool Logo::Update(float dt)
{
    GamePad& pad = sceneManager->input->pads[0];

    if (sceneManager->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || sceneManager->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN)
    {
        TransitionToScene(SceneType::TITLE);
    }

    if (state == 0)
    {
        state = 1;
    }
    else if (state == 1)
    {
        logoAlpha += (LOGO_FADE_SPEED * dt);

        if (logoAlpha > 1.0f)
        {
            logoAlpha = 1.0f;
            sceneManager->audio->PlayFx(temporalLogoSound);
            state = 2;
        }
    }
    else if (state == 2)
    {
        // Waiting for 3 seconds
        timeCounter += dt;
        if (timeCounter >= 3.0f) state = 3;
    }
    else if (state == 3)
    {
        logoAlpha -= (LOGO_FADE_SPEED * dt);

        if (logoAlpha < 0.0f)
        {
            logoAlpha = 0.0f;
            TransitionToScene(SceneType::TITLE);
        }
    }

    return true;
}

bool Logo::Draw()
{
    sceneManager->render->DrawRectangle({ 0, 0, 1280, 720 }, 0, 0, 0, 255);

    SDL_SetTextureAlphaMod(logo, logoAlpha * 255);
    sceneManager->render->DrawTexture(logo, sceneManager->render->camera.w / 2 - 600 / 2, sceneManager->render->camera.h / 2 - 561 / 2, NULL);

    return true;
}

bool Logo::Unload()
{
    sceneManager->tex->UnLoad(logo);

    sceneManager->audio->UnloadFx(temporalLogoSound - 1);
    return true;
}