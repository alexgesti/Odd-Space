#ifndef __OLDCAPTAIN_H__
#define __OLDCAPTAIN_H__

#include "Entity.h"


class Render;
class Textures;


class Captain : public Entity
{
public:

    // Get unique instance of the class
    static Captain* GetInstance(Render* render, Textures* tex);
    // Delete the instance
    static void ResetInstance();


    bool Update(float dt);

    bool Draw();

    void AddXP(int xp);

    SDL_Rect GetBounds();

private:

    // ----- OLD CAPTAIN VARIABLES ----- //
    //  Old Captain size
    int width, height;
    // Old Captain sprite sheets
    SDL_Texture* oldCaptainTexture;
    // Current Old Captain animation
    Animation* currentAnimation;
    // --------------------------------- //


    // ----- SINGLETON METHODS ----- //
    // Singleton instance
    static Captain* instance;
    // Private Constructor
    Captain(Render* render, Textures* tex);
    // Private Destructor
    virtual ~Captain();
    // Declare the copy constructor and the assignment operator
    // as private (or delete them explicitly) to prevent cloning your object
    Captain(const Captain&);
    Captain& operator=(const Captain&);
    // ----------------------------- //


    // ----- ANIMATION SETS ----- //
    Animation* animOldCaptainWalkUp = new Animation();
    Animation* animOldCaptainWalkDown = new Animation();
    Animation* animOldCaptainWalkLeft = new Animation();
    Animation* animOldCaptainWalkRight = new Animation();
    // -------------------------- //

private:

    Render* render;
    Textures* tex;
};

#endif // __OLDCAPTAIN_H__
