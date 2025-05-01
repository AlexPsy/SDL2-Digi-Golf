#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "ball.h"


class Renderer {
public:
	Renderer(SDL_Window* window);
	~Renderer();

	SDL_Texture* LoadTexture(const char* path);
	void Clear();
	void Present();
	SDL_Renderer* Get() const { return renderer; }

private:
	SDL_Renderer* renderer;
};


