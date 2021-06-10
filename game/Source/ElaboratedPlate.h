#ifndef __ELABORATEDPLATE_H__
#define __ELABORATEDPLATE_H__

#include "Item.h"


class Render;
class Textures;


class ElaboratedPlate : public Item
{
public:

    // Get unique instance of the class
    static ElaboratedPlate* GetInstance(Render* render, Textures* tex);
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
    static ElaboratedPlate* instance;
    // Private Constructor
    ElaboratedPlate(Render* render, Textures* tex);
    // Private Destructor
    virtual ~ElaboratedPlate();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    ElaboratedPlate(const ElaboratedPlate&);
    ElaboratedPlate& operator=(const ElaboratedPlate&);
    // ----------------------------- //

private:

    Render* render;
};

#endif // __STANDARDPIRATES_H__
