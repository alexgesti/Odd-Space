#include "OldCaptain.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"

#include "Collision.h"
//#include "Textures.h"



Captain* Captain::instance = nullptr;
// Instance creator
Captain* Captain::GetInstance(Input* input, Render* render)
{
    if (instance == nullptr) instance = new Captain(input, render);
    //else LOG("Returning player instance");

    return instance;
}
// Instance reseter
void Captain::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
Captain::Captain(Input* input, Render* render) : Entity(EntityType::CAPTAIN)
{
    this->input = input;
    this->render = render;


    texture = NULL;
    position = iPoint (12 * 16, 27 * 16);

    width = 32;
    height = 32;

    //Hero stats
    infoEntities.info.name = "Old Captain";
    infoEntities.info.HP = 20;
    infoEntities.info.SP = 15;
    infoEntities.info.maxHP = 20;
    infoEntities.info.maxSP = 15;
    infoEntities.info.LVL = 1;
    infoEntities.stats.ATK = 6;
    infoEntities.stats.DEF = 10;
    infoEntities.stats.SPD = 4;
    infoEntities.stats.LCK = 4;
    infoEntities.defense = false;
    infoEntities.attack = false;

    //Hero skills
    infoEntities.skills[0].name = "Crazy Noise";
    infoEntities.skills[0].cost = 3;
    infoEntities.skills[0].picked = false;
    infoEntities.skills[1].name = "Old Scars";
    infoEntities.skills[1].cost = 6;
    infoEntities.skills[1].picked = false;
    infoEntities.skills[2].name = "Share a drink";
    infoEntities.skills[2].picked = false;
    infoEntities.skills[2].cost = 5;
    infoEntities.skills[3].name = "War cry";
    infoEntities.skills[3].cost = 8;
    infoEntities.skills[3].picked = false;
    infoEntities.skills[4].name = "Wake up";
    infoEntities.skills[4].cost = 12;
    infoEntities.skills[4].picked = false;

    // Define Player animations
}
// Destructor
Captain::~Captain()
{}



bool Captain::Update(float dt)
{

    return true;
}


bool Captain::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    render->DrawRectangle(GetBounds(), 0, 255, 0, 255);

    return false;
}



void Captain::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect Captain::GetBounds()
{
    return { position.x, position.y, width, height };
}