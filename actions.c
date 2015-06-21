#include "actions.h"

void funcNewGame   (struct Game* game)
{
	struct PhObject* body = &(game->world.doodle.ph_body);

	game->game_state = WORLD;

	if (game->music_state == ON)
		Mix_PlayMusic (game->world.music, -1);
	
	game->world.life = ALIFE;
	game->world.camera.depth = 0.0;
	game->world.camera.display_depth = 0.0;

	game->world.doodle.visible_state = LEFT;
	body->texture = game->world.doodle.textures[game->world.doodle.visible_state];
	body->vx = 0.0;
	body->vy = 0.0;
	body->cx = 1000.0 + 200.0 / 2;
	body->cy = 700.0 - DOODLE_H / 2;
	body->rect.x = -DOODLE_W / 2;
	body->rect.y = -DOODLE_H / 2;
	body->rect.w =  DOODLE_W;
	body->rect.h =  DOODLE_H;

	if (game->world.plat_queue != NULL)
		deleteQueue (game->world.plat_queue);

	initQueue (game);

	SDL_Log ("User started New game");
}
void funcMenu      (struct Game* game)
{
	struct PhObject* body = &(game->menu.doodle.ph_body);
	int i;

	game->game_state = MENU;
	
	for (i = 0; i < MENU_BTN_COUNT; i++)
		game->menu.btns[i].visible_state = BTN_STATE_NORMAL;
	
	game->world.doodle.visible_state = LEFT;
	body->texture = game->menu.doodle.textures[game->world.doodle.visible_state];
	body->vx = 0.0;
	body->vy = 0.0;
	body->cx = game->menu.platform.rect.x + game->menu.platform.rect.w / 2;
	body->cy = game->menu.platform.rect.y - DOODLE_H / 2;
	body->rect.x = -DOODLE_W / 2;
	body->rect.y = -DOODLE_H / 2;
	body->rect.w =  DOODLE_W;
	body->rect.h =  DOODLE_H;

	SDL_Log ("User went to Menu");
}
void funcScores    (struct Game* game)
{
	game->should_exit = 0;
}
void funcHelp      (struct Game* game)
{
	int i;
	game->game_state = HELP;
	for (i = 0; i < HELP_BTN_COUNT; i++)
		game->help.btns[i].visible_state = BTN_STATE_NORMAL;
	SDL_Log ("User went to Help");
}
void funcOptions   (struct Game* game)
{
	int i;
	game->game_state = OPTIONS;
	for (i = 0; i < OPTIONS_BTN_COUNT; i++)
		game->options.btns[i].visible_state = BTN_STATE_NORMAL;
	SDL_Log ("User went to Options");
}
void funcExit      (struct Game* game)
{
	game->should_exit = 1;
	SDL_Log ("User exited");
}

void funcMusicOn   (struct Game* game)
{
	if (game->music_state == OFF)
	{
		Mix_PlayMusic (game->menu.music, -1);
		game->music_state = ON;
		SDL_Log ("User changed the settings. Music is ON");
	}
}
void funcMusicOff  (struct Game* game)
{
	if (game->music_state == ON)
	{
		game->music_state = OFF;
		Mix_HaltMusic ( );
		SDL_Log ("User changed the settings. Music is OFF");
	}
}
void funcSoundOn   (struct Game* game)
{
	if (game->sound_state == OFF)
	{
		game->sound_state = ON;
		SDL_Log ("User changed the settings. Sound is ON");
	}

}
void funcSoundOff  (struct Game* game)
{
	if (game->sound_state == ON)
	{
		game->sound_state = OFF;
		SDL_Log ("User changed the settings. Sound is OFF");
	}
}
