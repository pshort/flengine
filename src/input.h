#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

#define MAX_NUM_SCANCODES 512

class Input {

	public:

				Input ( void );
				~Input ( void );

	void		Update ( void );

	bool		GetKey ( const unsigned int scancode );
	bool		IsKeyDown ( const unsigned int scancode );
	bool		IsKeyUp ( const unsigned int scancode );

	private:

	bool textMode;

	int currentKeys[MAX_NUM_SCANCODES];
	int downKeys[MAX_NUM_SCANCODES];
	int upKeys[MAX_NUM_SCANCODES];

	SDL_Event event;

};


#endif
