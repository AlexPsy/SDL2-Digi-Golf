#include "ball.h"
#include "constant.h"

Ball::Ball() : x(SCREEN_WIDTH / 2.0f), y(SCREEN_HEIGHT / 2.0f), cx(0), cy(0), isDragging(false) {}

void Ball::Update() {
	if (!isDragging) {
		x += cx;
		y += cy;

		// Collision check on boundaries on update
		if (x < BALL_RADIUS || x > SCREEN_WIDTH - BALL_RADIUS) {
			x = x < BALL_RADIUS ? BALL_RADIUS : SCREEN_WIDTH - BALL_RADIUS;
			cx *= -BOUNCE_DAMPING;
		}
		if (y < BALL_RADIUS || y > SCREEN_HEIGHT - BALL_RADIUS) {
			y = y < BALL_RADIUS ? BALL_RADIUS : SCREEN_HEIGHT - BALL_RADIUS;
			cy *= -BOUNCE_DAMPING;
		}

		cx *= 0.99f;
		cy *= 0.99f;
	}
}

// Mouse dragging distance and release calcuation inside controls
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
		SDL_Rect dest{ static_cast<int>(x - BALL_RADIUS), static_cast<int>(y - BALL_RADIUS), BALL_RADIUS * 2, BALL_RADIUS * 2 };
		SDL_RenderCopy(renderer, texture, nullptr, &dest);
	}
}

bool Ball::PointInBall(int x, int y) const {
	float dx = x - this->x;
	float dy = y - this->y;
	return (dx * dx + dy * dy) <= (BALL_RADIUS * BALL_RADIUS);
}