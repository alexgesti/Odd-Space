#ifndef __GIANTBAT_H__
#define __GIANTBAT_H__

#include "Enemy.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"


class Input;
class Render;
class Textures;

enum class GiantBatAnim
{
    IDLE
};

class GiantBat : public Enemy
{
public:

    // Get unique instance of the class
    static GiantBat* GetInstance(Input* input, Render* render);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();



    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture;   // StandartPirates spritesheet

    GiantBatAnim currentAnim;

    int width, height;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static GiantBat* instance;
    // Private Constructor
    GiantBat(Input* input, Render* render);
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
};

#endif // __GIANTBAT_H__
