#include "Player.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"

#include "Collision.h"
//#include "Textures.h"



Player* Player::instance = nullptr;
// Instance creator
Player* Player::GetInstance(Input* input, Render* render)
{
    if (instance == nullptr) instance = new Player(input, render);
    else LOG("Returning player instance");

    return instance;
}
// Instance reseter
void Player::ResetInstance()
{
    delete instance;
    instance = nullptr;
}
// Constructor
Player::Player(Input* input, Render* render) : Entity(EntityType::PLAYER)
{
    this->input = input;
    this->render = render;


    texture = NULL;
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
    oldCaptain.stats.ATK = 3;
    oldCaptain.stats.DEF = 6;
    oldCaptain.stats.SPL = 5;
    oldCaptain.stats.SPD = 3;
    oldCaptain.stats.AGL = 2;
    oldCaptain.stats.LCK = 1;

    // Define Player animations

    // Set collision player variable to this player instance
}
// Destructor
Player::~Player()
{}



bool Player::Update(float dt)
{
    if (collision->player == nullptr) collision->player = this;

    // Temporary position used for collisions
    temPos = position;

    if (!transitioning) // Don't move while transitioning between scenes
    {
        // +1 makes velocities equal on both directions
        if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
            position.x -= (PLAYER_MOVE_SPEED * dt);
        if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt + 1);

        if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y -= (PLAYER_MOVE_SPEED * dt);
        if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) position.y += (PLAYER_MOVE_SPEED * dt + 1);
    }

    return true;
}


bool Player::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    render->DrawRectangle(GetBounds(), 0, 255, 0, 255);

    return false;
}



void Player::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect Player::GetBounds()
{
    return { position.x, position.y, width, height };
}

void Player::SetCollision(Collision* collision, Player* player)
{
    player->collision = collision;
}