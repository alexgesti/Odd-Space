#include "GiantBat.h"

#include "Log.h"

#include "Render.h"
#include "Textures.h"



GiantBat* GiantBat::instance = nullptr;
// Instance creator
GiantBat* GiantBat::GetInstance(Render* render,Textures* tex)
{
    instance = new GiantBat(render, tex);
    LOG("Returning giant bat instance");

    return instance;
}
// Instance reseter
void GiantBat::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
GiantBat::GiantBat(Render* render, Textures* tex) : Enemy(EnemyType::GIANTBAT)
{
    this->render = render;
    this->tex = tex;

    giantBatTexture = NULL;
    position = iPoint(0, 0);

    width = 16;
    height = 32;

    //Giant Bat stats
    infoEntities.info.name = "Giant Bat";
    infoEntities.info.HP = 10;
    infoEntities.info.LVL = 4;
    infoEntities.stats.ATK = 5;
    infoEntities.stats.DEF = 4;
    infoEntities.stats.SPD = 10;
    infoEntities.stats.LCK = 5;

    // Define Player animations
    giantBatTexture = this->tex->Load("assets/sprites/enemies/char_enemybat_v01_w.png");

    giantBatAnim->loop = true;
    giantBatAnim->speed = 0.25f;

    giantBatAnim->PushBack({ 0, 0, 97, 79 });
    giantBatAnim->PushBack({ 97, 0, 97, 79 });
    giantBatAnim->PushBack({ 194, 0, 97, 79 });
    giantBatAnim->PushBack({ 97, 0, 97, 79 });

    //Define Hurt Texture
    hurtTexture = this->tex->Load("assets/sprites/combat/cmb_hurt_v01.png");
}
// Destructor
GiantBat::~GiantBat()
{}



bool GiantBat::Update(float dt)
{
    giantBatAnim->Update();
    return true;
}


bool GiantBat::Draw()
{
    if (infoEntities.info.HP > 0)
    {
        // TODO: Calculate the corresponding rectangle depending on the
        // animation state and animation frame
        SDL_Rect rec = giantBatAnim->GetCurrentFrame();
        render->DrawTexture(giantBatTexture, position.x, position.y, &rec);

        rec = hurtAnim->GetCurrentFrame();
        render->DrawTexture(hurtTexture, position.x, position.y, &rec);
    }

    return false;
}



void GiantBat::SetTexture(SDL_Texture *tex)
{
    giantBatTexture = tex;
}

SDL_Rect GiantBat::GetBounds()
{
    return { position.x, position.y, width, height };
}

bool GiantBat::UnLoad()
{
    tex->UnLoad(giantBatTexture);

    delete giantBatAnim;
    giantBatAnim = nullptr;

    return false;
}
