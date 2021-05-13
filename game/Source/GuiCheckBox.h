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

    bool Update(Input* input, int buttonSelected, float dt);
    bool Draw(Render* render);

private:

    // GuiCheckBox specific properties
    // Maybe some animation properties for state change?
    int selected = 0;
    bool soundReproduced = true;
    bool checked;
};

#endif // __GUICHECKBOX_H__
