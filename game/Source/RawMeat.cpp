#include "RawMeat.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"

RawMeat* RawMeat::instance = nullptr;
// Instance creator
RawMeat* RawMeat::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr)
    {
        instance = new RawMeat(render, tex);
        LOG("Returning Raw Meat instance");
    }

    return instance;
}
// Instance reseter
void RawMeat::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
RawMeat::RawMeat(Render* render, Textures* tex) : Item(ItemType::RAWMEAT)
{
    this->render = render;

    infoEntities.info.name = "Raw Meat";
}
// Destructor
RawMeat::~RawMeat()
{}



bool RawMeat::Update(float dt)
{
    return true;
}

void RawMeat::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (*HP > 0) *HP += maxHP * 0.25;
    if (*HP >= maxHP) *HP = maxHP;
}


bool RawMeat::Draw()
{

    return false;
}


void RawMeat::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

bool RawMeat::UnLoad()
{   

    return false;
}