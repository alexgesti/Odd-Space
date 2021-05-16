#ifndef __SCENELOGO_H__
#define __SCENELOGO_H__

#include "Scene.h"
#include "Textures.h"

class SceneManager;
class SDL_Texture;

class Logo : public Scene
{
public:

    // Constructor
    Logo(SceneManager* sceneManager);
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

    SceneManager* sceneManager;

    SDL_Texture* logo = nullptr;

    int state;
    float timeCounter;
    float logoAlpha;  
    float angle;

    int temporalLogoSound = 0;
};

#endif // __SCENELOGO_H__