#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

    GuiSlider(uint32 id, SDL_Rect bounds, const char *text, Audio* audio);
    virtual ~GuiSlider();

    bool Update(Input* input, int buttonSelected, float dt);
    bool Draw(Render* render, int slider);

private:

    // GuiSlider specific properties
    // Maybe some animation properties for state change?
    int selected = 0;
    bool soundReproduced = true;
};

#endif // __GUISLIDER_H__
