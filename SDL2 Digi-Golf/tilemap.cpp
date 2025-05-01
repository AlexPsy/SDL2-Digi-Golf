#include <fstream>
#include <sstream>
#include <stdexcept>
#include "tilemap.h"

Tilemap::Tilemap(Renderer* renderer, const std::string& mapPath)
	: renderer(renderer), mapPath(mapPath), walkableTexture(nullptr), collisionTexture(nullptr), mapWidth(0), mapHeight(0) {}

bool Tilemap::LoadFromFile() {
	std::ifstream file(mapPath);
	if (!file.is_open()) {
		SDL_Log("Failed to open map file: %s", mapPath.c_str());
		return false;
	}

	std::string line;

	if (!std::getline(file, line)) return false;
	std::istringstream dimStream(line);
	if (!(dimStream >> mapWidth >> mapHeight)) return false;

	while (std::getline(file, line)) {
		std::vector<int> row;
		std::istringstream iss(line);
		int tile;

		while (iss >> tile) {
			row.push_back(tile);
		}
		if (!row.empty()) {
			tiles.push_back(row);
		}
	}

	walkableTexture = renderer->LoadTexture("assets/tiles/grass.png");
	collisionTexture = renderer->LoadTexture("assets/tiles/grass_border.png");

	return walkableTexture && collisionTexture;
}

void Tilemap::Render() const {
	for (int y = 0; y < tiles.size(); y++) {
		for (int x = 0; x < tiles[y].size(); x++) {
			SDL_Texture* txtr = tiles[y][x] == COLLISION_TILE ? collisionTexture : walkableTexture;
				
			SDL_Rect destRect = {
				x * TILE_SIZE,
				y * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE
			};

			SDL_RenderCopy(renderer->Get(), txtr, nullptr, &destRect);
			
		}
	}
}

bool Tilemap::IsCollisionTile(int x, int y) const {
	int tileX = x / TILE_SIZE;
	int tileY = y / TILE_SIZE;

	if (tileY < 0 || tileY >= tiles.size()) return true;
	if (tileX < 0 || tileX >= tiles[tileY].size()) return true;

	return tiles[tileY][tileX] == COLLISION_TILE;
}