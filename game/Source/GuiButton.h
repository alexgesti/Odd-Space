#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(uint32 id, SDL_Rect bounds, const char *text);
    virtual ~GuiButton();

    bool Update(Input* input, float dt);
    bool Draw(Render* render);

private:

    // Gui Button specific properties
    // Maybe some animation properties for state change?
};

#endif // __GUIBUTTON_H__
