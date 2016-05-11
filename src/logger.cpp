#include "logger.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Logger::Log(std::string message) {
	std::cout << message.c_str() << std::endl;
}

void Logger::Debug(std::string message) {
	std::cout << message.c_str() << std::endl;
}

void Logger::LogSDLError(std::string message) {
	std::cout << message.c_str() << SDL_GetError() << std::endl;
}

void Logger::LogIMGError(std::string message) {
	std::cout << message.c_str() << IMG_GetError() << std::endl;
}
