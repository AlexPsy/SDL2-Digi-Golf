#pragma once
#include <vector>
#include <string>
#include "rendering.h"
#include "constant.h"

class Tilemap {
public:
	Tilemap(Renderer* renderer, const std::string& mapPath);
	bool LoadFromFile();
	void Render() const;
	bool IsCollisionTile(int x, int y) const;

private:
	Renderer* renderer;
	std::string mapPath;
	std::vector<std::vector<int>> tiles;
	SDL_Texture* walkableTexture;
	SDL_Texture* collisionTexture;
	int mapWidth;
	int mapHeight;
};