#include "mainMenuState.h"

MainMenuState::MainMenuState(SdlClient* sdlClient)
{
	// initialize sdl, window
	this->sdlClient_ = sdlClient;
	this->sdlClient_->HideMouse(false);
	struct Color black = { 0, 0, 0, 0xFF };
	this->sdlClient_->RenderSetClear(black);
	this->sdlClient_->RenderClear();
	this->sdlClient_->Update();

	int windowW = this->sdlClient_->GetWindowWidth();
	int windowH = this->sdlClient_->GetWindowHeight();

	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	const std::string mainTitle = "NOT PONG";
	int w = 0, h = 0;
	int y = this->sdlClient_->GetWindowHeight() / 10 * 2;
	this->items_.insert(std::pair<int, MenuItem>((int)MenuItemEnum::TITLE, MenuItem(this->sdlClient_, mainTitle, (int)FontSizeEnum::H1, white, 0, y, w, h)));

	y += h - 15;
	const std::string subtitle = "## THIS IS TOTALLY NOT PONG ##";
	this->items_.insert(std::pair<int, MenuItem>((int)MenuItemEnum::SUBTITLE, MenuItem(this->sdlClient_, subtitle, (int)FontSizeEnum::P, white, 0, y, w, h)));

	y += h + 25;
	const std::string normalName = "Normal";
	this->items_.insert(std::pair<int, MenuItem>((int)MenuItemEnum::NEW_NORMAL, MenuItem(this->sdlClient_, normalName, (int)FontSizeEnum::P, white, 0, y, w, h)));

	const std::string hardName = "Hard";
	y += h;
	this->items_.insert(std::pair<int, MenuItem>((int)MenuItemEnum::NEW_HARD, MenuItem(this->sdlClient_, hardName, (int)FontSizeEnum::P, white, 0, y, w, h)));

	const std::string endlessName = "Endless";
	y += h;
	this->items_.insert(std::pair<int, MenuItem>((int)MenuItemEnum::NEW_ENDLESS, MenuItem(this->sdlClient_, endlessName, FontSizeEnum::P, white, 0, y, w, h)));

	const std::string quitName = "Quit";
	y += h;
	this->items_.insert(std::pair<int, MenuItem>((int)MenuItemEnum::QUIT, MenuItem(this->sdlClient_, quitName, FontSizeEnum::P, white, 0, y, w, h)));
}

void MainMenuState::Start()
{
	SDL_Event e;

	bool upped = false;
	bool cont = true;
	const Uint8* currentKeyStates = null;
	while (cont)
	{
		if (this->sdlClient_->MouseHidden())
		{
			this->sdlClient_->HideMouse(false);
		}

		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				cont = false;
				break;
			case SDL_MOUSEBUTTONUP:
				for (std::map<int, MenuItem>::iterator it = this->items_.begin(); it != this->items_.end(); it++)
				{
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);
					SDL_Rect* dest = it->second.GetLocation();
					if (x > dest->x
						&& x < dest->x + dest->w
						&& y > dest->y
						&& y < dest->y + dest->h)
					{
						switch (it->first)
						{
						case MenuItemEnum::NEW_NORMAL:
							BlockState(this->sdlClient_, 5, false, 200).Start();
							break;
						case MenuItemEnum::NEW_HARD:
							BlockState(this->sdlClient_, 15, true, 200).Start();
							break;
						case MenuItemEnum::NEW_ENDLESS:
							BlockState(this->sdlClient_, -1, true, 200).Start();
							break;
						case MenuItemEnum::QUIT:
							cont = false;
							break;
						}
					}
				}
				break;
			}
		}

		const Uint8* keystates = SDL_GetKeyboardState(null);

		// if (keystates[SDL_SCANCODE_ESCAPE])
		// {
		// 	cont = false;
		// 	break;
		// }

		this->sdlClient_->RenderClear();

		for (std::map<int, MenuItem>::iterator it = this->items_.begin(); it != this->items_.end(); it++)
		{
			int x = it->second.GetLocation()->x;
			int y = it->second.GetLocation()->y;
			int w = it->second.GetLocation()->w;
			int h = it->second.GetLocation()->h;
			this->sdlClient_->RenderTexture(it->second.GetTexture(), x, y, w, h);
		}

		this->sdlClient_->Update();
	}
}