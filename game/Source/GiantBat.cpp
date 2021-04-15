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

    //Giant Bat stats
    infoEntities.info.name = "Giant Bat";
    infoEntities.info.HP = 10;
    infoEntities.info.LVL = 4;
    infoEntities.stats.ATK = 5;
    infoEntities.stats.DEF = 4;
    infoEntities.stats.SPD = 10;
    infoEntities.stats.LCK = 5;

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
    if (infoEntities.info.HP > 0)
    {
        // TODO: Calculate the corresponding rectangle depending on the
        // animation state and animation frame
        //SDL_Rect rec = { 0 };
        //render->DrawTexture(texture, position.x, position.y, rec);

        render->DrawRectangle(GetBounds(), 0, 255, 0, 255);
    }

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
