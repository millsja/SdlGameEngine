#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <memory>
#include "SDL_mixer.h"
#include "utilities.h"
#include "sdlClient.h"

class SoundManager
{
public:
	SoundManager(SdlClient* sdlClient) { this->sdlClient_ = sdlClient; }
	void Register(int id, std::string const& path);
	void PlaySound(int id);
private:
	SdlClient* sdlClient_;
	std::map<int, std::unique_ptr<Mix_Chunk, SdlDeleter>> chunks_;
};

#endif