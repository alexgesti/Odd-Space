#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"

#include "Point.h"
#include "Font.h"

#include "SDL/include/SDL.h"

#define VSYNC true



class Window;

class Render : public Module
{
public:

	// Constructor
	Render(Window* win);
	// Destructor
	virtual ~Render();


	// Called before render is available
	bool Awake(pugi::xml_node&);
	// Called before the first frame
	bool Start();


	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();



	// Viewport
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();

	// Drawing
	bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawDegradedRectHorizontal(const SDL_Rect& rect, SDL_Color color1, SDL_Color color2, bool useCamera = true);
	bool DrawDegradedRectVertical(const SDL_Rect& rect, SDL_Color color1, SDL_Color color2, bool useCamera = true);
	bool DrawParticle(SDL_Texture* texture, int x, int y, const SDL_Rect* section, const SDL_Rect* rectSize, SDL_Color color, SDL_BlendMode blendMode = SDL_BLENDMODE_ADD, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;

	bool DrawText(Font* font, const char* text, int x, int y, int size, int spacing, SDL_Color tint);

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer* renderer;
	SDL_Rect camera;
	SDL_Rect viewport;
	SDL_Color background;

	iPoint prevCam;

	uint scale;

private:

	Window* win;
};

#endif // __RENDER_H__