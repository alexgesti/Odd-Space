#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_MOVE_SPEED 150

#include "Entity.h"

#define TILE_SIZE 32


class Input;
class Render;
class Textures;

class Collision;

// States of the Hero
enum HeroState
{
    IDLE = 0,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    GOD_MODE,
    FROZEN,
    BATTLE
};

enum HeroFacingDirection
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class Player: public Entity
{
public:

    // Get unique instance of the class
    static Player* GetInstance(Input* input, Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();

    bool Update(float dt);
    void UpdateState();
    void UpdateLogic(float dt);
    void ChangeState(HeroState previousState, HeroState newState);


    bool Draw();

    SDL_Rect GetBounds();

    static void SetCollision(Collision* collision, Player* player);

public:

    // ----- PLAYER VARIABLES ----- //
    // Player collision
    iPoint playerCollision[4];
    //Flag to know if the Hero is moving a tile
    bool movingFlag = false;
    // ---------------------------- //

private:

    // ----- PLAYER VARIABLES ----- //
    // Player size
    int width, height;
    // Hero's state
    HeroState state = IDLE;
    // Hero's facing direction
    HeroFacingDirection facingDirection = DOWN;
    // Player sprite sheets
    SDL_Texture* heroTexture;
    // Current Player animation
    Animation* currentAnimation;
    // Temporal position for tile movement
    iPoint tilePos = { 0,0 };
    // ---------------------------- //

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static Player* instance;
    // Private Constructor
    Player(Input* input, Render* render, Textures* tex);
    // Private Destructor
    virtual ~Player();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    Player(const Player&);
    Player& operator=(const Player&);
    // ----------------------------- //


    // ----- ANIMATION SETS ----- //
    Animation* animHeroWalkUp = new Animation();
    Animation* animHeroWalkDown = new Animation();
    Animation* animHeroWalkLeft = new Animation();
    Animation* animHeroWalkRight = new Animation();
    Animation* animHeroIdleUp = new Animation();
    Animation* animHeroIdleDown = new Animation();
    Animation* animHeroIdleLeft = new Animation();
    Animation* animHeroIdleRight = new Animation();
    // -------------------------- //

private:

    Input* input;
    Render* render;
    Textures* tex;

    Collision* collision;
};

#endif // __PLAYER_H__
