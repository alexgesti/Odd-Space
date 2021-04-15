#include "MutantRat.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
//#include "Textures.h"



MutantRat* MutantRat::instance = nullptr;
// Instance creator
MutantRat* MutantRat::GetInstance(Input* input, Render* render)
{
    instance = new MutantRat(input, render);
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
MutantRat::MutantRat(Input* input, Render* render) : Enemy(EnemyType::MUTANTRAT)
{
    this->input = input;
    this->render = render;


    texture = NULL;
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
}
// Destructor
MutantRat::~MutantRat()
{}



bool MutantRat::Update(float dt)
{
    return true;
}


bool MutantRat::Draw()
{
    if (infoEntities.info.HP > 0)
    {
        // TODO: Calculate the corresponding rectangle depending on the
        // animation state and animation frame
        //SDL_Rect rec = { 0 };
        //render->DrawTexture(texture, position.x, position.y, rec);

        render->DrawRectangle(GetBounds(), 255, 0, 0, 255);
    }

    return false;
}



void MutantRat::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect MutantRat::GetBounds()
{
    return { position.x, position.y, width, height };
}
