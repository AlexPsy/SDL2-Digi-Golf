#pragma once
#include <SDL.h>
#include "constant.h"

class Tilemap;

class Ball {
public:
	Ball(float startX = SCREEN_WIDTH / 2.0f, float startY = SCREEN_HEIGHT / 2.0f);

	void Update(const Tilemap& tilemap);
	void HandleDragEvent(const SDL_Event& event);
	void Render(SDL_Renderer* renderer, SDL_Texture* texture) const;

	float X() const { return x; }
	float Y() const { return y; }
	bool IsDragging() const { return isDragging; }

	int DragStartX() const { return dragStartX; }
	int DragStartY() const { return dragStartY; }
	int CurrentDragX() const { return currentDragX; }
	int CurrentDragY() const { return currentDragY; }

private:
	float x, y;
	float cx, cy;
	bool isDragging;
	int dragStartX, dragStartY;
	int currentDragX, currentDragY;

	bool PointInBall(int x, int y) const;
};