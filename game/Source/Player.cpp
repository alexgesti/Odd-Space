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
        animHeroWalkLeft->PushBack({ 64 * i, 196, 64, 98 });
    animHeroWalkLeft->PushBack({ 64, 196, 64, 98 });

    animHeroWalkRight->loop = true;
    animHeroWalkRight->speed = 0.08f;
    for (int i = 0; i < 3; ++i)
        animHeroWalkRight->PushBack({ 64 * i, 294, 64, 98 });
    animHeroWalkRight->PushBack({ 64, 294, 64, 98 });

    animHeroIdleUp->loop = true;
    animHeroIdleUp->speed = 0.08f;
    for (int i = 0; i < 2; ++i)
        animHeroIdleUp->PushBack({ 64 * i, 392, 64, 98 });

    animHeroIdleDown->loop = true;
    animHeroIdleDown->speed = 0.08f;
    for (int i = 0; i < 2; ++i)
        animHeroIdleDown->PushBack({ 64 * i, 490, 64, 98 });

    animHeroIdleLeft->loop = true;
    animHeroIdleLeft->speed = 0.08f;
    for (int i = 0; i < 2; ++i)
        animHeroIdleLeft->PushBack({ 64 * i, 588, 64, 98 });

    animHeroIdleRight->loop = true;
    animHeroIdleRight->speed = 0.08f;
    for (int i = 0; i < 2; ++i)
        animHeroIdleRight->PushBack({ 64 * i, 686, 64, 98 });



    //
    // Load textures
    //
    heroTexture = this->tex->Load("sprites/player/char_maincharacter_w.png");


    position = iPoint(12 * 16, 27 * 16);

    width = 32;
    height = 32;

    playerCollision[0] = { 0, 0 };
    playerCollision[1] = { width, 0 };
    playerCollision[2] = { 0, height };
    playerCollision[3] = {  width, height };

    //Hero stats
    infoEntities.info.name = "Hero";
    infoEntities.info.HP = 45;
    infoEntities.info.SP = 10;
    infoEntities.info.maxHP = 45;
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
    infoEntities.skills[1].name = "S. Boomerang";
    infoEntities.skills[1].cost = 4;
    infoEntities.skills[1].picked = false;
    infoEntities.skills[2].name = "L. Recovery";
    infoEntities.skills[2].cost = 3;
    infoEntities.skills[2].picked = false;
    infoEntities.skills[3].name = "Steal";
    infoEntities.skills[3].cost = 8;
    infoEntities.skills[3].picked = false;
    infoEntities.skills[4].name = "Triple Spatula";
    infoEntities.skills[4].cost = 10;
    infoEntities.skills[4].picked = false;

    // Define Player current animation
    currentAnimation = animHeroIdleDown;

    //Define Hurt Texture
    hurtTexture = this->tex->Load("sprites/combat/cmb_hurt.png");

    //Define Shield Texture
    shieldTexture = this->tex->Load("sprites/combat/cmb_shield.png");

    //Define Death Texture
    deathTexture = this->tex->Load("sprites/combat/cmb_death.png");
}
// Destructor
Player::~Player()
{}


