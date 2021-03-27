#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Input.h"
#include "Render.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"

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

    static Player* GetInstance(Input* input);

    static void ResetInstance();

    bool Update(float dt);

    bool Draw(Render* render);

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture;   // Player spritesheet

    // TODO: Define all animation properties
    PlayerAnim currentAnim;

    int width, height;

    float jumpSpeed = 0.0f;
    bool readyToJump = true;
    bool hitObstacle = false;

private:

    Input* input;

    //SINGLETONE

    Player(Input* input);

    virtual ~Player();

    Player(const Player&);

    Player& operator=(const Player&);

    static Player* instance;
};

#endif // __PLAYER_H__
