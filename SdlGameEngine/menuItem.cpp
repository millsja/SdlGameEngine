#include "menuItem.h"

MenuItem::MenuItem(SdlClient* sdlClient, std::string const& menuText, int fontSize, SDL_Color color, int x, int y, int& w, int& h)
{
	this->mainItemText_ = std::unique_ptr<SDL_Texture, SdlDeleter>(sdlClient->GetTextureFromText(menuText.c_str(), fontSize, color, w, h), SdlDeleter());
	this->dest_.x = sdlClient->GetWindowWidth() / 2 - w / 2;
	this->dest_.y = y;
	this->dest_.w = w;
	this->dest_.h = h;
}
