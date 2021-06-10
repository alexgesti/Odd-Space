#ifndef __PINT_H__
#define __PINT_H__

#include "Item.h"


class Render;
class Textures;


class Pint : public Item
{
public:

    // Get unique instance of the class
    static Pint* GetInstance(Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    void ItemFunction(int* HP, int* SP, int maxHP, int maxSP);

    bool Draw();

    bool UnLoad();

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture = nullptr;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static Pint* instance;
    // Private Constructor
    Pint(Render* render, Textures* tex);
    // Private Destructor
    virtual ~Pint();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    Pint(const Pint&);
    Pint& operator=(const Pint&);
    // ----------------------------- //

private:

    Render* render;
};

#endif // __PINT_H__
