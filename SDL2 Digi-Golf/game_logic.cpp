#include "game_logic.h"
#include "constant.h"

Game::Game() : window(nullptr), renderer(nullptr), ballTexture(nullptr), running(true) {}

Game::~Game() {
	SDL_DestroyTexture(ballTexture);
	delete tilemap;
	delete renderer;
	SDL_DestroyWindow(window);
}

// Initialisation and error checks
bool Game::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) return false;

	window = SDL_CreateWindow("Digi-Golf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) return false;

	renderer = new Renderer(window);
	ballTexture = renderer->LoadTexture("assets/golfball.png");

	ball = Ball(400.0F, 300.0f);

	tilemap = new Tilemap(renderer, TILE_MAP_PATH);
	if (!tilemap->LoadFromFile()) {
		SDL_Log("Failed to load tilemap");
		return false;
	}

	return true;
}

void Game::Run() {
	while (running) {
		ProcessEvents();
		ball.Update(*tilemap);
		Render();
	}
}

void Game::ProcessEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		ball.HandleDragEvent(event);
	}
}

void Game::Render() {
	renderer->Clear();

	tilemap->Render();

//	SDL_SetRenderDrawColor(renderer->Get(), 0, 128, 0, 255);
//	SDL_RenderClear(renderer->Get());

	ball.Render(renderer->Get(), ballTexture);
	directionIndicator.Render(renderer->Get(), ball);

	renderer->Present();
}