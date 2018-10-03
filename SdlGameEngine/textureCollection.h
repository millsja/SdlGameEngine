#ifndef TEXTURECOLLECTION_H
#define TEXTURECOLLECTION_H

#include "utilities.h"
#include "SDL.h"
#include <map>
#include <memory>

// #define _TextureMap std::map<int, TextureWrapper*>

class TextureCollection
{
public:
	void AddTexture(int id, SDL_Texture* texture);
	void RemoveTexture(int id);
	SDL_Texture* GetTexture(int id);
private:
	std::map<int, std::unique_ptr<SDL_Texture, SdlDeleter>> collection_;
};

#endif