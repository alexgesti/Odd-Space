#ifndef __OLDCAPTAIN_H__
#define __OLDCAPTAIN_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"
#include "Animation.h"

#include "SDL/include/SDL.h"



class Input;
class Render;
class Textures;

class Collision;

enum class CaptainAnim
{
    IDLE,
    WALK,
    JUMP,
    CLIMB
};

class Captain : public Entity
{
public:

    // Get unique instance of the class
    static Captain* GetInstance(Input* input, Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();



    SDL_Rect GetBounds();

private:

    // ----- OLD CAPTAIN VARIABLES ----- //
    //  Old Captain size
    int width, height;
    // Old Captain sprite sheets
    SDL_Texture* oldCaptainTexture;
    // Current Old Captain animation
    Animation* currentAnimation;
    // --------------------------------- //


    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static Captain* instance;
    // Private Constructor
    Captain(Input* input, Render* render, Textures* tex);
    // Private Destructor
    virtual ~Captain();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    Captain(const Captain&);
    Captain& operator=(const Captain&);
    // ----------------------------- //


    // ----- ANIMATION SETS ----- //
    Animation* animOldCaptainWalkUp = new Animation();
    Animation* animOldCaptainWalkDown = new Animation();
    Animation* animOldCaptainWalkLeft = new Animation();
    Animation* animOldCaptainWalkRight = new Animation();
    // -------------------------- //

private:

    Input* input;
    Render* render;
    Textures* tex;

    Collision* collision;
};

#endif // __PLAYER_H__
