#include "soundManager.h"

void SoundManager::Register(int id, std::string const& path)
{
	this->chunks_.insert(std::pair<int, std::unique_ptr<Mix_Chunk, SdlDeleter>>(id, std::unique_ptr<Mix_Chunk, SdlDeleter>(this->sdlClient_->LoadSoundEffect(path), SdlDeleter())));
}

void SoundManager::PlaySound(int id)
{
	Mix_Chunk* c = null;
	this->sdlClient_->PlaySound(this->chunks_.find(id)->second.get());
}