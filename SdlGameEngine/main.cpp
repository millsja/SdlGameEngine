#include "sdlClient.h"
#include "utilities.h"
#include "stateStack.h"
#include "blockState.h"
#include "SDL.h"
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	SdlClient client = { SCREEN_WIDTH, SCREEN_HEIGHT };
	StateStack stack;
	// GeometryState state(&client);
	// KeyTutorialGameState state(&client);
	BlockState state(&client);

	stack.Push(&state);
	stack.Run();

	return 0;
}