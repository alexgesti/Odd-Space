#ifndef __SCENELOGO_H__
#define __SCENELOGO_H__

#include "Scene.h"

#include "SDL/include/SDL.h"

class Input;
class Render;
class Textures;

class Logo : public Scene
{
public:

    // Constructor
    Logo(Input* input, Render* render, Textures* tex);
    // Destructor
    virtual ~Logo();


    // Load this scene
    bool Load();

    // Update this scene
    bool Update(float dt);

    // Draw this scene
    bool Draw();

    // Unload this scene
    bool Unload();

private:

    SDL_Texture* logo = nullptr;

    int state;
    float timeCounter;
    float logoAlpha;

private:

    Input* input;
    Render* render;
    Textures* tex;
};

#endif // __SCENELOGO_H__