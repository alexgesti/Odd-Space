#include "StandardPirate.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



StandardPirates* StandardPirates::instance = nullptr;
// Instance creator
StandardPirates* StandardPirates::GetInstance(Render* render, Textures* tex)
{
    instance = new StandardPirates(render, tex);
    LOG("Returning drunk customer instance");

    return instance;
}
// Instance reseter
void StandardPirates::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
StandardPirates::StandardPirates(Render* render, Textures* tex) : Enemy(EnemyType::STANDARTPIRATE)
{
    this->render = render;
    this->tex = tex;

    standardPirateTexture = NULL;
    position = iPoint(0, 0);

    width = 16;
    height = 32;

    //Drunk Customer stats
    infoEntities.info.name = "Drunk Customer";
    infoEntities.info.HP = 22;
    infoEntities.info.LVL = 2;
    infoEntities.stats.ATK = 8;
    infoEntities.stats.DEF = 7;
    infoEntities.stats.SPD = 4;
    infoEntities.stats.LCK = 5;

    // Define Player animations
    standardPirateTexture = this->tex->Load("sprites/enemies/nme_aggressivedrunkman_w.png");

    standardPirateAnim->loop = true;
    standardPirateAnim->speed = 0.15f;

    standardPirateAnim->PushBack({ 0, 0, 112, 128 });
    standardPirateAnim->PushBack({ 112, 0, 112, 128 });
    standardPirateAnim->PushBack({ 224, 0, 112, 128 });
    standardPirateAnim->PushBack({ 112, 0, 112, 128 });

    //Define Hurt Texture
    hurtTexture = this->tex->Load("sprites/combat/cmb_hurt.png");
}
// Destructor
StandardPirates::~StandardPirates()
{}



bool StandardPirates::Update(float dt)
{
    standardPirateAnim->Update();
    return true;
}


bool StandardPirates::Draw()
{
    if (infoEntities.info.HP > 0)
    {
        // TODO: Calculate the corresponding rectangle depending on the
        // animation state and animation frame
        SDL_Rect rec = standardPirateAnim->GetCurrentFrame();
        render->DrawTexture(standardPirateTexture, position.x, position.y, &rec);

        rec = hurtAnim->GetCurrentFrame();
        render->DrawTexture(hurtTexture, position.x, position.y, &rec);
    }

    return false;
}

void StandardPirates::SetTexture(SDL_Texture* tex)
{
    standardPirateTexture = tex;
}

SDL_Rect StandardPirates::GetBounds()
{
    return { position.x, position.y, width, height };
}

bool StandardPirates::UnLoad()
{
    tex->UnLoad(standardPirateTexture);

    delete standardPirateAnim;
    standardPirateAnim = nullptr;

    return false;
}