#ifndef __LARGERAWMEAT_H__
#define __LARGERAWMEAT_H__

#include "Item.h"


class Render;
class Textures;


class LargeRawMeat : public Item
{
public:

    // Get unique instance of the class
    static LargeRawMeat* GetInstance(Render* render, Textures* tex);
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
    static LargeRawMeat* instance;
    // Private Constructor
    LargeRawMeat(Render* render, Textures* tex);
    // Private Destructor
    virtual ~LargeRawMeat();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    LargeRawMeat(const LargeRawMeat&);
    LargeRawMeat& operator=(const LargeRawMeat&);
    // ----------------------------- //

private:

    Render* render;
};

#endif // __LARGERAWMEAT_H__
