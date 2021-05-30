#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"
#include "Font.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(uint32 id, SDL_Rect bounds, const char *text, Audio* audio, bool sorted = true);
    virtual ~GuiButton();

    bool Update(Input* input, int buttonSelected, float dt);
    bool Draw(Render* render, Font* font);
    bool UnLoad();

public:

    // Gui Button specific properties
    // Maybe some animation properties for state change?
    int hover = 0;
    int press = 0;
    int unavaliable = 0;
    float timer = 0.0f;
    Uint8 red = 255;
    Uint8 green = 255;
    Uint8 blue = 255;
    bool increase = false;
    bool decrease = false;
    Uint8 flips = 0;
private:
    bool soundReproduced = true;
    bool sorted;
};

#endif // __GUIBUTTON_H__
