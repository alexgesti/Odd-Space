#ifndef __COOKEDPLATE_H__
#define __COOKEDPLATE_H__

#include "Item.h"


class Render;
class Textures;


class CookedPlate : public Item
{
public:

    // Get unique instance of the class
    static CookedPlate* GetInstance(Render* render, Textures* tex);
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
    static CookedPlate* instance;
    // Private Constructor
    CookedPlate(Render* render, Textures* tex);
    // Private Destructor
    virtual ~CookedPlate();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    CookedPlate(const CookedPlate&);
    CookedPlate& operator=(const CookedPlate&);
    // ----------------------------- //

private:

    Render* render;
};

#endif // __COOKEDPLATE_H__
