#ifndef __SCENELOGO_H__
#define __SCENELOGO_H__

#include "Scene.h"

#include "SDL/include/SDL.h"

class Logo : public Scene
{
public:

    Logo();
    virtual ~Logo();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool Unload(Textures* tex);

private:

    SDL_Texture* logo = nullptr;

    int state;
    float timeCounter;
    float logoAlpha;
};

#endif // __SCENELOGO_H__
