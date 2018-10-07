#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <memory>
#include <string>
#include "utilities.h"
#include "SDL_ttf.h"

class TextRenderer
{
public:
	TextRenderer() {}
	TextRenderer(const std::string fontPath, int fontSize);
	void Init(const std::string fontPath, int fontSize);
	SDL_Texture* RenderText(SDL_Renderer* renderer, std::string text, SDL_Color color, int& w, int& h);
private:
	std::unique_ptr<TTF_Font, SdlDeleter> font_;
};

#endif