#include "StandardPirates.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
//#include "Textures.h"



StandardPirates* StandardPirates::instance = nullptr;
// Instance creator
StandardPirates* StandardPirates::GetInstance(Input* input, Render* render)
{
    if (instance == nullptr) instance = new StandardPirates(input, render);
    else LOG("Returning standart pirate instance");

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
    position = iPoint(12 * 16, 27 * 16);

    width = 16;
    height = 32;

    //Hero stats
    /*stats[3].HP = 15;
    stats[3].SP = 10;
    stats[3].ATK = 6;
    stats[3].DEF = 3;
    stats[3].SPL = 5;
    stats[3].SPD = 7;
    stats[3].AGL = 8;
    stats[3].LCK = 2;*/

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

    render->DrawRectangle(GetBounds(), 0, 255, 0, 255);

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
