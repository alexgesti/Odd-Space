#include "LargeRawMeat.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



LargeRawMeat* LargeRawMeat::instance = nullptr;
// Instance creator
LargeRawMeat* LargeRawMeat::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr)
    {
        instance = new LargeRawMeat(render, tex);
        LOG("Returning Large Raw Meat instance");
    }

    return instance;
}
// Instance reseter
void LargeRawMeat::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
LargeRawMeat::LargeRawMeat(Render* render, Textures* tex) : Item(ItemType::LARGERAWMEAT)
{
    this->render = render;

    infoEntities.info.name = "Large Raw Meat";
}
// Destructor
LargeRawMeat::~LargeRawMeat()
{}



bool LargeRawMeat::Update(float dt)
{
    return true;
}

void LargeRawMeat::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (*HP > 0) *HP += maxHP * 0.5;
    if (*HP >= maxHP) *HP = maxHP;
}


bool LargeRawMeat::Draw()
{

    return false;
}


void LargeRawMeat::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

bool LargeRawMeat::UnLoad()
{   

    return false;
}