#include "MutantRat.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"



MutantRat* MutantRat::instance = nullptr;
// Instance creator
MutantRat* MutantRat::GetInstance(Input* input, Render* render, Textures* tex)
{
    instance = new MutantRat(input, render,tex);
    LOG("Returning mutant rat instance");

    return instance;
}
// Instance reseter
void MutantRat::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
MutantRat::MutantRat(Input* input, Render* render, Textures* tex) : Enemy(EnemyType::MUTANTRAT)
{
    this->input = input;
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
    mutantRatTexture = this->tex->Load("assets/sprites/enemies/char_enemirat_v02_w.png");


    mutantRatAnim->loop = true;
    mutantRatAnim->speed = 0.15f;

    mutantRatAnim->PushBack({ 0, 0, 64, 64 });
    mutantRatAnim->PushBack({ 64, 0, 64, 64 });
    mutantRatAnim->PushBack({ 128, 0, 64, 64 });
    mutantRatAnim->PushBack({ 64, 0, 64, 64 });
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
