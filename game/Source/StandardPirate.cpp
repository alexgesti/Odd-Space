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
    infoEntities.info.name = "Standard Pirate";
    infoEntities.info.HP = 1;
    infoEntities.info.LVL = 1;
    infoEntities.stats.ATK = 0;
    infoEntities.stats.DEF = 0;
    infoEntities.stats.SPD = 0;
    infoEntities.stats.LCK = 0;

    // Define Player animations

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
        SDL_Rect rec;

        render->DrawRectangle(GetBounds(), 255, 0, 0, 255);

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
    tex->UnLoad(hurtTexture);

    RELEASE(hurtAnim);
    RELEASE(deathAnim);

    return false;
}