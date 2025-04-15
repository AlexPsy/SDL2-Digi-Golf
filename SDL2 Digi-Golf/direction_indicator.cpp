#include "direction_indicator.h"
#include <cmath>


void DirectionIndicator::Render(SDL_Renderer* renderer, const Ball& ball) const {
	if (ball.IsDragging()) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		
		// direction of mouse movement check
		float dirX = static_cast<float>(ball.DragStartX() - ball.CurrentDragX());
		float dirY = static_cast<float>(ball.DragStartY() - ball.CurrentDragY());
		float distance = std::sqrt(dirX * dirX + dirY * dirY);
		
		if (distance > 0) {
			float scale = LINE_LENGTH / distance;
			int endX = static_cast<int>(ball.X() + dirX * scale);
			int endY = static_cast<int>(ball.Y() + dirY * scale);

			SDL_RenderDrawLine(renderer, static_cast<int>(ball.X()), static_cast<int>(ball.Y()), endX, endY);
		}
	}
}