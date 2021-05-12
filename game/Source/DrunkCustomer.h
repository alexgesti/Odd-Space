#ifndef __DRUNKCUSTOMER_H__
#define __DRUNKCUSTOMER_H__

#include "Enemy.h"


class Input;
class Render;
class Textures;

class DrunkCustomer : public Enemy
{
public:

    // Get unique instance of the class
    static DrunkCustomer* GetInstance(Input* input, Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();

    bool UnLoad();

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    Animation* drunkCustomerAnim = new Animation();
    SDL_Texture* drunkCustomerTexture;
    int width, height;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static DrunkCustomer* instance;
    // Private Constructor
    DrunkCustomer(Input* input, Render* render, Textures* tex);
    // Private Destructor
    virtual ~DrunkCustomer();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    DrunkCustomer(const DrunkCustomer&);
    DrunkCustomer& operator=(const DrunkCustomer&);
    // ----------------------------- //

private:

    Input* input;
    Render* render;
    Textures* tex;
};

#endif // __DRUNKCUSTOMER_H__
