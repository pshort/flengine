#ifndef WORLD_ENTITY_H
#define WORLD_ENTITY_H

#include <SDL2/SDL.h>
#include <string>
#include "renderer.h"
#include "input.h"
#include <iostream>

// world entity exists in the world
// as a result it can be drawn, it has a position

class WorldEntity {
public:
	WorldEntity(std::string name, Renderer* renderer, Input* input) 
	{ 
		this->name = name; 
		this->renderer = renderer; 
		this->input = input;
		this->readyForCollection = false;
	}

	virtual ~WorldEntity() {}

	virtual void Render() = 0;
	virtual void Update(const unsigned int ticks) = 0;

	std::string GetName() { return name; }

	bool readyForCollection;
	int drawOrder = 0;

protected:

	Renderer* renderer;
	Input* input;

	float x;
	float y;

	bool isVisible;

	float xv;
	float yv;

	SDL_Texture* texture;

	std::string name;

};


#endif
