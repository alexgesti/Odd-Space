#ifndef __STRONGRON_H__
#define __STRONGRON_H__

#include "Item.h"


class Render;
class Textures;


class StrongRon : public Item
{
public:

    // Get unique instance of the class
    static StrongRon* GetInstance(Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    void ItemFunction(int* HP, int* SP, int maxHP, int maxSP);

    bool Draw();

    bool UnLoad();

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

    void CheckQuantity();

public:

    SDL_Texture* texture = nullptr;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static StrongRon* instance;
    // Private Constructor
    StrongRon(Render* render, Textures* tex);
    // Private Destructor
    virtual ~StrongRon();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    StrongRon(const StrongRon&);
    StrongRon& operator=(const StrongRon&);
    // ----------------------------- //

private:

    Render* render;
};

#endif // __STRONGRON_H__
