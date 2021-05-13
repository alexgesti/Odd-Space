#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"
#include "Font.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(uint32 id, SDL_Rect bounds, const char *text, Audio* audio);
    virtual ~GuiButton();

    bool Update(Input* input, int buttonSelected, float dt);
    bool Draw(Render* render, Font* font);

private:

    // Gui Button specific properties
    // Maybe some animation properties for state change?
    int hover = 0;
    int press = 0;
    int unavaliable = 0;
    bool soundReproduced = true;
};

#endif // __GUIBUTTON_H__
