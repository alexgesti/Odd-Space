#include "Player.h"

#include "Log.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"

#include "Collision.h"



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
Player::Player(Input* input, Render* render, Textures* tex) : Entity(EntityType::HERO)
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


    position = iPoint(12 * 16, 27 * 16);

    width = 32;
    height = 32;

    playerCollision[0] = { 0, 0 };
    playerCollision[1] = { width, 0 };
    playerCollision[2] = { 0, height };
    playerCollision[3] = {  width, height };

    //Hero stats
    infoEntities.info.name = "Hero";
    infoEntities.info.HP = 15;
    infoEntities.info.SP = 10;
    infoEntities.info.maxHP = 15;
    infoEntities.info.maxSP = 10;
    infoEntities.info.LVL = 1;
    infoEntities.stats.ATK = 8;
    infoEntities.stats.DEF = 4;
    infoEntities.stats.SPD = 9;
    infoEntities.stats.LCK = 3;
    infoEntities.defense = false;
    infoEntities.attack = false;

    //Hero skills
    infoEntities.skills[0].name = "Lucky Slash";
    infoEntities.skills[0].cost = 2;
    infoEntities.skills[0].picked = false;
    infoEntities.skills[1].name = "Spatula-Boomerang";
    infoEntities.skills[1].cost = 4;
    infoEntities.skills[1].picked = false;
    infoEntities.skills[2].name = "Light Recovery";
    infoEntities.skills[2].cost = 3;
    infoEntities.skills[2].picked = false;
    infoEntities.skills[3].name = "Steal";
    infoEntities.skills[3].cost = 8;
    infoEntities.skills[3].picked = false;
    infoEntities.skills[4].name = "Triple Spatula";
    infoEntities.skills[4].cost = 10;
    infoEntities.skills[4].picked = false;

    // Define Player current animation
    currentAnimation = animHeroWalkDown;
}
// Destructor
Player::~Player()
{}



bool Player::Update(float dt)
{
    GamePad& pad = input->pads[0];

    if (noClip == false) collision->player = this;
    else collision->player = nullptr;

    // Temporary position used for collisions
    temPos = position;

    if (!transitioning && !isPause && !inConversation) // Don't move while transitioning between scenes
    {
        // +1 makes velocities equal on both directions
        if ((input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && input->joystickState() == false || (pad.l_x < -0.25f && pad.l_y > -0.75f && pad.l_y < 0.75f) && input->joystickState() == true)
        {
            position.x -= (PLAYER_MOVE_SPEED * dt);
            if (currentAnimation != animHeroWalkLeft) currentAnimation = animHeroWalkLeft;
        }
        if ((input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && input->joystickState() == false || (pad.l_x > 0.25f && pad.l_y > -0.75f && pad.l_y < 0.75f) && input->joystickState() == true)
        {
            position.x += (PLAYER_MOVE_SPEED * dt + 1);
            if (currentAnimation != animHeroWalkRight) currentAnimation = animHeroWalkRight;
        }

        if ((input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && input->joystickState() == false || (pad.l_y < 0.25f && pad.l_x > -0.75f && pad.l_x < 0.75f) && input->joystickState() == true)
        {
            position.y -= (PLAYER_MOVE_SPEED * dt);
            //render->camera.y += (PLAYER_MOVE_SPEED * dt);
            if (currentAnimation != animHeroWalkUp) currentAnimation = animHeroWalkUp;
        }
        if ((input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) && input->joystickState() == false || (pad.l_y > -0.25f && pad.l_x > -0.75f && pad.l_x < 0.75f) && input->joystickState() == true)
        {
            position.y += (PLAYER_MOVE_SPEED * dt + 1);
            //render->camera.y -= (PLAYER_MOVE_SPEED * dt + 1);
            if (currentAnimation != animHeroWalkDown) currentAnimation = animHeroWalkDown;
        }

        if (input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) interacting = true;
        else interacting = false;
    }

    if(inBattle == true) currentAnimation = animHeroWalkRight;
    else
    {
        if (position == temPos) currentAnimation->SetCurrentFrame(1);
        else currentAnimation->Update();
    }

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
    render->DrawTexture(heroTexture, (int)position.x - 16, (int)position.y - 64, &rect);


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