#include "rendering.h"
#include "constant.h"
#include <cmath>


//SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
//	SDL_Texture* texture = IMG_LoadTexture(renderer, path);
//	if (!texture) {
//		SDL_Log("Failed to load texture: %s", IMG_GetError());
//	}
//	return texture;
//}

//void renderScene(SDL_Renderer* renderer, const Ball& ball, SDL_Texture* ballTexture) {

//	SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
//	SDL_RenderClear(renderer);
	
	// Draw circle representing ball (temporary later will be image as asset)
//	if (ballTexture) {
//		SDL_Rect destRect = { static_cast<int>(ball.x - BALL_RADIUS), static_cast<int>(ball.y - BALL_RADIUS), BALL_RADIUS * 2, BALL_RADIUS * 2 };
//		SDL_RenderCopy(renderer, ballTexture, NULL, &destRect);
//	}

	// Direction line indicator (might change to asset)
//	if (ball.isMouseDragging) {
//		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//		float dirX = static_cast<float>(ball.dragStartX - ball.currentDragX);
//		float dirY = static_cast<float>(ball.dragStartY - ball.currentDragY);
//		float distance = std::sqrt(dirX * dirX + dirY * dirY);
//
//		if (distance > 0) {
//			float scale = LINE_LENGTH / distance;
//			int endX = static_cast<int>(ball.x + dirX * scale);
//			int endY = static_cast<int>(ball.y + dirY * scale);
//			SDL_RenderDrawLine(renderer, static_cast<int>(ball.x), static_cast<int>(ball.y), endX, endY);
//		}
//	}

//	SDL_RenderPresent(renderer);
//}


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