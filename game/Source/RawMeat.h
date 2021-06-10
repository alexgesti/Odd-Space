#ifndef __RAWMEAT_H__
#define __RAWMEAT_H__

#include "Item.h"


class Render;
class Textures;


class RawMeat : public Item
{
public:

    // Get unique instance of the class
    static RawMeat* GetInstance(Render* render, Textures* tex);
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
    static RawMeat* instance;
    // Private Constructor
    RawMeat(Render* render, Textures* tex);
    // Private Destructor
    virtual ~RawMeat();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    RawMeat(const RawMeat&);
    RawMeat& operator=(const RawMeat&);
    // ----------------------------- //

private:

    Render* render;
};

#endif // __STANDARDPIRATES_H__
