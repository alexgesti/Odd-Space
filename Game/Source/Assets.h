#ifndef _ASSETS_H_
#define _ASSETS_H_

#include "Module.h"
#include "External/SDL/include/SDL.h"

class Assets{
public:

	static Assets* GetInstance();
	static void ResetInstance();

	bool Init();
	SDL_RWops* Load(const char* fileName);
	int MakeLoad(const char* fileName);
	bool DeleteBuffer();
	char* GetLastBuffer();
	char* buffer = nullptr;

private:
	static Assets* instance;
	Assets();
	virtual ~Assets();
	Assets(const Assets&);
	Assets& operator=(const Assets&);
};

#endif // !_ASSETS_H_