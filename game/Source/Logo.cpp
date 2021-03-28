#include "Logo.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"

#define LOGO_FADE_SPEED 1.0f



// Constructor
Logo::Logo(Input* input, Render* render, Textures* tex)
{
    this->input = input;
    this->render = render;
    this->tex = tex;


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
    logo = tex->Load("assets/sprites/Logo/logo_chaoticevil.png");
    return true;
}

bool Logo::Update(float dt)
{
    if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
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
    render->DrawRectangle({ 0, 0, 1280, 720 }, 0, 0, 0, 255);

    SDL_SetTextureAlphaMod(logo, logoAlpha * 255);
    render->DrawTexture(logo, render->camera.w / 2 - 600 / 2, render->camera.h / 2 - 561 / 2, NULL);

    return true;
}

bool Logo::Unload()
{
    tex->UnLoad(logo);
    return true;
}