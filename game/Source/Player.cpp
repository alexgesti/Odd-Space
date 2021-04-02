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

    width = 16;
    height = 32;

    playerCollision[0] = { 0, 0 };
    playerCollision[1] = { width, 0 };
    playerCollision[2] = { 0, height };
    playerCollision[3] = {  width, height };

    //Hero stats
  /*stats[1].HP = 15;
    stats[1].SP = 10;
    stats[1].ATK = 6;
    stats[1].DEF = 3;
    stats[1].SPL = 5;
    stats[1].SPD = 7;
    stats[1].AGL = 8;
    stats[1].LCK = 2;

    //Old captain stats
    stats[2].HP = 20;
    stats[2].SP = 16;
    stats[2].ATK = 3;
    stats[2].DEF = 6;
    stats[2].SPL = 5;
    stats[2].SPD = 3;
    stats[2].AGL = 2;
    stats[2].LCK = 1;*/

    // Define Player animations

    // Set collision player variable to this player instance
}
// Destructor
Player::~Player()
{}



bool Player::Update(float dt)
{
    if (collision->player == nullptr) collision->player = this;

    #define PLAYER_MOVE_SPEED 150.0f

    // Temporary position used for collisions
    temPos = position;

    //if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y += (PLAYER_MOVE_SPEED * dt);
    //if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) position.y -= (PLAYER_MOVE_SPEED * dt);
    if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
    if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);

    if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y -= (PLAYER_MOVE_SPEED * dt);
    if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) position.y += (PLAYER_MOVE_SPEED * dt);

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