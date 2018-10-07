#include "textRenderer.h"

TextRenderer::TextRenderer(const std::string fontPath, int fontSize)
{
	TTF_Font* f = TTF_OpenFont(fontPath.c_str(), fontSize);
	this->font_ = std::unique_ptr<TTF_Font, SdlDeleter>(f, SdlDeleter());
}

SDL_Texture* TextRenderer::RenderText(SDL_Renderer* renderer, std::string text, SDL_Color color, int& w, int& h)
{
	if (this->font_.get() != null)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(this->font_.get(), text.c_str(), color);
		std::unique_ptr<SDL_Surface, SdlDeleter> tSurface = std::unique_ptr<SDL_Surface, SdlDeleter>(surface, SdlDeleter());
		w = tSurface.get()->w;
		h = tSurface.get()->h;
		if (tSurface.get() != null)
		{
			return SDL_CreateTextureFromSurface(renderer, tSurface.get());
		}
	}

	return null;
}

void TextRenderer::Init(const std::string fontPath, int fontSize)
{
	TTF_Font* f = TTF_OpenFont(fontPath.c_str(), fontSize);
	this->font_ = std::unique_ptr<TTF_Font, SdlDeleter>(f, SdlDeleter());
}