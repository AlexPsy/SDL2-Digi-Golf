#include "ball.h"
#include "constant.h"

bool Ball::pointInBall(int x, int y) const {
	float dx = x - this->x;
	float dy = y - this->y;
	return (dx * dx + dy * dy) <= (BALL_RADIUS * BALL_RADIUS);
}