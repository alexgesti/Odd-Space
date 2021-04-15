#ifndef __MUTANTRAT_H__
#define __MUTANTRAT_H__

#include "Enemy.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"


class Input;
class Render;
class Textures;

enum class MutantRatAnim
{
    IDLE
};

class MutantRat : public Enemy
{
public:

    // Get unique instance of the class
    static MutantRat* GetInstance(Input* input, Render* render);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();



    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture;   // StandartPirates spritesheet

    MutantRatAnim currentAnim;

    int width, height;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static MutantRat* instance;
    // Private Constructor
    MutantRat(Input* input, Render* render);
    // Private Destructor
    virtual ~MutantRat();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    MutantRat(const MutantRat&);
    MutantRat& operator=(const MutantRat&);
    // ----------------------------- //

private:

    Input* input;
    Render* render;
};

#endif // __MUTANTRAT_H__
