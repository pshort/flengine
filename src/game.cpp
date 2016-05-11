#include "game.h"
#include <iostream>
#include "logger.h"
#include <SDL2/SDL.h>

#include <stdlib.h>
#include <time.h>

#include <string>
#include <sstream>

Game::Game( const char* title, const int width, const int height ) {
	std::srand(time(NULL));

	renderer = new Renderer();
	renderer->Initialize(title, width, height);
	input = new Input();
}

bool Game::InternalInitialize( void ) {

	lastTicks = SDL_GetTicks();
	currentTicks = lastTicks;
	fpsAccumulator = 1000;
	return true;
}

void Game::Run(void) {

	InternalInitialize();
	Initialize();

	running = true;

	while (running) {
		currentTicks = SDL_GetTicks();

		this->input->Update();

		if(this->input->GetKey(SDL_SCANCODE_ESCAPE)) {
			running = false;
		}

		InternalUpdate(currentTicks - lastTicks);
		Update(currentTicks - lastTicks);

		InternalRender();
//		Render();
        renderer->Present();

		lastTicks = currentTicks;
		fpsCount++;
	}

	Shutdown();
}

void Game::InternalUpdate(const unsigned int ticks) {

	fpsAccumulator -= ticks;

	if (fpsAccumulator <= 0) {

		std::ostringstream oss;
		oss << "FPS : " << fpsCount;
		Logger::Log(oss.str());

		fpsCount = 0;
		fpsAccumulator = 1000;

	}
}

bool sortEntities(const WorldEntity* first, const WorldEntity* second) {
	return first->drawOrder < second->drawOrder;
}

void Game::InternalRender(void) {
	renderer->ClearScreen(0, 0, 0);

	entities.sort(sortEntities);

	for (auto e : entities) {
		e->Render();
	}


}

void Game::Shutdown(void) {
 	for (auto e : entities) {
		e->~WorldEntity();
	}
	entities.clear();
}

Game::~Game( void ) {

	Shutdown();
	input->~Input();
	renderer->~Renderer();
}
