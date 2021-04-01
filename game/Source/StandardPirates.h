#ifndef __STANDARDPIRATES_H__
#define __STANDARDPIRATES_H__

#include "Enemy.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"


class Input;
class Render;
class Textures;

enum class StandardPiratesAnim
{
    IDLE
};

class StandardPirates : public Enemy
{
public:

    // Get unique instance of the class
    static StandardPirates* GetInstance(Input* input, Render* render);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();



    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture;   // StandartPirates spritesheet

    StandardPiratesAnim currentAnim;

    int width, height;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static StandardPirates* instance;
    // Private Constructor
    StandardPirates(Input* input, Render* render);
    // Private Destructor
    virtual ~StandardPirates();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    StandardPirates(const StandardPirates&);
    StandardPirates& operator=(const StandardPirates&);
    // ----------------------------- //

private:

    Input* input;
    Render* render;
};

#endif // __STANDARDPIRATES_H__
