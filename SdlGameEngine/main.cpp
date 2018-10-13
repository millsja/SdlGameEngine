#include "sdlClient.h"
#include "utilities.h"
#include "stateStack.h"
#include "blockState.h"
#include "mainMenuState.h"
#include "SDL.h"
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const std::string NAME = "SDL Game";
const std::string FONT_PATH = "C:\\Users\\James\\source\\repos\\SdlGameEngine\\Debug\\VT323-Regular.ttf";

int main( int argc, char* args[] )
{
	SdlClient client = { SCREEN_WIDTH, SCREEN_HEIGHT, NAME, true };
	client.SetUpTextRenderer(FONT_PATH, (int)FontSizeEnum::H1);
	client.SetUpTextRenderer(FONT_PATH, (int)FontSizeEnum::P);

	MainMenuState state(&client);
	state.Start();

	// StateStack stack;
	// stack.Push(&state);
	// stack.Run();

	return 0;
}