#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "ball.h"

//SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
//void renderScene(SDL_Renderer* renderer, const Ball& ball, SDL_Texture* ballTexture);

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


