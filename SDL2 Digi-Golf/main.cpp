#include <SDL.h>
#include "game_logic.h"

int main(int argc, char* argv[]) {
	Game game;
	if (game.Init()) {
		game.Run();
	}

	IMG_Quit();
	SDL_Quit();

	return 0;
}