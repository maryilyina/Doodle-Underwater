#include "closure.h"

void close (struct Game* game)
{
	Mix_FreeMusic (game->menu.music );
	Mix_FreeMusic (game->world.music);
	Mix_FreeChunk (game->jump_sound );

	Mix_CloseAudio ( );
	SDL_DestroyRenderer (game->sdl_data.renderer);
	SDL_DestroyWindow   (game->sdl_data.window  );

	Mix_Quit ( );
    IMG_Quit ( );
	SDL_Quit ( );

}
