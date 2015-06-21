#include "processors.h"

void menuProcessor    (struct Game* game)	
{
	struct PhObject body = game->menu.doodle.ph_body;
	
	SDL_RenderClear (game->sdl_data.renderer);
	SDL_ShowCursor (1);
	
	SDL_RenderCopy (game->sdl_data.renderer, game->menu.background_texture, NULL, NULL);
	updateMenuPhysics (game);
	
	drawObject  (game, convertToGlobal(body.cx, body.cy, body.rect), body.texture);
	drawObject  (game, game->menu.platform.rect, game->menu.platform.texture); 
	drawButtons (game, game->menu.btns, MENU_BTN_COUNT);

	processMenuInput (game);

	SDL_RenderPresent (game->sdl_data.renderer);
	SDL_Delay(10);
}
void worldProcessor   (struct Game* game)
{
	struct PhObject body = game->world.doodle.ph_body;

	SDL_RenderClear (game->sdl_data.renderer);
	SDL_ShowCursor (0);
	
	SDL_RenderCopy (game->sdl_data.renderer, game->world.background_texture, NULL, NULL);

	if (game->world.life == ALIFE)
	{
		updatePlatQueue (game);
		updateWorldPhysics (game);
		
		drawPlatQueue (game, game->world.plat_queue);
		drawObject (game, convertToCamera (game->world.camera.display_depth, convertToGlobal(body.cx, body.cy, body.rect)), body.texture);
		
		processWorldInput (game);

	} else {
		game->current_time = SDL_GetTicks ();
		drawObject (game, game->world.sign_game_over.rect, game->world.sign_game_over.texture);
		processGameOverInput (game);
	}

	SDL_RenderPresent (game->sdl_data.renderer);
	SDL_Delay(10);
}
void optionsProcessor (struct Game* game)
{
	SDL_RenderClear (game->sdl_data.renderer);
	processOptionsInput (game);
	SDL_RenderCopy (game->sdl_data.renderer, game->options.background_texture, NULL, NULL);
	
	drawButtons (game, game->options.btns, OPTIONS_BTN_COUNT);
	drawObject  (game, game->options.signs[OPTIONS_SIGN_MUSIC].rect, game->options.signs[OPTIONS_SIGN_MUSIC].texture);
	drawObject  (game, game->options.signs[OPTIONS_SIGN_SOUND].rect, game->options.signs[OPTIONS_SIGN_SOUND].texture);
	
	game->current_time = SDL_GetTicks();
	SDL_RenderPresent (game->sdl_data.renderer);
	SDL_Delay(10);
}
void helpProcessor    (struct Game* game)
{
	SDL_RenderClear (game->sdl_data.renderer);
	processHelpInput (game);
	SDL_RenderCopy (game->sdl_data.renderer, game->help.background_texture, NULL, NULL);
	
	drawButtons (game, game->help.btns, HELP_BTN_COUNT);
	
	game->current_time = SDL_GetTicks();
	SDL_RenderPresent (game->sdl_data.renderer);
	SDL_Delay(10);
}