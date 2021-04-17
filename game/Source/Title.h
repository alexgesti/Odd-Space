#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SDL/include/SDL.h"

#define MAX_ZOOM 3.0f
#define MIN_ZOOM 0.3f



class Window;
class Input;
class Render;
class Textures;

class Title : public Scene
{
public:

    // Constructor
    Title(Window* win, Input* input, Render* render, Textures* tex);
    // Destructor
    virtual ~Title();


    // Load this scene
    bool Load();

    // Update this scene
    bool Update(float dt);

    // Draw this scene
    bool Draw();

    // Unload this scene
    bool Unload();



    // Declare on mouse click event
    //bool OnGuiMouseClickEvent(GuiControl* control);

private:
    
    SDL_Texture* bgTitle;

    Window* win;
    Input* input;
    Render* render;
    Textures* tex;

};

#endif // __SCENETITLE_H__