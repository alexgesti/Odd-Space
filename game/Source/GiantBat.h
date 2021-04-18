#ifndef __GIANTBAT_H__
#define __GIANTBAT_H__

#include "Enemy.h"

#include "Point.h"
#include "SString.h"
#include "Animation.h"

#include "SDL/include/SDL.h"


class Input;
class Render;
class Textures;


class GiantBat : public Enemy
{
public:

    // Get unique instance of the class
    static GiantBat* GetInstance(Input* input, Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();

    bool UnLoad(); 

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    Animation* giantBatAnim = new Animation();
    SDL_Texture* giantBatTexture;
    int width, height;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static GiantBat* instance;
    // Private Constructor
    GiantBat(Input* input, Render* render, Textures* tex);
    // Private Destructor
    virtual ~GiantBat();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    GiantBat(const GiantBat&);
    GiantBat& operator=(const GiantBat&);
    // ----------------------------- //

private:

    Input* input;
    Render* render;
    Textures* tex;
};

#endif // __GIANTBAT_H__
