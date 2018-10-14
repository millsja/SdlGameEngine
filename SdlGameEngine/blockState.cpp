#include "blockState.h"

BlockState::BlockState(SdlClient* sdlClient, int maxPoints, bool accelerate, float maxYSpeed)
	: scoreKeeper_(sdlClient, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }),
	  soundManager_(sdlClient)
{
	// initialize sdl, window
	this->sdlClient_ = sdlClient;
	this->sdlClient_->HideMouse(true);
	// struct Color gameboy = {(Uint8)216, (Uint8)240, (Uint8)202, 0xFF};
	struct Color black = { 0, 0, 0, 0xFF };
	this->sdlClient_->RenderSetClear(black);
	this->sdlClient_->RenderClear();
	this->sdlClient_->Update();
	this->soundManager_.Register(SoundEffectEnum::WIN, ".\\audio\\win.wav");
	this->soundManager_.Register(SoundEffectEnum::LOSE, ".\\audio\\lose.wav");

	int windowW = this->sdlClient_->GetWindowWidth();
	int windowH = this->sdlClient_->GetWindowHeight();

	// init collision detector, scorekeeper
	this->collisionDetector_.SetH(this->sdlClient_->GetWindowHeight());
	this->collisionDetector_.SetW(this->sdlClient_->GetWindowWidth());
	this->collisionDetector_.SetObjects(&(this->objects_));
	this->scoreKeeper_.SetWinThreshold(maxPoints);

	// load player
	int w = 0, h = 0;
	Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Texture* sprite = this->sdlClient_->LoadTexture(".\\textures\\breakout_player.png", w, h, &white);
	this->collection_.AddTexture(TextureIdEnum::SPRITE_1, sprite);
	this->soundManager_.Register(SoundEffectEnum::HIT, ".\\audio\\enemy_wall_hit.wav");
	this->objects_.push_back(std::unique_ptr<IGameObject>(new PlayerObject(this->sdlClient_, TextureIdEnum::SPRITE_1, windowW/2 - w/2, windowH - w/2 - 25, w, h, &(this->soundManager_), (int)SoundEffectEnum::HIT)));

	// load enemy 
	w = 0, h = 0;
	SDL_Texture* enemySprite = this->sdlClient_->LoadTexture(".\\textures\\breakout_player.png", w, h, &white);
	this->collection_.AddTexture(TextureIdEnum::SPRITE_3, enemySprite);
	EnemyObject* enemy = new EnemyObject(this->sdlClient_, TextureIdEnum::SPRITE_3, windowW / 2 - w / 2, 50, w, h, 50, &(this->soundManager_), SoundEffectEnum::HIT);
	this->objects_.push_back(std::unique_ptr<IGameObject>(enemy));

	// load ball
	w = 0, h = 0;
	int yDirection = this->sdlClient_->GetRandom() % 2 * -2 + 1;
	int xDirection = this->sdlClient_->GetRandom() % 2 * -2 + 1;
	SDL_Texture* ballSprite = this->sdlClient_->LoadTexture(".\\textures\\ball.png", w, h, &white);
	this->collection_.AddTexture(TextureIdEnum::SPRITE_2, ballSprite);
	BallObject* ball = new BallObject(this->sdlClient_, TextureIdEnum::SPRITE_2, windowW / 2 - w / 2, windowH / 2, w, h, xDirection * 25, yDirection * 100, accelerate, maxYSpeed);
	ball->AttachObserver(enemy);
	this->objects_.push_back(std::unique_ptr<IGameObject>(ball));

	// load boundaries
	this->soundManager_.Register(SoundEffectEnum::SCORE, ".\\audio\\score_change.wav");
	this->objects_.push_back(std::unique_ptr<IGameObject>(new BoundaryObject(TextureIdEnum::NO_RENDER, -2, 0, 2, windowH, &this->scoreKeeper_, ball, 0, 0, &(this->soundManager_), SoundEffectEnum::HIT)));
	this->objects_.push_back(std::unique_ptr<IGameObject>(new BoundaryObject(TextureIdEnum::NO_RENDER, windowW, 0, 2, windowH, &this->scoreKeeper_, ball, 0, 0, &(this->soundManager_), SoundEffectEnum::HIT)));
	this->objects_.push_back(std::unique_ptr<IGameObject>(new BoundaryObject(TextureIdEnum::NO_RENDER, 0, -2, windowW, 2, &this->scoreKeeper_, ball, 1, 0, &(this->soundManager_), SoundEffectEnum::SCORE)));
	this->objects_.push_back(std::unique_ptr<IGameObject>(new BoundaryObject(TextureIdEnum::NO_RENDER, 0, windowH, windowW, 2, &this->scoreKeeper_, ball, 0, 1, &(this->soundManager_), SoundEffectEnum::SCORE)));
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
			IControllable* a = null;
			if (a = dynamic_cast<IControllable*>(it->get()))
			{
				a->HandleEvents(&e, keystates);
			}

			IEveryFrame* b = null;
			if (b = dynamic_cast<IEveryFrame*>(it->get()))
			{
				b->HandleNewFrame();
			}
		}

		this->collisionDetector_.FindCollisions();

		GameStatusEnum gameStatus = this->scoreKeeper_.GetGameStatus();
		if (gameStatus == GameStatusEnum::ENEMY_VICTORY)
		{
			this->soundManager_.PlaySound(SoundEffectEnum::LOSE);
			this->sdlClient_->RenderClear();
			int hw = 0, hh = 0;
			int sw = 0, sh = 0;
			std::unique_ptr<SDL_Texture, SdlDeleter> text = std::unique_ptr<SDL_Texture, SdlDeleter>(this->sdlClient_->GetTextureFromText("YOU LOST!", FontSizeEnum::H1, SDL_Color{ 255, 0, 0 }, hw, hh), SdlDeleter());
			this->sdlClient_->RenderTexture(text.get(), this->sdlClient_->GetWindowWidth() / 2 - hw / 2, this->sdlClient_->GetWindowHeight() / 10 * 3, hw, hh);
			std::unique_ptr<SDL_Texture, SdlDeleter> subText = std::unique_ptr<SDL_Texture, SdlDeleter>(this->sdlClient_->GetTextureFromText("(how sad)", FontSizeEnum::P, SDL_Color{ 255, 0, 0 }, sw, sh), SdlDeleter());
			this->sdlClient_->RenderTexture(subText.get(), this->sdlClient_->GetWindowWidth() / 2 - sw / 2, this->sdlClient_->GetWindowHeight() / 10 * 3 + hh, sw, sh);
			this->sdlClient_->Update();
			while (cont)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_MOUSEBUTTONDOWN:
						cont = false;
						break;
					case SDL_KEYDOWN:
						cont = false;
						break;
					}
				}
			}
			cont = false;
			break;
		}
		else if (gameStatus == GameStatusEnum::PLAYER_VICTORY)
		{
			this->soundManager_.PlaySound(SoundEffectEnum::WIN);
			int hw = 0, hh = 0;
			int sw = 0, sh = 0;
			this->sdlClient_->RenderClear();
			std::unique_ptr<SDL_Texture, SdlDeleter> text = std::unique_ptr<SDL_Texture, SdlDeleter>(this->sdlClient_->GetTextureFromText("YOU WON!", FontSizeEnum::H1, SDL_Color{ 118, 238, 0 }, hw, hh), SdlDeleter());
			this->sdlClient_->RenderTexture(text.get(), this->sdlClient_->GetWindowWidth() / 2 - hw / 2, this->sdlClient_->GetWindowHeight() / 10 * 3, hw, hh);
			std::unique_ptr<SDL_Texture, SdlDeleter> subText = std::unique_ptr<SDL_Texture, SdlDeleter>(this->sdlClient_->GetTextureFromText("(how nice)", FontSizeEnum::P, SDL_Color{ 118, 238, 0 }, sw, sh), SdlDeleter());
			this->sdlClient_->RenderTexture(subText.get(), this->sdlClient_->GetWindowWidth() / 2 - sw / 2, this->sdlClient_->GetWindowHeight() / 10 * 3 + hh, sw, sh);
			this->sdlClient_->Update();
			while (cont)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_MOUSEBUTTONDOWN:
						cont = false;
						break;
					case SDL_KEYDOWN:
						cont = false;
						break;
					}
				}
			}
			this->sdlClient_->RenderSetClear(Color{ 0, 0, 0, 0 });
			cont = false;
			break;
		}

		this->sdlClient_->RenderClear();
		int scoreW = 0, scoreH = 0;
		SDL_Texture* scoreTexture = this->scoreKeeper_.GetScoreTexture(scoreW, scoreH);
		this->sdlClient_->RenderTexture(scoreTexture, this->sdlClient_->GetWindowWidth() / 2 - scoreW / 2, this->sdlClient_->GetWindowHeight() - 40, scoreW, scoreH);
		// this->sdlClient_->RenderTexture(scoreTexture, this->sdlClient_->GetWindowWidth() / 2 - scoreW / 2, 5, scoreW, scoreH);

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