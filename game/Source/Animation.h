#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"

#define MAX_FRAMES 240
#define MAX_STEPS 20


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

enum class Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Step
{
public:
	Step() {};

	Step(int xo, int xf, int yo, int yf, int w, int h)
	{
		this->xo = xo;
		this->xf = xf;
		this->yo = yo;
		this->yf = yf;
		this->w = w;
		this->h = h;
		this->currentXf = xo;
		this->currentYf = yo;
		if (xf - xo < 0) this->direction = Direction::LEFT;
		else if (xf - xo > 0) this->direction = Direction::RIGHT;
		else if (yf - yo > 0) this->direction = Direction::DOWN;
		else if (yf - yo < 0) this->direction = Direction::UP;
	}

	int xo;
	int xf;
	int yo;
	int yf;
	int w = 20;
	int h = 20;
	int currentXf;
	int currentYf;
	bool completed = false;
	Direction direction;
	int alpha = 255;
	bool disapear = true;

	void Reset()
	{
		xo = xf = yo = yf = currentXf = currentYf = 0;
		completed = false;
		w = h = 20;
		alpha = 255;
		disapear = true;
	}
};

class StepedAnimation
{
public:
	void Pushback(int xo, int xf, int yo, int yf, int w, int h)
	{
		Step temp = { xo, xf, yo, yf, w, h };
		steps[stepAmount] = temp;
		stepAmount++;
	}

	SDL_Rect Update()
	{
		SDL_Rect temp;

		switch (steps[currentStep].direction)
		{
		case Direction::LEFT:
			if (steps[currentStep].currentXf >= steps[currentStep].xf) steps[currentStep].currentXf -= speed;
			if (steps[currentStep].currentXf < steps[currentStep].xf) steps[currentStep].currentXf = steps[currentStep].xf;
			temp.w = steps[currentStep].currentXf - steps[currentStep].xo;
			temp.h = steps[currentStep].h;
			break;
		case Direction::RIGHT:
			if (steps[currentStep].currentXf <= steps[currentStep].xf) steps[currentStep].currentXf += speed;
			if (steps[currentStep].currentXf > steps[currentStep].xf) steps[currentStep].currentXf = steps[currentStep].xf;
			temp.w = steps[currentStep].currentXf - steps[currentStep].xo;
			temp.h = steps[currentStep].h;
			break;
		case Direction::UP:
			if (steps[currentStep].currentYf >= steps[currentStep].yf)steps[currentStep].currentYf -= speed;
			if (steps[currentStep].currentYf < steps[currentStep].yf) steps[currentStep].currentYf = steps[currentStep].yf;
			temp.h = steps[currentStep].currentYf - steps[currentStep].yo;
			temp.w = steps[currentStep].w;
			break;
		case Direction::DOWN:
			if (steps[currentStep].currentYf <= steps[currentStep].yf)steps[currentStep].currentYf += speed;
			if (steps[currentStep].currentYf > steps[currentStep].yf) steps[currentStep].currentYf = steps[currentStep].yf;
			temp.h = steps[currentStep].currentYf - steps[currentStep].yo;
			temp.w = steps[currentStep].w;
			break;
		default:
			break;
		}

		temp.x = steps[currentStep].xo;
		temp.y = steps[currentStep].yo;

		if (stepCompleted())
		{
			steps[currentStep].completed = true;
			steps[currentStep].currentXf = steps[currentStep].xf;
			steps[currentStep].currentYf = steps[currentStep].yf;

			switch (steps[currentStep].direction)
			{
			case Direction::LEFT:
				steps[currentStep].w = steps[currentStep].xf - steps[currentStep].xo;
				break;
			case Direction::RIGHT:
				steps[currentStep].w = steps[currentStep].xf - steps[currentStep].xo;
				break;
			case Direction::UP:
				steps[currentStep].h = steps[currentStep].yf - steps[currentStep].yo;
				break;
			case Direction::DOWN:
				steps[currentStep].h = steps[currentStep].yf - steps[currentStep].yo;
				break;
			default:
				break;
			}

			if (currentStep >= stepAmount) animationCompleted = true;
			else currentStep++;
		}

		return temp;
	}

	bool stepCompleted()
	{
		switch (steps[currentStep].direction)
		{
		case Direction::LEFT:
			return (steps[currentStep].currentXf <= steps[currentStep].xf);
			break;
		case Direction::RIGHT:
			return (steps[currentStep].currentXf >= steps[currentStep].xf);
			break;
		case Direction::UP:
			return (steps[currentStep].currentYf <= steps[currentStep].yf);
			break;
		case Direction::DOWN:
			return (steps[currentStep].currentYf >= steps[currentStep].yf);
			break;
		default:
			break;
		}
	}

	SDL_Rect GetStep(int step)
	{
		SDL_Rect temp;
		temp.x = steps[step].xo;
		temp.y = steps[step].yo;
		temp.w = steps[step].w;
		temp.h = steps[step].h;
		return temp;
	}

	void Reset()
	{
		for (int i = 0; i < stepAmount; i++)
		{
			steps[stepAmount].Reset();
		}
		currentStep = 0;
		stepAmount = 0;
		animationCompleted = false;
	}

	float speed;
	int stepAmount = 0;
	int currentStep = 0;
	bool animationCompleted = false;

	Step steps[MAX_STEPS];
};

#endif