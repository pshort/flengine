#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger
{
public:
	static void Log(std::string message);
	static void Debug(std::string message);
	static void LogSDLError(std::string message);
	static void LogIMGError(std::string message);
};

#endif
