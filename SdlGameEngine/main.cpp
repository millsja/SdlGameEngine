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

int main( int argc, char* args[] )
{
	SdlClient client = { SCREEN_WIDTH, SCREEN_HEIGHT, NAME };
	StateStack stack;
	BlockState state(&client);

	stack.Push(&state);
	stack.Run();

	return 0;
}