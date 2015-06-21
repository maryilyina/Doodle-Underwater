#include "processors.h"

int main ( )
{	
	int main_ret = 0;
	struct Game game;

	assert (initResources (&game) == 0);
	SDL_Log ("All game resources initialised\n`");

	while (!game.should_exit)
	{
		game.game_state_processors [game.game_state] (&game);
	}

	close (&game);
	return 0;
}
