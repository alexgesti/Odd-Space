#include "MutantRat.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



MutantRat* MutantRat::instance = nullptr;
// Instance creator
MutantRat* MutantRat::GetInstance(Render* render, Textures* tex)
{
    instance = new MutantRat(render,tex);
    LOG("Returning mutant rat instance");

    return instance;
}
// Instance reseter
void MutantRat::ResetInstance()
{
    RELEASE(instance);
}
// Constructor
MutantRat::MutantRat(Render* render, Textures* tex) : Enemy(EnemyType::MUTANTRAT)
{
    this->render = render;
    this->tex = tex;

    mutantRatTexture = NULL;
    position = iPoint(0, 0);

    width = 16;
    height = 32;

    //Mutant Rat stats
    infoEntities.info.name = "Mutant Rat";
    infoEntities.info.HP = 15;
    infoEntities.info.LVL = 3;
    infoEntities.stats.ATK = 10;
    infoEntities.stats.DEF = 3;
    infoEntities.stats.SPD = 7;
    infoEntities.stats.LCK = 4;

    // Define Player animations
    mutantRatTexture = this->tex->Load("sprites/enemies/nme_normalrat_w.png");


    mutantRatAnim->loop = true;
    mutantRatAnim->speed = 0.15f;

    mutantRatAnim->PushBack({ 0, 0, 64, 64 });
    mutantRatAnim->PushBack({ 64, 0, 64, 64 });
    mutantRatAnim->PushBack({ 128, 0, 64, 64 });
    mutantRatAnim->PushBack({ 64, 0, 64, 64 });

    //Define Hurt Texture
    hurtTexture = this->tex->Load("sprites/combat/cmb_hurt.png");
}
// Destructor
MutantRat::~MutantRat()
{}



bool MutantRat::Update(float dt)
{
    mutantRatAnim->Update();
    return true;
}


bool MutantRat::Draw()
{
    if (infoEntities.info.HP > 0)
    {
        // TODO: Calculate the corresponding rectangle depending on the
        // animation state and animation frame
        SDL_Rect rec = mutantRatAnim->GetCurrentFrame();
        render->DrawTexture(mutantRatTexture, position.x, position.y, &rec);

        rec = hurtAnim->GetCurrentFrame();
        render->DrawTexture(hurtTexture, position.x, position.y, &rec);
    }

    return false;
}



void MutantRat::SetTexture(SDL_Texture *tex)
{
    mutantRatTexture = tex;
}

SDL_Rect MutantRat::GetBounds()
{
    return { position.x, position.y, width, height };
}

bool MutantRat::UnLoad()
{
    tex->UnLoad(mutantRatTexture);
    tex->UnLoad(hurtTexture);

    RELEASE(mutantRatAnim);
    RELEASE(hurtAnim);
    RELEASE(deathAnim);

    return false;
}
