#include "Jug.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



Jug* Jug::instance = nullptr;
// Instance creator
Jug* Jug::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr)
    {
        instance = new Jug(render, tex);
        LOG("Returning Jug instance");
        instance->quantity = 1;
    }
    else instance->quantity++;

    return instance;
}
// Instance reseter
void Jug::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
Jug::Jug(Render* render, Textures* tex) : Item(ItemType::JUG)
{
    this->render = render;

    infoEntities.info.name = "Jug";
}
// Destructor
Jug::~Jug()
{}



bool Jug::Update(float dt)
{
    return true;
}

void Jug::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (quantity > 0)
    {
        quantity--;
        if (*HP > 0) *SP += maxSP * 0.5;
        if (*SP >= maxSP) *SP = maxSP;
    }
}


bool Jug::Draw()
{

    return false;
}


void Jug::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

bool Jug::UnLoad()
{   

    return false;
}