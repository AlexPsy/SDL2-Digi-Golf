#pragma once
#include "SDL.h"
#include "ball.h"
#include "direction_indicator.h"
#include "rendering.h"

class Game {
public:
	Game();
	~Game();

	bool Init();
	void Run();

private:
	void ProcessEvents();
	void Render();

	SDL_Window* window;
	Renderer* renderer;
	Ball ball;
	DirectionIndicator directionIndicator;
	SDL_Texture* ballTexture;
	bool running;
};