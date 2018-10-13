#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <memory>
#include "SDL.h"
#include "utilities.h"
#include "sdlClient.h"

class MenuItem
{
public:
	MenuItem(SdlClient* sdlClient, std::string const& menuText, int fontSize, SDL_Color color, int x, int y, int& w, int& h);
	SDL_Rect* GetLocation() { return &this->dest_; }
	SDL_Texture* GetTexture() { return this->mainItemText_.get(); }
private:
	SDL_Rect dest_;
	std::unique_ptr<SDL_Texture, SdlDeleter> mainItemText_;
};

#endif