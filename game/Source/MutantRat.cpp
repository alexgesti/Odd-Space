#include "MutantRat.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
//#include "Textures.h"



MutantRat* MutantRat::instance = nullptr;
// Instance creator
MutantRat* MutantRat::GetInstance(Input* input, Render* render)
{
    if (instance == nullptr) instance = new MutantRat(input, render);
    else LOG("Returning standart pirate instance");

    return instance;
}
// Instance reseter
void MutantRat::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
MutantRat::MutantRat(Input* input, Render* render) : Enemy(EnemyType::STANDARTPIRATE)
{
    this->input = input;
    this->render = render;


    texture = NULL;
    position = iPoint(12 * 16, 27 * 16);

    width = 16;
    height = 32;

    //Hero stats
    mutantRat.stats.HP = 45;
    mutantRat.stats.SP = 0;
    mutantRat.stats.ATK = 30;
    mutantRat.stats.DEF = 12;
    mutantRat.stats.SPL = 3;
    mutantRat.stats.SPD = 18;
    mutantRat.stats.AGL = 21;
    mutantRat.stats.LCK = 9;

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
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    render->DrawRectangle(GetBounds(), 0, 255, 0, 255);

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
