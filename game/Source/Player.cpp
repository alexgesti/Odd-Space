#include "Player.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"

#include "Collision.h"
#include "Animation.h"

Player* Player::instance = nullptr;
// Instance creator
Player* Player::GetInstance(Input* input, Render* render, Textures* tex)
{
    if (instance == nullptr) instance = new Player(input, render, tex);
    //else LOG("Returning player instance");

    return instance;
}
// Instance reseter
void Player::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
Player::Player(Input* input, Render* render, Textures* tex) : Entity(EntityType::PLAYER)
{
    this->input = input;
    this->render = render;
    this->tex = tex;

    //
    // Animation pushbacks
    //
    animHeroWalkUp->loop = true;
    animHeroWalkUp->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animHeroWalkUp->PushBack({ 64 * i, 0, 64, 98 });
    animHeroWalkUp->PushBack({ 64, 0, 64, 98 });

    animHeroWalkDown->loop = true;
    animHeroWalkDown->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animHeroWalkDown->PushBack({ 64 * i, 98, 64, 98 });
    animHeroWalkDown->PushBack({ 64, 98, 64, 98 });

    animHeroWalkLeft->loop = true;
    animHeroWalkLeft->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animHeroWalkLeft->PushBack({ 64 * i, 296, 64, 98 });
    animHeroWalkLeft->PushBack({ 64, 296, 64, 98 });

    animHeroWalkRight->loop = true;
    animHeroWalkRight->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animHeroWalkRight->PushBack({ 64 * i, 196, 64, 98 });
    animHeroWalkRight->PushBack({ 64, 196, 64, 98 });

    //
    // Load textures
    //
    //heroTexture = this->tex->Load("assets/sprites/player/cyborg_spritesheet_48x96px.png");
    heroTexture = this->tex->Load("assets/sprites/player/char_maincharacter_v01_w.png");
    oldCaptainTexture = NULL;


    position = iPoint(12 * 16, 27 * 16);

    width = 32;
    height = 32;

    playerCollision[0] = { 0, 0 };
    playerCollision[1] = { width, 0 };
    playerCollision[2] = { 0, height };
    playerCollision[3] = {  width, height };

    //Hero stats
    hero.name = "Hero";
    hero.stats.HP = 15;
    hero.stats.SP = 10;
    hero.stats.LVL = 1;
    hero.stats.ATK = 6;
    hero.stats.DEF = 3;
    hero.stats.SPL = 5;
    hero.stats.SPD = 7;
    hero.stats.AGL = 8;
    hero.stats.LCK = 2;

    //Old captain stats
    oldCaptain.name = "Old Captain";
    oldCaptain.stats.HP = 20;
    oldCaptain.stats.SP = 16;
    oldCaptain.stats.LVL = 1;
    oldCaptain.stats.ATK = 3;
    oldCaptain.stats.DEF = 6;
    oldCaptain.stats.SPL = 5;
    oldCaptain.stats.SPD = 3;
    oldCaptain.stats.AGL = 2;
    oldCaptain.stats.LCK = 1;

    // Define Player animations

    // Set collision player variable to this player instance


    currentAnimation = animHeroWalkDown;
}
// Destructor
Player::~Player()
{}



bool Player::Update(float dt)
{
    GamePad& pad = input->pads[0];

    if (collision->player == nullptr) collision->player = this;

    // Temporary position used for collisions
    temPos = position;

    if (!transitioning) // Don't move while transitioning between scenes
    {
        // +1 makes velocities equal on both directions
        if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || pad.l_x < -0.5f)
        {
            position.x -= (PLAYER_MOVE_SPEED * dt);
            if (currentAnimation != animHeroWalkLeft) currentAnimation = animHeroWalkLeft;
        }
        if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || pad.l_x > 0.5f)
        {
            position.x += (PLAYER_MOVE_SPEED * dt + 1);
            if (currentAnimation != animHeroWalkRight) currentAnimation = animHeroWalkRight;
        }

        if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || pad.l_y < 0.5f)
        {
            position.y -= (PLAYER_MOVE_SPEED * dt);
            if (currentAnimation != animHeroWalkUp) currentAnimation = animHeroWalkUp;
        }
        if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || pad.l_y > -0.5f)
        {
            position.y += (PLAYER_MOVE_SPEED * dt + 1);
            if (currentAnimation != animHeroWalkDown) currentAnimation = animHeroWalkDown;
        }

        if (input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) interacting = true;
        else interacting = false;
    }


    currentAnimation->Update();

    return true;
}


bool Player::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    //render->DrawRectangle(GetBounds(), 0, 255, 0, 255);
    SDL_Rect rect = currentAnimation->GetCurrentFrame();
    render->DrawTexture(heroTexture, (int)position.x - 8, (int)position.y - 64, &rect);


    return false;
}



SDL_Rect Player::GetBounds()
{
    return { position.x, position.y, width, height };
}

void Player::SetCollision(Collision* collision, Player* player)
{
    player->collision = collision;
}