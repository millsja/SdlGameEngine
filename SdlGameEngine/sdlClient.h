#ifndef SDLCLIENT_H
#define SDLCLIENT_H

#include <string>
#include <stdio.h>
#include <time.h>
#include "SDL_image.h"
#include "utilities.h"
#include "textRenderer.h"

enum FontSizeEnum { P = 28, H1 = 100, };

class SdlClient
{
public:
	// constructors
	SdlClient(const int sceenWidth, const int screenHeight, std::string const& name, bool fullscreen);
	~SdlClient();

	// apply surfaces
	void BlitSurface(SDL_Surface* surface);
	void BlitStretched(SDL_Surface* surface);
	void Update();

	// render
	void RenderSetClear(Color const& color);
	void RenderTexture(SDL_Texture* texture);
	void RenderTexture(SDL_Texture* texture, int dX, int dY, int dW, int dH);
	void RenderClear(Color* color);
	void RenderClear();
	void RenderPresent();
	void RenderPoint(int x, int y, Color* color);
	void RenderSetViewpoint(int x, int y, int w, int h);

	// text rendering
	SDL_Texture* GetTextureFromText(std::string const& text, int fontSize, SDL_Color color, int& w, int& h);
	void SetUpTextRenderer(std::string const& path, int fontSize);

	// load media
	SDL_Surface* LoadSurface(std::string const& path);
	SDL_Texture* LoadTexture(std::string const& path, int& w, int& h, Color* alphaKey);

	// utilities
	double GetElapsedTime(Uint64 previousTime, Uint64& currentTime);
	void Delay(int ms);
	int GetWindowHeight();
	int GetWindowWidth();
	void HideMouse(bool hide);
	bool MouseHidden();
	int GetRandom();
private:
	bool mouseHidden_;
	TextRenderer textRenderer_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	void InitWindow(const int sceenWidth, const int screenHeight, std::string const& name, bool fullscreen);
	void InitScreenSurface();
};

#endif