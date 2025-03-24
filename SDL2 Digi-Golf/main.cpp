#include <SDL.h>
#include "constant.h"
#include "ball.h"
#include "rendering.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = SDL_CreateWindow("Digi-Golf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture* ballTexture = loadTexture(renderer, "golfball.png");
	if (!ballTexture) {
		SDL_Log("Failed to load texture: %s", IMG_GetError());
		return 1;
	}

	Ball ball{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0, 0, false };

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;

				// Mouse controls preferable move to seperate file when actually doing properly
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT && ball.pointInBall(event.button.x, event.button.y)) {
						ball.isMouseDragging = true;
						ball.dragStartX = static_cast<int>(ball.x);
						ball.dragStartY = static_cast<int>(ball.y);
						ball.currentDragX = event.button.x;
						ball.currentDragY = event.button.y;
					}
					break;

				case SDL_MOUSEMOTION:
					if (ball.isMouseDragging) {
						ball.currentDragX = event.motion.x;
						ball.currentDragY = event.motion.y;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT && ball.isMouseDragging) {
						ball.isMouseDragging = false;
						ball.cx = (ball.dragStartX - ball.currentDragX) * SPEED_FACTOR;
						ball.cy = (ball.dragStartY - ball.currentDragY) * SPEED_FACTOR;
					}
					break;
			}
		}

		// collision with edges of screen (move to ball.cpp later)
		if (!ball.isMouseDragging) {
			ball.x += ball.cx;
			ball.y += ball.cy;

			if (ball.x < BALL_RADIUS || ball.x > SCREEN_WIDTH - BALL_RADIUS) {
				ball.x = ball.x < BALL_RADIUS ? BALL_RADIUS : SCREEN_WIDTH - BALL_RADIUS;
				ball.cx *= -BOUNCE_DAMPING;
			}
			if (ball.y < BALL_RADIUS || ball.y > SCREEN_HEIGHT - BALL_RADIUS) {
				ball.y = ball.y < BALL_RADIUS ? BALL_RADIUS : SCREEN_HEIGHT - BALL_RADIUS;
				ball.cy *= -BOUNCE_DAMPING;
			}

			ball.cx *= 0.99f;
			ball.cy *= 0.99f;
		}

		renderScene(renderer, ball, ballTexture);
	}

	SDL_DestroyTexture(ballTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}