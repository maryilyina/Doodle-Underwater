#include "input_process.h"

void handleMouse          (struct Game* game, SDL_Event event, struct Button btns [], int btns_count)
{
	struct Button* t_btn_p;
	struct FRect t_rect;
	int i;

	if (event.type==SDL_MOUSEMOTION || event.type==SDL_MOUSEBUTTONUP)
			{
				int mx = event.motion.x;
				int my = event.motion.y;
				
				
				for (i = 0; i < btns_count; i++)
				{
					t_btn_p = &(btns[i]);
					t_rect = t_btn_p->rects[t_btn_p->visible_state];
					t_btn_p->visible_state = BTN_STATE_NORMAL;
					
					if (mx > t_rect.x    &&    mx < t_rect.x + t_rect.w    &&
						my > t_rect.y    &&    my < t_rect.y + t_rect.h)
					{
						t_btn_p->visible_state = BTN_STATE_HOVER;
					}
				}
			}

			if (event.type==SDL_MOUSEBUTTONDOWN)
			{
				int mx = event.motion.x;
				int my = event.motion.y;
				for (i = 0; i < btns_count; i++)
				{
					t_btn_p = &(btns[i]);
					t_btn_p->visible_state = BTN_STATE_NORMAL;
					t_rect = t_btn_p->rects[t_btn_p->visible_state];

					if (mx > t_rect.x    &&    mx < t_rect.x + t_rect.w    &&
						my > t_rect.y    &&    my < t_rect.y + t_rect.h)
					{
						t_btn_p->visible_state = BTN_STATE_CLICKED;
						t_btn_p->action(game);
					}
				}
			}

}
void handleWorldKey       (struct Game* game, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					if (game->world.doodle.visible_state == LEFT)
						game->world.doodle.ph_body.vx = 0;
					game->world.doodle.ph_body.vx += X_SPEED;
					game->world.doodle.visible_state = RIGHT;
					game->world.doodle.ph_body.texture = game->world.doodle.textures[game->world.doodle.visible_state];
					break;

				case SDLK_LEFT:
					if (game->world.doodle.visible_state == RIGHT)
						game->world.doodle.ph_body.vx = 0;
					game->world.doodle.ph_body.vx -= X_SPEED;
					game->world.doodle.visible_state = LEFT;
					game->world.doodle.ph_body.texture = game->world.doodle.textures[game->world.doodle.visible_state];
					break;
				
				case SDLK_ESCAPE:
					if (game->music_state == ON)
						Mix_PlayMusic (game->menu.music, -1);
					funcMenu (game);
					break;

				default:
					break;
				}
			}

}

void processMenuInput     (struct Game* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) 
		{
			if (event.type==SDL_QUIT)
			{
				funcExit (game);
			}
			
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					funcExit (game);
			}

			handleMouse (game, event, game->menu.btns, MENU_BTN_COUNT);
		}
}
void processWorldInput    (struct Game* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) 
	{
		handleWorldKey (game, event);
	}
}
void processOptionsInput  (struct Game* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					funcMenu (game);
			}

			handleMouse (game, event, game->options.btns, OPTIONS_BTN_COUNT);
			
			if (game->music_state == ON)
				game->options.btns[OPTIONS_BTN_MUSIC_ON].visible_state = BTN_STATE_HOVER;
			if (game->music_state == OFF)
				game->options.btns[OPTIONS_BTN_MUSIC_OFF].visible_state = BTN_STATE_HOVER;
			if (game->sound_state == ON)
				game->options.btns[OPTIONS_BTN_SOUND_ON].visible_state = BTN_STATE_HOVER;
			if (game->sound_state == OFF)
				game->options.btns[OPTIONS_BTN_SOUND_OFF].visible_state = BTN_STATE_HOVER;
		}
}
void processHelpInput     (struct Game* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					funcMenu (game);
			}

			handleMouse (game, event, game->help.btns, HELP_BTN_COUNT);
		}
}
void processGameOverInput (struct Game* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RETURN:
					game->world.life = ALIFE;
					funcNewGame (game);
					break;

				case SDLK_ESCAPE:
					if (game->music_state == ON)
						Mix_PlayMusic (game->menu.music, -1);
					funcMenu (game);
					break;

				default:
					break;
				}
			}

	}
}