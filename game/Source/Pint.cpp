#include "Pint.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



Pint* Pint::instance = nullptr;
// Instance creator
Pint* Pint::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr)
    {
        instance = new Pint(render, tex);
        LOG("Returning Pint instance");
    }

    return instance;
}
// Instance reseter
void Pint::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
Pint::Pint(Render* render, Textures* tex) : Item(ItemType::PINT)
{
    this->render = render;

    infoEntities.info.name = "Pint";
}
// Destructor
Pint::~Pint()
{
    UnLoad();
}



bool Pint::Update(float dt)
{
    return true;
}

void Pint::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (*HP > 0) *SP += maxSP * 0.25;
    if (*SP >= maxSP) *SP = maxSP;
}


bool Pint::Draw()
{

    return false;
}


void Pint::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

bool Pint::UnLoad()
{   
    render = nullptr;

    return false;
}