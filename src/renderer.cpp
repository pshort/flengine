#include "renderer.h"

#include "logger.h"

Renderer::Renderer(void)
{

}

bool Renderer::Initialize(const char* title, const int width, const int height) {

	this->zoomFactor = 1;
	this->width = width;
	this->height = height;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::LogSDLError("Renderer: SDL Init error : ");
		return false;
	}
	else {
		Logger::Log("Renderer: SDL intialized");
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Logger::LogIMGError("Renderer: Failed to init png loader");
		return false;
	}

    if(TTF_Init() != 0) {
        Logger::LogSDLError("TTF Init Failed : ");
        return false;
    }

	window = SDL_CreateWindow(title, 450, 0, width * zoomFactor, height * zoomFactor, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		Logger::LogSDLError("Renderer: Create window error : ");
		return false;
	}
	else {
		Logger::Log("Renderer: Window created");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		Logger::LogSDLError("Renderer: Create renderer error : ");
		return false;
	}
	else {
		Logger::Log("Renderer: Renderer created");
	}

	return true;
}

void Renderer::ClearScreen(int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
}

SDL_Texture* Renderer::LoadTexture(std::string path) {
	SDL_Texture* result = textures[path];
	if (result != nullptr) {
		//Logger::Log("Cache hit");
		return result;
	} else {
		//Logger::Log("Loading texture");
		SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
		if (texture == nullptr) {
			Logger::LogIMGError("Failed to load Texture in IMG lib : ");
			return nullptr;
		}
		textures[path] = texture;
		return texture;
	}
}

TTF_Font* Renderer::LoadFont(std::string name, std::string file, int size) {
    TTF_Font* result = fonts[name];
    if(result != nullptr) {
        return result;
    } else {
        result = TTF_OpenFont(file.c_str(), size) ;
        if(result == nullptr) {
            Logger::LogSDLError("Failed to load font : ");
            return nullptr;
        }
        fonts[name] = result;
        return result;
    }
}

void Renderer::UnloadTextures() {
	
	if(textures.size() == 0) {
		return;
	}

	for (std::pair<std::string, SDL_Texture*> pair : textures) {
		Logger::Log(pair.first);
		if(pair.second != nullptr) {
			SDL_DestroyTexture(pair.second);
		}
	}

	textures.clear();
}

void Renderer::UnloadFonts() {
    if(fonts.size() == 0) {
        return;
    }

    for(std::pair<std::string, TTF_Font*> pair : fonts) {
        Logger::Log(pair.first);
        if(pair.second != nullptr) {
            TTF_CloseFont(pair.second);
        }
    }

    fonts.clear();
}

void Renderer::RenderText(std::string font, std::string text, int x, int y, unsigned char r, unsigned char g, unsigned char b) {

    SDL_Color color = {r, g, b};

    TTF_Font* ttfFont = fonts[font];

    SDL_Surface* surf = TTF_RenderText_Blended(ttfFont, text.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(this->renderer, surf);

    // draw it
    this->RenderTexture(tex, x, y);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

void Renderer::SetZoom(const int zoom) {
	zoomFactor = zoom;
	SDL_SetWindowSize(window, width * zoomFactor, height * zoomFactor);
	//SDL_RenderSetScale(renderer, zoom, zoom);
}

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y) {

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	dest.x *= zoomFactor;
	dest.y *= zoomFactor;
	dest.w *= zoomFactor;
	dest.h *= zoomFactor;

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Renderer::RenderTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest) {

	SDL_Rect actualDest;

	actualDest.x = dest->x;
	actualDest.y = dest->y;
	actualDest.w = dest->w;
	actualDest.h = dest->h;

	actualDest.x *= zoomFactor;
	actualDest.y *= zoomFactor;
	actualDest.w *= zoomFactor;
	actualDest.h *= zoomFactor;

	SDL_RenderCopy(renderer, texture, src, &actualDest);
}

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y, float rot) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	dest.x *= zoomFactor;
	dest.y *= zoomFactor;
	dest.w *= zoomFactor;
	dest.h *= zoomFactor;

	SDL_RenderCopyEx(renderer, texture, NULL, &dest, rot, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	//SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Renderer::RenderLine(int x1, int y1, int x2, int y2, int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawLine(renderer, x1 * zoomFactor, y1 * zoomFactor, x2 * zoomFactor, y2 * zoomFactor);
}

void Renderer::RenderRect(int x1, int y1, int x2, int y2, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect;
    rect.x = x1 * zoomFactor;
    rect.y = y1 * zoomFactor;
    rect.w = ( x2 - x1 ) * zoomFactor;
    rect.h = ( y2 - y1 ) * zoomFactor;
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::RenderRect(Rect rect, int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_Rect d_rect;
	d_rect.x = rect.x * zoomFactor;
	d_rect.y = rect.y * zoomFactor;
	d_rect.w = rect.w * zoomFactor;
	d_rect.h = rect.h * zoomFactor;
	SDL_RenderFillRect(renderer, &d_rect);
}

void Renderer::Present() {
	SDL_RenderPresent(renderer);
}

Renderer::~Renderer(void)
{
	UnloadTextures();
	// if renderer is null and window then just leave
	if(renderer == nullptr && window == nullptr) 
		return;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}
