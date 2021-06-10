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
    }

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
{
    UnLoad();
}



bool ElaboratedPlate::Update(float dt)
{
    return true;
}

void ElaboratedPlate::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (*HP > 0) *HP += maxHP * 0.5;
    if (*HP >= maxHP) *HP = maxHP;
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
    render = nullptr;

    return false;
}