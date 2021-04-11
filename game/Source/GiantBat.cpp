#include "GiantBat.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
//#include "Textures.h"



GiantBat* GiantBat::instance = nullptr;
// Instance creator
GiantBat* GiantBat::GetInstance(Input* input, Render* render)
{
    instance = new GiantBat(input, render);
    LOG("Returning giant bat instance");

    return instance;
}
// Instance reseter
void GiantBat::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
GiantBat::GiantBat(Input* input, Render* render) : Enemy(EnemyType::GIANTBAT)
{
    this->input = input;
    this->render = render;


    texture = NULL;
    position = iPoint(0, 0);

    width = 16;
    height = 32;

    //Hero stats
    giantBat.stats.HP = 60;
    giantBat.stats.SP = 0;
    giantBat.stats.LVL = 4;
    giantBat.stats.ATK = 20;
    giantBat.stats.DEF = 24;
    giantBat.stats.SPL = 40;
    giantBat.stats.SPD = 32;
    giantBat.stats.AGL = 16;
    giantBat.stats.LCK = 12;

    // Define Player animations
}
// Destructor
GiantBat::~GiantBat()
{}



bool GiantBat::Update(float dt)
{
    return true;
}


bool GiantBat::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    render->DrawRectangle(GetBounds(), 0, 255, 0, 255);

    return false;
}



void GiantBat::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect GiantBat::GetBounds()
{
    return { position.x, position.y, width, height };
}
