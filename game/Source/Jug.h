#ifndef __JUG_H__
#define __JUG_H__

#include "Item.h"


class Render;
class Textures;


class Jug : public Item
{
public:

    // Get unique instance of the class
    static Jug* GetInstance(Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    void ItemFunction(int* HP, int* SP, int maxHP, int maxSP);

    bool Draw();

    bool UnLoad();

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static Jug* instance;
    // Private Constructor
    Jug(Render* render, Textures* tex);
    // Private Destructor
    virtual ~Jug();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    Jug(const Jug&);
    Jug& operator=(const Jug&);
    // ----------------------------- //

private:

    Render* render;
};

#endif // __JUG_H__
