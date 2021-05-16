#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

    GuiCheckBox(uint32 id, SDL_Rect bounds, const char *text, Audio* audio);
    virtual ~GuiCheckBox();

    bool Update(Input* input, bool* checked, int buttonSelected, float dt);
    bool Draw(Render* render, SDL_Texture* texture);
    bool UnLoad();

private:

    // GuiCheckBox specific properties
    // Maybe some animation properties for state change?
    int hover = 0;
    int press = 0;
    int unavaliable = 0;
    bool soundReproduced = true;
    bool check;
};

#endif // __GUICHECKBOX_H__
