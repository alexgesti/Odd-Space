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
    }

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
{
    UnLoad();
}



bool Jug::Update(float dt)
{
    return true;
}

void Jug::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (*HP > 0) *SP += maxSP * 0.5;
    if (*SP >= maxSP) *SP = maxSP;
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
    render = nullptr;

    return false;
}