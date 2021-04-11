#include "StandardPirates.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
//#include "Textures.h"



StandardPirates* StandardPirates::instance = nullptr;
// Instance creator
StandardPirates* StandardPirates::GetInstance(Input* input, Render* render)
{
    instance = new StandardPirates(input, render);
    LOG("Returning standart pirate instance");

    return instance;
}
// Instance reseter
void StandardPirates::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
StandardPirates::StandardPirates(Input* input, Render* render) : Enemy(EnemyType::STANDARTPIRATE)
{
    this->input = input;
    this->render = render;


    texture = NULL;
    position = iPoint(0, 0);

    width = 16;
    height = 32;

    //Hero stats
    standardPirate.stats.HP = 15;
    standardPirate.stats.SP = 10;
    standardPirate.stats.LVL = 1;
    standardPirate.stats.ATK = 6;
    standardPirate.stats.DEF = 3;
    standardPirate.stats.SPL = 5;
    standardPirate.stats.SPD = 7;
    standardPirate.stats.AGL = 8;
    standardPirate.stats.LCK = 2;

    // Define Player animations
}
// Destructor
StandardPirates::~StandardPirates()
{}



bool StandardPirates::Update(float dt)
{
    return true;
}


bool StandardPirates::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    render->DrawRectangle(GetBounds(), 255, 0, 0, 255);

    return false;
}



void StandardPirates::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect StandardPirates::GetBounds()
{
    return { position.x, position.y, width, height };
}
