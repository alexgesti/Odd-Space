#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"

#define MAX_FRAMES 240


//Animation Class
class Animation
{
public:
	bool loop = true;
	bool finish = false;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

	// Allows the animation to keep going back and forth
	bool pingPong = false;

private:
	float currentFrame = 0.0f;
	int totalFrames = 0;
	int loopCount = 0;
	int pingPongDirection = 1;

public:

	//Add frame to animation
	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	//Restart animation
	void Reset()
	{
		currentFrame = 0;
		loopCount = 0;
		finish = false;
	}

	//Controls whether a loop has finished or not
	bool HasFinished()
	{
		return !loop && !pingPong && loopCount > 0;
	}

	//Update the animation to change sprite
	void Update()
	{
		currentFrame += speed;
		if (currentFrame >= totalFrames)
		{
			currentFrame = (loop || pingPong) ? 0.0f : totalFrames - 1;
			++loopCount;

			if (pingPong)
				pingPongDirection = -pingPongDirection;
		}
	}

	//Returns the square of the current frame
	SDL_Rect& GetCurrentFrame()
	{
		int actualFrame = (int)currentFrame;
		if (pingPongDirection == -1)
			actualFrame = totalFrames - (int)currentFrame;

		if (frames[actualFrame].x == 0 &&
			frames[actualFrame].y == 0 &&
			frames[actualFrame].w == 0 &&
			frames[actualFrame].h == 0)
		{
			return frames[actualFrame - 1];
		}
		else
		{
			return frames[actualFrame];
		}
	}

	int GetCurrentFrameID()
	{
		return (int)currentFrame;
	}

	void SetCurrentFrame(int id)
	{
		currentFrame = (float)id;
	}
};

#endif