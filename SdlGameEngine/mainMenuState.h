#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <map>
#include "SDL.h"
#include "sdlClient.h"
#include "iGameState.h"
#include "blockState.h"
#include "menuItem.h"

enum MenuItemEnum { QUIT = 0, NEW_NORMAL = 1, NEW_HARD = 2, NEW_ENDLESS = 3, TITLE = 4, SUBTITLE = 5, };
class MainMenuState : public IGameState
{
public:
	MainMenuState(SdlClient* sdlClient);
	void Start();
	void Sleep() {}
private:
	std::map<int, MenuItem> items_;
	SdlClient* sdlClient_;
};

#endif