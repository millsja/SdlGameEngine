#ifndef SDLCLIENT_H
#define SDLCLIENT_H

#include "utilities.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <memory>
#include <string>
#include "textRenderer.h"

class SdlClient
{
public:
	// constructors
	SdlClient(const int sceenWidth, const int screenHeight, const std::string name);
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

	// text rendering
	SDL_Texture* GetTextureFromText(std::string text, SDL_Color color, int& w, int& h);
	void SetUpTextRenderer(const std::string path, int fontSize);

	// load media
	SDL_Surface* LoadSurface(const char* path);
	SDL_Texture* LoadTexture(const char* path, int& w, int& h, Color* alphaKey);

	// utilities
	void Delay(int ms);
	int GetWindowHeight();
	int GetWindowWidth();
	void HideMouse(bool hide);
private:
	TextRenderer textRenderer_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	void InitWindow(const int sceenWidth, const int screenHeight, const std::string name);
	void InitScreenSurface();
};

#endif