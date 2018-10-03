#include "blockState.h"

BlockState::BlockState(SdlClient* sdlClient)
{
	// initialize sdl, window
	this->sdlClient_ = sdlClient;
	this->sdlClient_->HideMouse(true);
	struct Color gameboy = {(Uint8)216, (Uint8)240, (Uint8)202, 0xFF};
	this->sdlClient_->RenderSetClear(&gameboy);
	this->sdlClient_->RenderClear();
	this->sdlClient_->Update();

	// init collision detector
	this->collisionDetector_.SetH(this->sdlClient_->GetWindowHeight());
	this->collisionDetector_.SetW(this->sdlClient_->GetWindowWidth());
	this->collisionDetector_.SetObjects(&(this->objects_));

	// load player
	int w = 0, h = 0;
	Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Texture* sprite = this->sdlClient_->LoadTexture("C:\\Users\\James\\source\\repos\\SDLTutorials\\Debug\\breakout_player.png", w, h, &white);
	this->collection_.AddTexture(TextureIdEnum::SPRITE_1, sprite);
	this->objects_.push_back(std::unique_ptr<IGameObject>(new PlayerObject(TextureIdEnum::SPRITE_1, 150, 400, w, h)));

	// load boundaries
	int windowW = this->sdlClient_->GetWindowWidth();
	int windowH = this->sdlClient_->GetWindowHeight();
	this->objects_.push_back(std::unique_ptr<IGameObject>(new BoundaryObject(TextureIdEnum::NO_RENDER, -2, 0, 2, windowH)));
	this->objects_.push_back(std::unique_ptr<IGameObject>(new BoundaryObject(TextureIdEnum::NO_RENDER, windowW, 0, 2, windowH)));
}

void BlockState::Start()
{
	SDL_Event e;

	bool upped = false;
	bool cont = true;
	const Uint8* currentKeyStates = null;
	while (cont)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				cont = false;
				break;
			}
		}

		const Uint8* keystates = SDL_GetKeyboardState(null);

		if (keystates[SDL_SCANCODE_ESCAPE])
		{
			cont = false;
			break;
		}

		for (std::vector<std::unique_ptr<IGameObject>>::iterator it = this->objects_.begin(); it != objects_.end(); it++)
		{
			it->get()->HandleEvents(&e, keystates);
		}

		while (this->collisionDetector_.FindCollisions())
		{
		}

		this->sdlClient_->RenderClear();
		for (std::vector<std::unique_ptr<IGameObject>>::iterator it = this->objects_.begin(); it != objects_.end(); it++)
		{
			SDL_Rect* dest = it->get()->GetDestination();
			int textureId = it->get()->GetTextureId();
			if (!textureId == TextureIdEnum::NO_RENDER)
			{
				this->sdlClient_->RenderTexture(this->collection_.GetTexture(textureId), dest->x, dest->y, dest->w, dest->h);
			}
		}
		this->sdlClient_->Update();
	}
}

void BlockState::Sleep()
{
}

BlockState::~BlockState()
{
	// delete this->_sdlClient;
	// this->_sdlClient = null;

	// delete this->_collection;
	// this->_collection = null;
}