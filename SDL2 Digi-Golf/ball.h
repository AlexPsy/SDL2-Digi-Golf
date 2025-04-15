#pragma once
#include <SDL.h>
#include "constant.h"

//struct Ball {
//	float x, y;
//	float cx, cy;
//	bool isMouseDragging;
//	int dragStartX, dragStartY;
//	int currentDragX, currentDragY;

//	bool pointInBall(int x, int y) const;
//};

class Ball {
public:
	Ball();

	void Update();
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