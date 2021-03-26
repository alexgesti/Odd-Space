#include "Timer.h"
#include "SDL\include\SDL_timer.h"

// L07: DONE 1: Fill Start(), Read(), ReadSec() methods
// they are simple, one line each!

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	startTime = SDL_GetTicks();
}

uint32 Timer::Read() const
{
	return (SDL_GetTicks() - startTime);
}

float Timer::ReadSec() const
{
	return float(SDL_GetTicks() - startTime) / 1000.0f;
}