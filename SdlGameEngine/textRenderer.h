#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <memory>
#include <map>
#include "utilities.h"

class TextRenderer
{
public:
	TextRenderer() {}
	TextRenderer(const std::string fontPath, int fontSize);
	void Init(const std::string fontPath, int fontSize);
	SDL_Texture* RenderText(SDL_Renderer* renderer, int fontSize, std::string text, SDL_Color color, int& w, int& h);
private:
	std::map<int, std::unique_ptr<TTF_Font, SdlDeleter>> fonts_;
};

#endif