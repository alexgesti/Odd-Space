#include "Player.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
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

    // Define Player animations
}
// Destructor
Player::~Player()
{}



bool Player::Update(float dt)
{
    #define PLAYER_MOVE_SPEED 150.0f

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
