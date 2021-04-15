#ifndef __OLDCAPTAIN_H__
#define __OLDCAPTAIN_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"

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
    static Captain* GetInstance(Input* input, Render* render);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();



    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture;   // Player spritesheet

    // TODO: Define all animation properties
    CaptainAnim currentAnim;

    int width, height;

    iPoint temPos;

    iPoint playerCollision[4];

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static Captain* instance;
    // Private Constructor
    Captain(Input* input, Render* render);
    // Private Destructor
    virtual ~Captain();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    Captain(const Captain&);
    Captain& operator=(const Captain&);
    // ----------------------------- //

private:

    Input* input;
    Render* render;

    Collision* collision;
};

#endif // __PLAYER_H__
