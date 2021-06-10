#include "StrongRon.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"


StrongRon* StrongRon::instance = nullptr;
// Instance creator
StrongRon* StrongRon::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr)
    {
        instance = new StrongRon(render, tex);
        LOG("Returning Strong Ron instance");
    }

    return instance;
}
// Instance reseter
void StrongRon::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
StrongRon::StrongRon(Render* render, Textures* tex) : Item(ItemType::STRONGRON)
{
    this->render = render;

    infoEntities.info.name = "Strong Ron";
}
// Destructor
StrongRon::~StrongRon()
{
    UnLoad();
}



bool StrongRon::Update(float dt)
{
    return true;
}

void StrongRon::ItemFunction(int* HP, int* SP, int maxHP, int maxSP)
{
    if (*HP <= 0) *HP = maxHP * 0.5;
}


bool StrongRon::Draw()
{

    return false;
}



void StrongRon::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

bool StrongRon::UnLoad()
{   
    render = nullptr;

    return false;
}