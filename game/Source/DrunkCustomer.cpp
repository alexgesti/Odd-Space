#include "DrunkCustomer.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"



DrunkCustomer* DrunkCustomer::instance = nullptr;
// Instance creator
DrunkCustomer* DrunkCustomer::GetInstance(Input* input, Render* render, Textures* tex)
{
    instance = new DrunkCustomer(input, render, tex);
    LOG("Returning drunk customer instance");

    return instance;
}
// Instance reseter
void DrunkCustomer::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
DrunkCustomer::DrunkCustomer(Input* input, Render* render, Textures* tex) : Enemy(EnemyType::DRUNKCUSTOMER)
{
    this->input = input;
    this->render = render;
    this->tex = tex;

    drunkCustomerTexture = NULL;
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
    drunkCustomerTexture = this->tex->Load("assets/sprites/enemies/char_enemydrunk_v01_w.png");

    drunkCustomerAnim->loop = true;
    drunkCustomerAnim->speed = 0.15f;
   
    drunkCustomerAnim->PushBack({ 0, 0, 70, 78 });
    drunkCustomerAnim->PushBack({ 70, 0, 70, 78 });
    drunkCustomerAnim->PushBack({ 140, 0, 70, 78 });
    drunkCustomerAnim->PushBack({ 70, 0, 70, 78 });
}
// Destructor
DrunkCustomer::~DrunkCustomer()
{}



bool DrunkCustomer::Update(float dt)
{
    drunkCustomerAnim->Update();
    return true;
}


bool DrunkCustomer::Draw()
{
    if (infoEntities.info.HP > 0)
    {
        // TODO: Calculate the corresponding rectangle depending on the
        // animation state and animation frame
        SDL_Rect rec = drunkCustomerAnim->GetCurrentFrame();
        render->DrawTexture(drunkCustomerTexture, position.x, position.y, &rec);

    }

    return false;
}

void DrunkCustomer::SetTexture(SDL_Texture *tex)
{
    drunkCustomerTexture = tex;
}

SDL_Rect DrunkCustomer::GetBounds()
{
    return { position.x, position.y, width, height };
}

bool DrunkCustomer::UnLoad()
{
    tex->UnLoad(drunkCustomerTexture);
    
    delete drunkCustomerAnim;
    
    return false;
}
