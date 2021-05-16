#ifndef __FONT_H__
#define __FONT_H__

#include "Defs.h"

#include "SDL/include/SDL.h"

class Textures;
class Assets;

class Font
{
public:

    Font(const char* rtpFontFile, Textures* tex);

    ~Font();

    SDL_Texture* GetTextureAtlas();
    SDL_Rect GetCharRec(int value);

private:

    bool fontLoaded;

    SDL_Texture* texture;

    int baseSize;
    int charsCount;
    SDL_Rect charsRecs[128];


    Assets* assets;
};

#endif //__FONT_H__