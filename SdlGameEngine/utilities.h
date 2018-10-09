#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>
#include "SDL.h"
#include "SDL_ttf.h"

#define null NULL

struct Velocity
{
	int pixels;
	double ms;
};

struct Coords
{
	int x;
	int y;
};

struct Color 
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct SdlDeleter 
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
	void operator()(SDL_Surface* p) const { SDL_FreeSurface(p); }
	void operator()(TTF_Font* p) const { TTF_CloseFont(p); }
};

// typedef std::unique_ptr<SDL_Surface, SdlDeleter> UniqueSdlSurface;
// typedef std::unique_ptr<SDL_Texture, SdlDeleter> UniqueSdlTexture;
// typedef std::unique_ptr<SDL_Window, SdlDeleter> UniqueSdlWindow;
// typedef std::unique_ptr<SDL_Renderer, SdlDeleter> UniqueSdlRenderer;

// std::unique_ptr<SDL_Surface, SdlDeleter>;
// std::unique_ptr<SDL_Texture, SdlDeleter>;
// std::unique_ptr<SDL_Window, SdlDeleter>;
// std::unique_ptr<SDL_Renderer, SdlDeleter>;

#endif
