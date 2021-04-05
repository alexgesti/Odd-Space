#ifndef __DRUNKCUSTOMER_H__
#define __DRUNKCUSTOMER_H__

#include "Enemy.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"


class Input;
class Render;
class Textures;

enum class DrunkCustomerAnim
{
    IDLE
};

class DrunkCustomer : public Enemy
{
public:

    // Get unique instance of the class
    static DrunkCustomer* GetInstance(Input* input, Render* render);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();



    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture;   // StandartPirates spritesheet

    DrunkCustomerAnim currentAnim;

    int width, height;

private:

    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static DrunkCustomer* instance;
    // Private Constructor
    DrunkCustomer(Input* input, Render* render);
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

    Entities drunkCustomer;
};

#endif // __DRUNKCUSTOMER_H__
