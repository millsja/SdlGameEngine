#include "sdlClient.h"
#include "utilities.h"
#include "stateStack.h"
#include "blockState.h"
#include "SDL.h"
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const string NAME = "SDL Game";
const string FONT_PATH = "C:\\Users\\James\\source\\repos\\SdlGameEngine\\Debug\\VT323-Regular.ttf";

int main( int argc, char* args[] )
{
	SdlClient client = { SCREEN_WIDTH, SCREEN_HEIGHT, NAME };
	client.SetUpTextRenderer(FONT_PATH, 28);
	StateStack stack;
	BlockState state(&client, 15, true, 0.35);

	stack.Push(&state);
	stack.Run();

	return 0;
}