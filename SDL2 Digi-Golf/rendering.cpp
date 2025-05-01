#include "rendering.h"
#include "constant.h"
#include <cmath>


Renderer::Renderer(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer:: ~Renderer() {
	SDL_DestroyRenderer(renderer);
}

// texture loader
SDL_Texture * Renderer::LoadTexture(const char* path) {
	SDL_Texture* texture = IMG_LoadTexture(renderer, path);
	if (!texture) {
		SDL_Log("Failed to load texture: %s", IMG_GetError());
	}
	return texture;
}

void Renderer::Clear() {
	SDL_RenderClear(renderer);
}

void Renderer::Present() {
	SDL_RenderPresent(renderer);
}