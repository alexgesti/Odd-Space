#include "OldCaptain.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



Captain* Captain::instance = nullptr;
// Instance creator
Captain* Captain::GetInstance(Render* render, Textures* tex)
{
    if (instance == nullptr) instance = new Captain(render, tex);
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
Captain::Captain(Render* render, Textures* tex) : Entity(EntityType::CAPTAIN)
{
    this->render = render;
    this->tex = tex;

    //
    // Animation pushbacks
    //
    animOldCaptainWalkUp->loop = true;
    animOldCaptainWalkUp->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animOldCaptainWalkUp->PushBack({ 48 * i, 0, 48, 96 });
    animOldCaptainWalkUp->PushBack({ 48, 0, 48, 96 });

    animOldCaptainWalkDown->loop = true;
    animOldCaptainWalkDown->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animOldCaptainWalkDown->PushBack({ 48 * i, 96, 48, 96 });
    animOldCaptainWalkDown->PushBack({ 48, 96, 48, 96 });

    animOldCaptainWalkLeft->loop = true;
    animOldCaptainWalkLeft->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animOldCaptainWalkLeft->PushBack({ 48 * i, 192, 48, 96 });
    animOldCaptainWalkLeft->PushBack({ 48 , 192, 48, 96 });

    animOldCaptainWalkRight->loop = true;
    animOldCaptainWalkRight->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animOldCaptainWalkRight->PushBack({ 48 * i, 288, 48, 96 });
    animOldCaptainWalkRight->PushBack({ 48, 288, 48, 96 });


    //
    // Load textures
    //
    oldCaptainTexture = this->tex->Load("sprites/player/char_oldcaptain_w.png");
    
    
    position = iPoint (12 * 16, 27 * 16);

    width = 32;
    height = 32;

    //Hero stats
    infoEntities.info.name = "Captain";
    infoEntities.info.HP = 50;
    infoEntities.info.SP = 15;
    infoEntities.info.maxHP = 50;
    infoEntities.info.maxSP = 15;
    infoEntities.info.LVL = 1;
    infoEntities.info.XP = 0;
    infoEntities.info.maxXP = 50;
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
    infoEntities.skills[2].name = "Share drink";
    infoEntities.skills[2].cost = 5;
    infoEntities.skills[2].picked = false;
    infoEntities.skills[3].name = "War cry";
    infoEntities.skills[3].cost = 8;
    infoEntities.skills[3].picked = false;
    infoEntities.skills[4].name = "Wake up";
    infoEntities.skills[4].cost = 12;
    infoEntities.skills[4].picked = false;

    // Define Old Captain current animation
    currentAnimation = animOldCaptainWalkDown;

    //Define Hurt Texture
    hurtTexture = this->tex->Load("sprites/combat/cmb_hurt.png");

    //Define Shield Texture
    shieldTexture = this->tex->Load("sprites/combat/cmb_shield.png");

    //Define Death Texture
    deathTexture = this->tex->Load("sprites/combat/cmb_death.png");
}
// Destructor
Captain::~Captain()
{
    tex->UnLoad(oldCaptainTexture);
    tex->UnLoad(hurtTexture);
    tex->UnLoad(shieldTexture);
    tex->UnLoad(deathTexture);

    RELEASE(hurtAnim);
    RELEASE(deathAnim);

    RELEASE(animOldCaptainWalkUp);
    RELEASE(animOldCaptainWalkDown);
    RELEASE(animOldCaptainWalkLeft);
    RELEASE(animOldCaptainWalkRight);

    currentAnimation = nullptr;

    render = nullptr;
    tex = nullptr;
}



bool Captain::Update(float dt)
{
    // Temporary position used for animation render
    temPos = position;


    if (inBattle == true)
    {
        currentAnimation = animOldCaptainWalkRight;
        currentAnimation->SetCurrentFrame(1);
        if (infoEntities.info.HP <= 0) deathAnim->Update();
    }
    else
    {
        if (position == temPos) currentAnimation->SetCurrentFrame(1);
        else currentAnimation->Update();
    }

    return true;
}


bool Captain::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    //render->DrawRectangle(GetBounds(), 0, 255, 0, 255);
    if (inBattle == true)
    {
        if (infoEntities.info.HP > 0)
        {
            SDL_Rect rect = currentAnimation->GetCurrentFrame();
            render->DrawTexture(oldCaptainTexture, (int)position.x - 8, (int)position.y - 64, &rect);
        }
        else if (infoEntities.info.HP <= 0) 
        {
            SDL_Rect rect_death = deathAnim->GetCurrentFrame();
            render->DrawTexture(deathTexture, (int)position.x - 40, (int)position.y - 64, &rect_death); 
        }

        SDL_Rect rect_hurt = hurtAnim->GetCurrentFrame();
        render->DrawTexture(hurtTexture, (int)position.x, (int)position.y - 64, &rect_hurt);

        if (infoEntities.defense && infoEntities.info.HP > 0)
        {
            SDL_Rect rect_def = { 0, 0, 64, 96 };
            render->DrawTexture(shieldTexture, (int)position.x + 40, (int)position.y - 64, &rect_def);
        }
    }

    return false;
}


SDL_Rect Captain::GetBounds()
{
    return { position.x, position.y, width, height };
}

void Captain::AddXP(int xp)
{
    int total = infoEntities.info.XP + xp;

    // While loop in case we increase more than 1 level
    while (total > infoEntities.info.maxXP)
    {
        infoEntities.info.LVL++;
        total -= infoEntities.info.maxXP;
        infoEntities.info.maxXP += 50 * infoEntities.info.LVL;
    }

    infoEntities.info.XP = total;
}