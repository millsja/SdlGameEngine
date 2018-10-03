#ifndef SDLCLIENT_H
#define SDLCLIENT_H

#include "utilities.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <memory>

class SdlClient
{
public:
	// constructors
	SdlClient(const int sceenWidth, const int screenHeight);
	~SdlClient();

	// apply surfaces
	void BlitSurface(SDL_Surface* surface);
	void BlitStretched(SDL_Surface* surface);
	void Update();

	// render
	void RenderSetClear(Color* color);
	void RenderTexture(SDL_Texture* texture);
	void RenderTexture(SDL_Texture* texture, int dX, int dY, int dW, int dH);
	void RenderClear(Color* color);
	void RenderClear();
	void RenderPresent();
	void RenderPoint(int x, int y, Color* color);
	void RenderSetViewpoint(int x, int y, int w, int h);

	// load media
	SDL_Surface* LoadSurface(const char* path);
	SDL_Texture* LoadTexture(const char* path, int& w, int& h, Color* alphaKey);

	// utilities
	void Delay(int ms);
	int GetWindowHeight();
	int GetWindowWidth();
	void HideMouse(bool hide);
private:
	SDL_Window* window_;
	// SDL_Surface* _screenSurface;
	SDL_Renderer* renderer_;
	void InitWindow(const int sceenWidth, const int screenHeight);
	void InitScreenSurface();
};

#endif