#ifndef __MUTANTRAT_H__
#define __MUTANTRAT_H__

#include "Enemy.h"


class Input;
class Render;
class Textures;


class MutantRat : public Enemy
{
public:

    // Get unique instance of the class
    static MutantRat* GetInstance(Input* input, Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();

    bool UnLoad();

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    Animation* mutantRatAnim = new Animation();
    SDL_Texture* mutantRatTexture;
    int width, height;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static MutantRat* instance;
    // Private Constructor
    MutantRat(Input* input, Render* render, Textures* tex);
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
    Textures* tex;
};

#endif // __MUTANTRAT_H__
