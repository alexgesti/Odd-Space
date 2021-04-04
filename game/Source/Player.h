#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_MOVE_SPEED 100.0f

#include "Entity.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"

class Input;
class Render;
class Textures;

class Collision;

enum class PlayerAnim
{
    IDLE,
    WALK,
    JUMP,
    CLIMB
};

class Player: public Entity
{
public:

    // Get unique instance of the class
    static Player* GetInstance(Input* input, Render* render);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();



    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

    static void SetCollision(Collision* collision, Player* player);

public:

    SDL_Texture* texture;   // Player spritesheet

    // TODO: Define all animation properties
    PlayerAnim currentAnim;

    int width, height;

    float jumpSpeed = 0.0f;
    bool readyToJump = true;
    bool hitObstacle = false;

    iPoint temPos;

    iPoint playerCollision[4];

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static Player* instance;
    // Private Constructor
    Player(Input* input, Render* render);
    // Private Destructor
    virtual ~Player();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    Player(const Player&);
    Player& operator=(const Player&);
    // ----------------------------- //

private:

    Input* input;
    Render* render;

    Collision* collision;
};

#endif // __PLAYER_H__