// Update called each iteration
bool Player::Update(float dt)
{
    UpdateState();
    UpdateLogic(dt);
 
    return true;
}
// Control the when a state changes
void Player::UpdateState()
{
    GamePad& pad = input->pads[0];

    switch (state)
    {
    case IDLE:
    {
        if (((input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && input->joystickState() == false) ||
            (pad.l_y < -0.5f && input->joystickState() == true))
        {
            ChangeState(state, MOVE_UP);
            break;
        }
        if ((input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && input->joystickState() == false) ||
            (pad.l_y > 0.5f && input->joystickState() == true))
        {
            ChangeState(state, MOVE_DOWN);
            break;
        }
        if ((input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && input->joystickState() == false) ||
            (pad.l_x < -0.5f && input->joystickState() == true))
        {
            ChangeState(state, MOVE_LEFT);
            break;
        }
        if ((input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && input->joystickState() == false) ||
            (pad.l_x > 0.5f && input->joystickState() == true))
        {
            ChangeState(state, MOVE_RIGHT);
            break;
        }
        if (input->GetKey(SDL_SCANCODE_X) == KEY_UP ||
            pad.GetPadKey(SDL_CONTROLLER_BUTTON_A) == KEY_UP)
        {
            interacting = true;
        }
        else
        {
            interacting = false;
        }


        if (noClip)
        {
            ChangeState(state, GOD_MODE);
            break;
        }
        else if (inBattle)
        {
            ChangeState(state, BATTLE);
            break;
        }
        else if (transitioning || inConversation)
        {
            ChangeState(state, FROZEN);
            break;
        }

        break;
    }
    case MOVE_UP:
    {
        if (!movingFlag)
        {
            if (((input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && input->joystickState() == false) ||
                ((pad.l_y < -0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f || pad.l_x == 0.0f) && input->joystickState() == true))
                ChangeState(state, MOVE_UP);
            if ((input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_y > 0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_DOWN);
            if ((input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x < -0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_LEFT);
            if ((input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x > 0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_RIGHT);

            if (!movingFlag)
                ChangeState(state, IDLE);
        }

        if (noClip)
        {
            ChangeState(state, GOD_MODE);
            break;
        }
        if (transitioning || inConversation)
        {
            ChangeState(state, FROZEN);
            break;
        }
        if (inBattle)
        {
            ChangeState(state, BATTLE);
            break;
        }

        break;
    }
    case MOVE_DOWN:
    {
        if (!movingFlag)
        {
            if (((input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && input->joystickState() == false) ||
                ((pad.l_y < -0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f || pad.l_x == 0.0f) && input->joystickState() == true))
                ChangeState(state, MOVE_UP);
            if ((input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_y > 0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_DOWN);
            if ((input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x < -0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_LEFT);
            if ((input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x > 0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_RIGHT);

            if (!movingFlag)
                ChangeState(state, IDLE);
        }

        if (noClip)
        {
            ChangeState(state, GOD_MODE);
            break;
        }
        if (transitioning || inConversation)
        {
            ChangeState(state, FROZEN);
            break;
        }
        if (inBattle)
        {
            ChangeState(state, BATTLE);
            break;
        }

        break;
    }
    case MOVE_LEFT:
    {
        if (!movingFlag)
        {
            if (((input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && input->joystickState() == false) ||
                ((pad.l_y < -0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f || pad.l_x == 0.0f) && input->joystickState() == true))
                ChangeState(state, MOVE_UP);
            if ((input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_y > 0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_DOWN);
            if ((input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x < -0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_LEFT);
            if ((input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x > 0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_RIGHT);

            if (!movingFlag)
                ChangeState(state, IDLE);
        }

        if (noClip)
        {
            ChangeState(state, GOD_MODE);
            break;
        }
        if (transitioning || inConversation)
        {
            ChangeState(state, FROZEN);
            break;
        }
        if (inBattle)
        {
            ChangeState(state, BATTLE);
            break;
        }

        break;
    }
    case MOVE_RIGHT:
    {
        if (!movingFlag)
        {
            if (((input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && input->joystickState() == false) ||
                ((pad.l_y < -0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f ||pad.l_x == 0.0f) && input->joystickState() == true))
                ChangeState(state, MOVE_UP);
            if ((input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_y > 0.25f && pad.l_x > -0.25f && pad.l_x < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_DOWN);
            if ((input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x < -0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_LEFT);
            if ((input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN ||
                input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && input->joystickState() == false) ||
                (pad.l_x > 0.25f && pad.l_y > -0.25f && pad.l_y < 0.25f && input->joystickState() == true))
                ChangeState(state, MOVE_RIGHT);

            if (!movingFlag)
                ChangeState(state, IDLE);
        }

        if (noClip)
        {
            ChangeState(state, GOD_MODE);
            break;
        }
        if (transitioning || inConversation)
        {
            ChangeState(state, FROZEN);
            break;
        }
        if (inBattle)
        {
            ChangeState(state, BATTLE);
            break;
        }

        break;
    }
    case GOD_MODE:
    {
        if (!noClip)
        {
            ChangeState(state, IDLE);
            break;
        }

        break;
    }
    case FROZEN:
    {
        if (!transitioning && !inConversation)
        {
            ChangeState(state, IDLE);
            break;
        }

        break;
    }
    case BATTLE:
    {
        if (!inBattle)
        {
            ChangeState(state, IDLE);
            break;
        }

        break;
    }
    default:
        break;
    }
}
// Update the logic of the Hero
void Player::UpdateLogic(float dt)
{
    GamePad& pad = input->pads[0];

    temPos = position;

    collision->player = this;


    switch (state)
    {
    case IDLE:
    {
        currentAnimation->Update();

        break;
    }
    case MOVE_UP:
    {
        if (movingFlag)
        {
            if (position.y >= (tilePos.y - TILE_SIZE))
            {
                position.y -= (PLAYER_MOVE_SPEED * dt);
            }
            else
            {
                position.y = (tilePos.y - TILE_SIZE);
                movingFlag = false;
            }
        }

        currentAnimation->Update();

        break;
    }
    case MOVE_DOWN:
    {
        if (movingFlag)
        {
            if (position.y <= (tilePos.y + TILE_SIZE))
            {
                position.y += (PLAYER_MOVE_SPEED * dt + 1);
            }
            else
            {
                position.y = (tilePos.y + TILE_SIZE);
                movingFlag = false;
            }
        }

        currentAnimation->Update();

        break;
    }
    case MOVE_LEFT:
    {
        if (movingFlag)
        {
            if (position.x >= (tilePos.x - TILE_SIZE))
            {
                position.x -= (PLAYER_MOVE_SPEED * dt);
            }
            else
            {
                position.x = (tilePos.x - TILE_SIZE);
                movingFlag = false;
            }
        }

        currentAnimation->Update();

        break;
    }
    case MOVE_RIGHT:
    {
        if (movingFlag)
        {
            if (position.x <= (tilePos.x + TILE_SIZE))
            {
                position.x += (PLAYER_MOVE_SPEED * dt + 1);
            }
            else
            {
                position.x = (tilePos.x + TILE_SIZE);
                movingFlag = false;
            }
        }

        currentAnimation->Update();

        break;
    }
    case GOD_MODE:
    {
        collision->player = nullptr;

        if ((input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && input->joystickState() == false) ||
            (pad.l_y < 0.0f && input->joystickState() == true))
            position.y -= (PLAYER_MOVE_SPEED * dt);
        if ((input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && input->joystickState() == false) ||
            (pad.l_y > 0.0f && input->joystickState() == true))
            position.y += (PLAYER_MOVE_SPEED * dt + 1);
        if ((input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && input->joystickState() == false) ||
            (pad.l_x < 0.0f && input->joystickState() == true))
            position.x -= (PLAYER_MOVE_SPEED * dt);
        if ((input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN ||
            input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && input->joystickState() == false) ||
            (pad.l_x > 0.0f && input->joystickState() == true))
            position.x += (PLAYER_MOVE_SPEED * dt + 1);

        currentAnimation->Update();

        break;
    }
    case FROZEN:
    {
        // Do nothing
        break;
    }
    case BATTLE:
    {
        currentAnimation->Update();
        if (infoEntities.info.HP <= 0) deathAnim->Update();
        break;
    }
    default:
        break;
    }
}
// Controls what happens when you change to a state
void Player::ChangeState(HeroState previousState, HeroState newState)
{
    switch (newState)
    {
    case IDLE:
    {
        switch (facingDirection)
        {
        case UP:
        {
            currentAnimation = animHeroIdleUp;
            break;
        }
        case DOWN:
        {
            currentAnimation = animHeroIdleDown;
            break;
        }
        case LEFT:
        {
            currentAnimation = animHeroIdleLeft;
            break;
        }
        case RIGHT:
        {
            currentAnimation = animHeroIdleRight;
            break;
        }
        default:
            break;
        }
        break;
    }
    case MOVE_UP:
    {
        currentAnimation = animHeroWalkUp;
        movingFlag = true;
        tilePos = position;
        facingDirection = UP;

        break;
    }
    case MOVE_DOWN:
    {
        currentAnimation = animHeroWalkDown;
        movingFlag = true;
        tilePos = position;
        facingDirection = DOWN;

        break;
    }
    case MOVE_LEFT:
    {
        currentAnimation = animHeroWalkLeft;
        movingFlag = true;
        tilePos = position;
        facingDirection = LEFT;

        break;
    }
    case MOVE_RIGHT:
    {
        currentAnimation = animHeroWalkRight;
        movingFlag = true;
        tilePos = position;
        facingDirection = RIGHT;

        break;
    }
    case GOD_MODE:
    {
        currentAnimation = animHeroIdleDown;
        break;
    }
    case FROZEN:
    {

        break;
    }
    case BATTLE:
    {
        currentAnimation = animHeroIdleRight;
        break;
    }
    default:
        break;
    }

    state = newState;
}


bool Player::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    //SDL_Rect rec = { 0 };
    //render->DrawTexture(texture, position.x, position.y, rec);

    if (noClip)
    {
        render->DrawRectangle(GetBounds(), 0, 255, 0, 255);
    }
    if (infoEntities.info.HP > 0)
    {
        SDL_Rect rect = currentAnimation->GetCurrentFrame();
        render->DrawTexture(heroTexture, (int)position.x - 16, (int)position.y - 64, &rect);
    }
    else if (infoEntities.info.HP <= 0)
    {
        SDL_Rect rect_death = deathAnim->GetCurrentFrame();
        render->DrawTexture(deathTexture, (int)position.x - 40, (int)position.y - 64, &rect_death);
    }

    SDL_Rect rect_hurt = hurtAnim->GetCurrentFrame();
    render->DrawTexture(hurtTexture, (int)position.x - 16, (int)position.y - 64, &rect_hurt);

    if (infoEntities.defense)
    {
        SDL_Rect rect_def = { 0, 0, 64, 96 };
        render->DrawTexture(shieldTexture, (int)position.x + 40, (int)position.y - 64, &rect_def);
    }

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