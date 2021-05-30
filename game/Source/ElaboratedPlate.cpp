#include "ElaboratedPlate.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



ElaboratedPlate* ElaboratedPlate::instance = nullptr;
// Instance creator
ElaboratedPlate* ElaboratedPlate::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr)
    {
        instance = new ElaboratedPlate(render, tex);
        LOG("Returning Elaborated Plate instance");
        instance->quantity = 1;
    }
    else instance->quantity++;

    return instance;
}
// Instance reseter
void ElaboratedPlate::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
ElaboratedPlate::ElaboratedPlate(Render* render, Textures* tex) : Item(ItemType::ELABORATEDPLATE)
{
    this->render = render;

    infoEntities.info.name = "Elaborated Plate";
}
// Destructor
ElaboratedPlate::~ElaboratedPlate()
{}



bool ElaboratedPlate::Update(float dt)
{
    return true;
}

void ElaboratedPlate::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (quantity > 0)
    {
        quantity--;
        if (*HP > 0) *HP += maxHP * 0.5;
        if (*HP >= maxHP) *HP = maxHP;
        LOG("Elaboratedworking");
    }
}


bool ElaboratedPlate::Draw()
{

    return false;
}


void ElaboratedPlate::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

bool ElaboratedPlate::UnLoad()
{   

    return false;
}