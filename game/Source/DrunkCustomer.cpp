#include "DrunkCustomer.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
//#include "Textures.h"



DrunkCustomer* DrunkCustomer::instance = nullptr;
// Instance creator
DrunkCustomer* DrunkCustomer::GetInstance(Input* input, Render* render)
{
    if (instance == nullptr) instance = new DrunkCustomer(input, render);
    else LOG("Returning standart pirate instance");

    return instance;
}
// Instance reseter
void DrunkCustomer::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
DrunkCustomer::DrunkCustomer(Input* input, Render* render) : Enemy(EnemyType::STANDARTPIRATE)
{
    this->input = input;
    this->render = render;


    texture = NULL;
    position = iPoint(12 * 16, 27 * 16);

    width = 16;
    height = 32;

    //Hero stats
    drunkCustomer.stats.HP = 40;
    drunkCustomer.stats.SP = 0;
    drunkCustomer.stats.ATK = 14;
    drunkCustomer.stats.DEF = 4;
    drunkCustomer.stats.SPL = 2;
    drunkCustomer.stats.SPD = 4;
    drunkCustomer.stats.AGL = 2;
    drunkCustomer.stats.LCK = 6;

    // Define Player animations
}
// Destructor
DrunkCustomer::~DrunkCustomer()
{}



bool DrunkCustomer::Update(float dt)
{
    return true;
}


bool DrunkCustomer::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    render->DrawRectangle(GetBounds(), 0, 255, 0, 255);

    return false;
}



void DrunkCustomer::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect DrunkCustomer::GetBounds()
{
    return { position.x, position.y, width, height };
}
