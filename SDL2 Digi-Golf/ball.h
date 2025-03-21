#pragma once

struct Ball {
	float x, y;
	float cx, cy;
	bool isMouseDragging;
	int dragStartX, dragStartY;
	int currentDragX, currentDragY;

	bool pointInBall(int x, int y) const;
};