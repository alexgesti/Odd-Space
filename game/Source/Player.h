#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_MOVE_SPEED 100.0f

#include "Entity.h"

#include "Point.h"
#include "SString.h"
#include "Animation.h"

#include "SDL/include/SDL.h"



class Input;
class Render;
class Textures;

class Collision;


class Player: public Entity
{
public:

    // Get unique instance of the class
    static Player* GetInstance(Input* input, Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();

    bool Update(float dt);

    bool Draw();

    SDL_Rect GetBounds();

    static void SetCollision(Collision* collision, Player* player);

public:

    // ----- PLAYER VARIABLES ----- //
    // Player collision
    iPoint playerCollision[4];
    // ---------------------------- //

private:

    // ----- PLAYER VARIABLES ----- //
    // Player size
    int width, height;
    // Player sprite sheets
    SDL_Texture* heroTexture;
    // Current Player animation
    Animation* currentAnimation;   
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
    // -------------------------- //

private:

    Input* input;
    Render* render;
    Textures* tex;

    Collision* collision;
};

#endif // __PLAYER_H__
