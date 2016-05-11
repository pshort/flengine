#ifndef GAME_H
#define GAME_H

#include "renderer.h"
#include "input.h"
#include <SDL2/SDL.h>
#include <list>
#include <memory>
#include "worldentity.h"

class Game
{
public:
					Game( const char* title, const int width, const int height );
					~Game( void );

	void			Shutdown(void);
	void			Run( void );
	virtual bool	Initialize(void) = 0;
	virtual	void	Update(const unsigned int ticks) = 0;
	Renderer*		GetRenderer();

protected:

	bool			InternalInitialize(void);
	void			InternalUpdate(const unsigned int ticks);

	void			InternalRender(void);

protected:
	bool running;
	Renderer* renderer;
	Input* input;

	unsigned int lastTicks, currentTicks;
	unsigned int fpsCount;
	int fpsAccumulator;

	std::list<WorldEntity*> entities;

};

#endif

