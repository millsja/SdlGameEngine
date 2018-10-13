#include "sdlClient.h"

SdlClient::SdlClient(const int screenWidth, const int screenHeight, std::string const& name, bool fullscreen)
{
	srand(time(null));
	this->mouseHidden_ = false;
	this->window_ = null;
	this->InitWindow(screenWidth, screenHeight, name, fullscreen);
	this->InitScreenSurface();
}

SdlClient::~SdlClient()
{
	if (this->window_ != null)
	{
		SDL_DestroyWindow(this->window_);
	}

	SDL_Quit();
}

int SdlClient::GetRandom()
{
	return rand();
}

void SdlClient::SetUpTextRenderer(std::string const& fontPath, int size)
{
	this->textRenderer_.Init(fontPath, size);
}

SDL_Texture* SdlClient::GetTextureFromText(std::string const& text, int fontSize, SDL_Color color, int& w, int& h)
{
	return this->textRenderer_.RenderText(this->renderer_, fontSize, text, color, w, h);
}

void SdlClient::BlitStretched(SDL_Surface* surface)
{
	std::unique_ptr<SDL_Surface, SdlDeleter> windowSurface(SDL_GetWindowSurface(this->window_), SdlDeleter());
	SDL_Surface* w = windowSurface.get();
	SDL_Rect stretchedRect;
	stretchedRect.x = 0;
	stretchedRect.y = 0;
	stretchedRect.w = w->w;
	stretchedRect.h = w->h;
	SDL_BlitScaled(surface, null, windowSurface.get(), &stretchedRect);
}

void SdlClient::BlitSurface(SDL_Surface* surface)
{
	std::unique_ptr<SDL_Surface, SdlDeleter> windowSurface(SDL_GetWindowSurface(this->window_), SdlDeleter());
	SDL_BlitSurface(surface, null, windowSurface.get(), null);
}

void SdlClient::Update()
{
	SDL_UpdateWindowSurface(this->window_);
}

void SdlClient::Delay(int ms)
{
	SDL_Delay(ms);
}

double SdlClient::GetElapsedTime(Uint64 previous, Uint64& now)
{
	now = SDL_GetPerformanceCounter();
	return (double)((now - previous) * 1000 / (double)SDL_GetPerformanceFrequency());
}

void SdlClient::InitScreenSurface()
{
	std::unique_ptr<SDL_Surface, SdlDeleter> screenSurface(SDL_GetWindowSurface(this->window_), SdlDeleter());
	SDL_FillRect(screenSurface.get(), NULL, SDL_MapRGB(screenSurface.get()->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(this->window_);
}

void SdlClient::InitWindow(const int screenWidth, const int screenHeight, std::string const& name, bool fullscreen)
{
	this->window_ = SDL_CreateWindow(
		name.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN);

	if (fullscreen)
	{
		SDL_SetWindowFullscreen(this->window_, SDL_WINDOW_FULLSCREEN);
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("Error initializing PNG loading: \n%s\n", IMG_GetError());
	}

	if (TTF_Init() < 0)
	{
		printf("Error initializing fonts: \n%s\n", IMG_GetError());
	}

	this->renderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(this->renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
}

SDL_Surface* SdlClient::LoadSurface(std::string const& path)
{
	std::unique_ptr<SDL_Surface, SdlDeleter> loadedSurface(IMG_Load(path.c_str()), SdlDeleter());
	SDL_Surface* optimizedSurface = null;
	if (loadedSurface.get() != null)
	{
		SDL_Surface* windowSurface = SDL_GetWindowSurface(this->window_);
		optimizedSurface = SDL_ConvertSurface(loadedSurface.get(), windowSurface->format, null);
		return optimizedSurface;
		// return SurfaceWrapper(optimizedSurface);
	}
	else
	{
		printf("Error loading image: \n%s\n%s\n", path.c_str(), IMG_GetError());
		return null;
	}
}

SDL_Texture* SdlClient::LoadTexture(std::string const& path, int& w, int& h, Color* alphaKey = null)
{
	SDL_Texture* texture = null;
	std::unique_ptr<SDL_Surface, SdlDeleter> surface(this->LoadSurface(path.c_str()), SdlDeleter());
	if (surface.get() != null)
	{
		w = surface.get()->w;
		h = surface.get()->h;
		if (alphaKey != null)
		{
			SDL_SetColorKey(surface.get(), SDL_TRUE, SDL_MapRGB(surface.get()->format, alphaKey->r, alphaKey->g, alphaKey->b));
		}
		return SDL_CreateTextureFromSurface(this->renderer_, surface.get());
	}

	return null;
};

void SdlClient::RenderClear(Color* color)
{
	SDL_SetRenderDrawColor(this->renderer_, color->r, color->g, color->b, color->a);
	SDL_RenderClear(this->renderer_);
}

void SdlClient::RenderClear()
{
	SDL_RenderClear(this->renderer_);
}

void SdlClient::RenderTexture(SDL_Texture* texture)
{
	SDL_RenderCopy(this->renderer_, texture, null, null);
}

void SdlClient::RenderTexture(SDL_Texture* texture, int dX, int dY, int dW, int dH)
{
	SDL_Rect dRect;
	dRect.x = dX;
	dRect.y = dY;
	dRect.w = dW;
	dRect.h = dH;
	SDL_RenderCopy(this->renderer_, texture, null, &dRect);
}

void SdlClient::RenderPresent()
{
	SDL_RenderPresent(this->renderer_);
}

void SdlClient::RenderPoint(int x, int y, Color* color)
{
	SDL_SetRenderDrawColor(this->renderer_, color->r, color->g, color->b, color->a);
	SDL_RenderDrawPoint(this->renderer_, x, y);
}

int SdlClient::GetWindowHeight()
{
	std::unique_ptr<SDL_Surface, SdlDeleter> windowSurface(SDL_GetWindowSurface(this->window_), SdlDeleter());
	return windowSurface.get()->h;
}

int SdlClient::GetWindowWidth()
{
	std::unique_ptr<SDL_Surface, SdlDeleter> windowSurface(SDL_GetWindowSurface(this->window_), SdlDeleter());
	return windowSurface.get()->w;
}

void SdlClient::RenderSetViewpoint(int x, int y, int w, int h)
{
	SDL_Rect viewport;
	viewport.x = x;
	viewport.y = y;
	viewport.w = w;
	viewport.h = h;
	SDL_RenderSetViewport(this->renderer_, &viewport);
}

void SdlClient::RenderSetClear(Color const& color)
{
	SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
}

bool SdlClient::MouseHidden()
{
	return this->mouseHidden_;
}

void SdlClient::HideMouse(bool hide)
{
	this->mouseHidden_ = hide;
	SDL_ShowCursor(!hide);
}
