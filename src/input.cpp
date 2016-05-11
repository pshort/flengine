#include "input.h"
#include "logger.h"

#include <iostream>

Input::Input( void ) { 
	this->textMode = false;
	for(int i = 0; i < MAX_NUM_SCANCODES; i++) {
		currentKeys[i] = false;
	}
}

Input::~Input ( void ) { }

void Input::Update ( void ) { 
	for(int i = 0; i < MAX_NUM_SCANCODES; i++) {
		downKeys[i] = false;
		upKeys[i] = false;
	}
	while(SDL_PollEvent(&event)) {

		if(SDL_KEYDOWN == event.type) {
			int value = event.key.keysym.scancode;
			if(!currentKeys[value] && !textMode) {
				downKeys[value] = true;
			} else if (textMode) {
				downKeys[value] = true;
			}
			currentKeys[value] = true;
		}
	
		if(SDL_KEYUP == event.type) {
			int value = event.key.keysym.scancode;
			upKeys[value] = true;
			currentKeys[value] = false;
		}
	}
}

bool Input::GetKey ( const unsigned int scancode ) {
	return currentKeys[scancode];
}

bool Input::IsKeyDown ( const unsigned int scancode ) {
	return downKeys[scancode];
}

bool Input::IsKeyUp ( const unsigned int scancode ) {
	return upKeys[scancode];
}
