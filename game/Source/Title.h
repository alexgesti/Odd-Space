#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "Window.h"

#define MAX_ZOOM 3.0f
#define MIN_ZOOM 0.3f

class Title : public Scene
{
public:

    Title(Window* win);
    virtual ~Title();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool Unload(Textures* tex);

    // Declare on mouse click event
    //bool OnGuiMouseClickEvent(GuiControl* control);

private:
    Window* win;
};

#endif // __SCENETITLE_H__
