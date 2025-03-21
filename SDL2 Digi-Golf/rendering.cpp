#include "rendering.h"
#include "constant.h"
#include <cmath>

void renderScene(SDL_Renderer* renderer, const Ball& ball) {

	SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
	SDL_RenderClear(renderer);
	
	// Draw circle representing ball (temporary later will be image as asset)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int w = -BALL_RADIUS; w < BALL_RADIUS; w++) {
		for (int h = -BALL_RADIUS; h < BALL_RADIUS; h++) {
			if (w * w + h * h <= BALL_RADIUS * BALL_RADIUS) {
				SDL_RenderDrawPoint(renderer, static_cast<int>(ball.x) + w, static_cast<int>(ball.y) + h);
			}
		}
	}

	// Direction line indicator (might change to asset)
	if (ball.isMouseDragging) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		float dirX = static_cast<float>(ball.dragStartX - ball.currentDragX);
		float dirY = static_cast<float>(ball.dragStartY - ball.currentDragY);
		float distance = std::sqrt(dirX * dirX + dirY * dirY);

		if (distance > 0) {
			float scale = LINE_LENGTH / distance;
			int endX = static_cast<int>(ball.x + dirX * scale);
			int endY = static_cast<int>(ball.y + dirY * scale);
			SDL_RenderDrawLine(renderer, static_cast<int>(ball.x), static_cast<int>(ball.y), endX, endY);
		}
	}

	SDL_RenderPresent(renderer);
}