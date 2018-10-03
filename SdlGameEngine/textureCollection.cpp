#include "textureCollection.h"

void TextureCollection::AddTexture(int id, SDL_Texture* texture)
{
	this->collection_.insert(std::pair<int, std::unique_ptr<SDL_Texture, SdlDeleter>>(id, texture));
}

void TextureCollection::RemoveTexture(int id)
{
	std::map<int, std::unique_ptr<SDL_Texture, SdlDeleter>>::iterator it = this->collection_.find(id);
	if (it != this->collection_.end())
	{
		// SDL_DestroyTexture(it->second);
		// delete it->second;
		this->collection_.erase(it);
	}
}

SDL_Texture* TextureCollection::GetTexture(int id)
{
	std::map<int, std::unique_ptr<SDL_Texture, SdlDeleter>>::iterator it = this->collection_.find(id);

	if (it == this->collection_.end())
	{
		return null;
	}
	else
	{
		return it->second.get();
	}
}