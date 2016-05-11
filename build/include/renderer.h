#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include <iostream>

#include "rect.h"

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	bool Initialize(const char* title, const int width, const int height);

	SDL_Texture* LoadTexture(std::string path);
	void UnloadTextures();
	void RenderTexture(SDL_Texture* texture, int x, int y);
	void RenderTexture(SDL_Texture* texture, int x, int y, float rot);
	void RenderTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest);

    TTF_Font* LoadFont(std::string name, std::string file, int size);
    void UnloadFonts();
    void RenderText(std::string font, std::string text, int x, int y, unsigned char r, unsigned char g, unsigned char b);

	void RenderLine(int x1, int y1, int x2, int y2, int r, int g, int b);

    void RenderRect(int x1, int y1, int x2, int y2, int r, int g, int b);
	void RenderRect(Rect rect, int r, int g, int b);

	void ClearScreen(int r, int g, int b);

	void Present();

	void SetZoom(const int zoom);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int zoomFactor;
	int width;
	int height;

	std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};

#endif
