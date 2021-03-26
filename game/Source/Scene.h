#ifndef __SCENE_H__
#define __SCENE_H__

#include "SString.h"

class Input;
class Render;
class Textures;

class GuiControl;

enum class SceneType
{
    LOGO,
    TITLE,
    CANTINA
};

class Scene
{
public:

    Scene() : active(true), loaded(false), transitionRequired(false) {}

    virtual bool Load(Textures* tex)
    {
        return true;
    }

    virtual bool Update(Input* input, float dt)
    {
        return true;
    }

    virtual bool Draw(Render* render)
    {
        return true;
    }

    virtual bool Unload()
    {
        return true;
    }

    void TransitionToScene(SceneType scene)
    {
        transitionRequired = true;
        nextScene = scene;
    }

    // Define multiple Gui Event methods
    virtual bool OnGuiMouseClickEvent(GuiControl* control)
    {
        return true;
    }

public:

    bool active = true;
    SString name;         // Scene name identifier?

    // Possible properties
    bool loaded = false;
    // TODO: Transition animation properties

    bool transitionRequired;
    SceneType nextScene;

    bool fullscreenChange = false;
};

#endif // __SCENE_H__