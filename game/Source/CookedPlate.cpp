#include "CookedPlate.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



CookedPlate* CookedPlate::instance = nullptr;
// Instance creator
CookedPlate* CookedPlate::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr)
    {
        instance = new CookedPlate(render, tex);
        LOG("Returning Cooked Plate instance");
    }

    return instance;
}
// Instance reseter
void CookedPlate::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
CookedPlate::CookedPlate(Render* render, Textures* tex) : Item(ItemType::COOKEDPLATE)
{
    this->render = render;

    infoEntities.info.name = "Cooked Plate";
}
// Destructor
CookedPlate::~CookedPlate()
{
    UnLoad();
}



bool CookedPlate::Update(float dt)
{
    return true;
}

void CookedPlate::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (*HP > 0) *HP += maxHP * 0.25;
    if (*HP >= maxHP) *HP = maxHP;
}


bool CookedPlate::Draw()
{

    return false;
}


void CookedPlate::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

bool CookedPlate::UnLoad()
{   
    render = nullptr;

    return false;
}