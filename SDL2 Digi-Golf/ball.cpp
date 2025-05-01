#include "ball.h"
#include "constant.h"
#include "tilemap.h"

Ball::Ball(float startX, float startY) : x(startX), y(startY), cx(0), cy(0), isDragging(false) {}

void Ball::Update(const Tilemap& tilemap) {
	if (!isDragging) {
		float prevX = x;
		float prevY = y;

		x += cx;
		y += cy;

		bool leftCollision = tilemap.IsCollisionTile(x - BALL_RADIUS, y);
		bool rightCollision = tilemap.IsCollisionTile(x + BALL_RADIUS, y);
		bool topCollision = tilemap.IsCollisionTile(x, y - BALL_RADIUS);
		bool bottomCollision = tilemap.IsCollisionTile(x, y + BALL_RADIUS);

		if (leftCollision || rightCollision) {
			cx *= -BOUNCE_DAMPING;
			x = prevX;
		}

		if (topCollision || bottomCollision) {
			cy *= -BOUNCE_DAMPING;
			y = prevY;
		}

		// Collision check on boundaries on update
		//if (x < BALL_RADIUS || x > SCREEN_WIDTH - BALL_RADIUS) {
		//	x = x < BALL_RADIUS ? BALL_RADIUS : SCREEN_WIDTH - BALL_RADIUS;
		//	cx *= -BOUNCE_DAMPING;
		//}
		//if (y < BALL_RADIUS || y > SCREEN_HEIGHT - BALL_RADIUS) {
		//	y = y < BALL_RADIUS ? BALL_RADIUS : SCREEN_HEIGHT - BALL_RADIUS;
		//	cy *= -BOUNCE_DAMPING;
		//}

		cx *= 0.99f;
		cy *= 0.99f;
	}
}

// Mouse dragging distance and release calculation inside controls
void Ball ::HandleDragEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT && PointInBall(event.button.x, event.button.y)) {
				isDragging = true;
				dragStartX = static_cast<int>(x);
				dragStartY = static_cast<int>(y);
				currentDragX = event.button.x;
				currentDragY = event.button.y;
			}
			break;
		case SDL_MOUSEMOTION:
			if (isDragging) {
				currentDragX = event.motion.x;
				currentDragY = event.motion.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT && isDragging) {
				isDragging = false;
				cx = (dragStartX - currentDragX) * SPEED_FACTOR;
				cy = (dragStartY - currentDragY) * SPEED_FACTOR;
			}
			break;
	}
}

void Ball::Render(SDL_Renderer* renderer, SDL_Texture* texture) const {
	if (texture) {
		SDL_Rect dest{ 
			static_cast<int>(x - BALL_RADIUS), 
			static_cast<int>(y - BALL_RADIUS), 
			BALL_RADIUS * 2, 
			BALL_RADIUS * 2 
		};
		SDL_RenderCopy(renderer, texture, nullptr, &dest);
	}
}

bool Ball::PointInBall(int x, int y) const {
	float dx = x - this->x;
	float dy = y - this->y;
	return (dx * dx + dy * dy) <= (BALL_RADIUS * BALL_RADIUS);
}