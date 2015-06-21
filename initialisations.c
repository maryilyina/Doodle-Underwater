#include "initialisations.h"

int initStatObject (struct Game* game, struct StatObject* object, struct FRect rect, char* file)
{
	SDL_Surface* surface;
	int ret = 0;
	surface = IMG_Load (file);
	if (surface == NULL)
		ret = 1;
	object->texture = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surface);
	SDL_FreeSurface (surface);

	object->rect = rect;

	return ret;
}
int initPhObject   (struct PhObject* object,  float cx, float cy, struct FRect rect, float vx, float vy, SDL_Texture *texture)
{
	int ret = 0;

	object->cx = cx;
	object->cy = cy;
	object->vx = vx;
	object->vy = vy;
	object->rect = rect;
	object->texture = texture;

	if (object->texture == NULL)
		ret = 1;

	return ret;
}
int initDoodle     (struct Game* game, struct Doodle* doodle, float cx, float cy, struct FRect rect, float vx, float vy, char* files[], int visible_state)
{
	int i;
	int ret = 0;
	SDL_Surface* surfaces[2];
	doodle->visible_state = visible_state;
	
	for (i = 0; i < DOODLE_STATES_COUNT; i++)
	{
		surfaces[i] = IMG_Load (files[i]);
		if (surfaces[i] == NULL)
			ret = 1;

		doodle->textures[i] = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surfaces[i]);
		SDL_FreeSurface (surfaces[i]);
	}

	initPhObject (&(doodle->ph_body), cx, cy, rect, vx, vy, doodle->textures[visible_state]);
	return ret;
	
}
int initButton     (struct Game* game, struct Button* t_btn, struct FRect rect, void (*action) (struct Game*), char* files[])
{
	int i;
	int ret = 0;
	SDL_Surface* surfaces[BTN_STATES_COUNT];

	t_btn->action = action;
	t_btn->visible_state = BTN_STATE_NORMAL;

	t_btn->display_rect = rect;

	t_btn->rects[BTN_STATE_NORMAL ] = rect;

	t_btn->rects[BTN_STATE_HOVER  ] = rect;
	t_btn->rects[BTN_STATE_HOVER  ].x -= 0.05f * rect.w;
	t_btn->rects[BTN_STATE_HOVER  ].w += 0.10f * rect.w;
	t_btn->rects[BTN_STATE_HOVER  ].y -= 0.05f * rect.h;
	t_btn->rects[BTN_STATE_HOVER  ].h += 0.10f * rect.h;

	t_btn->rects[BTN_STATE_CLICKED] = rect;
	t_btn->rects[BTN_STATE_CLICKED].x -= 0.04f * rect.w;
	t_btn->rects[BTN_STATE_CLICKED].w += 0.08f * rect.w;
	t_btn->rects[BTN_STATE_CLICKED].y -= 0.04f * rect.h;
	t_btn->rects[BTN_STATE_CLICKED].h += 0.08f * rect.h;
	
	for (i = 0; i < BTN_STATES_COUNT; i++)
	{
		surfaces[i] = IMG_Load (files[i]);
		if (surfaces[i] == NULL)
			ret = 1;

		t_btn->textures[i] = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surfaces[i]);
		SDL_FreeSurface (surfaces[i]);
	}
	return ret;
}

int initMenuResources    (struct Game* game)
{
	int ret = 0;
	struct FRect rect;
	float cx, cy;
	SDL_Surface* surface;
	char* doodle_files[DOODLE_STATES_COUNT];
	char* btn_files[BTN_STATES_COUNT];

	game->menu.music = Mix_LoadMUS ("./music/menu_music.mp3");
	if (game->menu.music == NULL)
		ret = 1;
	
	surface = IMG_Load ("./images/background_menu.png");
	if (surface == NULL)
		ret = 1;
	game->menu.background_texture = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surface);
	SDL_FreeSurface (surface);


	rect.x = 1000.0;
	rect.y =  700.0;
	rect.w =  200.0;
	rect.h =   50.0;
	if (initStatObject (game, &(game->menu.platform), rect, "./images/platform.png") != 0)
		ret = 1;
	

	doodle_files[LEFT ] = "./images/doodle_left.png";
	doodle_files[RIGHT] = "./images/doodle_right.png";
	cx = rect.x + rect.w / 2;
	cy = rect.y - DOODLE_H / 2;
	rect.x = -DOODLE_W / 2;
	rect.y = -DOODLE_H / 2;
	rect.w =  DOODLE_W;
	rect.h =  DOODLE_H;
	if (initDoodle (game, &(game->menu.doodle), cx, cy, rect, 0.0, 0.0, doodle_files, LEFT) != 0)
		ret = 1;
	
	
	
	btn_files[BTN_STATE_NORMAL ] = "./images/but_0_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_0_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_0_2.png";
	rect.x = 350;
	rect.y = 250;
	rect.h = 100;
	rect.w = 400;
	if (initButton (game, &(game->menu.btns[MENU_BTN_NEW_GAME]), rect, funcNewGame, btn_files) != 0)
		ret = 1;
	
	btn_files[BTN_STATE_NORMAL ] = "./images/but_1_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_1_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_1_2.png";
	rect.y += 120;
	if (initButton (game, &(game->menu.btns[MENU_BTN_SCORES  ]), rect, funcScores,  btn_files) != 0)
		ret = 1;

	btn_files[BTN_STATE_NORMAL ] = "./images/but_2_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_2_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_2_2.png";
	rect.y += 120;
	if (initButton (game, &(game->menu.btns[MENU_BTN_OPTIONS ]), rect, funcOptions, btn_files) != 0)
		ret = 1;

	btn_files[BTN_STATE_NORMAL ] = "./images/but_3_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_3_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_3_2.png";
	rect.y += 120;
	if (initButton (game, &(game->menu.btns[MENU_BTN_EXIT    ]), rect, funcExit,    btn_files) != 0)
		ret = 1;

	btn_files[BTN_STATE_NORMAL ] = "./images/but_4_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_4_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_4_2.png";
	rect.h = 100;
	rect.w = 100;
	rect.x = SCREEN_W - rect.w - 50;
	rect.y = 50;
	if (initButton (game, &(game->menu.btns[MENU_BTN_HELP    ]), rect, funcHelp,    btn_files) != 0)
		ret = 1;

	return ret;
}
int initWorldResources   (struct Game* game)
{
	int ret = 0;
	struct FRect rect;
	float cx, cy;
	SDL_Surface* surface;
	char* doodle_files[DOODLE_STATES_COUNT];

	game->world.camera.depth = 0.0;
	game->world.camera.display_depth = 0.0;
	game->world.life = ALIFE;

	game->world.plat_queue = NULL;

	game->world.music  = Mix_LoadMUS ("./music/world_music.mp3");
	if (game->world.music == NULL)
		ret = 1;
	
	surface  = IMG_Load ("./images/background_world.png");
	if (surface == NULL)
		ret = 1;

	game->world.background_texture  = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surface);
	SDL_FreeSurface (surface);


	doodle_files[LEFT ] = "./images/doodle_left.png";
	doodle_files[RIGHT] = "./images/doodle_right.png";
	cx = 1000.0 + 200.0 / 2;
	cy = 700.0 - DOODLE_H / 2;
	rect.x = -DOODLE_W / 2;
	rect.y = -DOODLE_H / 2;
	rect.w =  DOODLE_W;
	rect.h =  DOODLE_H;
	if (initDoodle (game, &(game->world.doodle), cx, cy, rect, 0.0, 0.0, doodle_files, LEFT) != 0)
		ret = 1;

	rect.w = 800.0;
	rect.h = 500.0;
	rect.x = (SCREEN_W - rect.w) / 2;
	rect.y = (SCREEN_H - rect.h) / 2;
	if (initStatObject (game, &(game->world.sign_game_over), rect, "./images/sign_game_over.png") != 0)
		ret = 1;

	return ret;
}
int initOptionsResources (struct Game* game)
{
	int ret = 0;
	struct FRect rect;
	SDL_Surface* surface;
	char* btn_files[BTN_STATES_COUNT];
	
	surface = IMG_Load ("./images/background_options.png");
	if (surface == NULL)
		ret = 1;
	game->options.background_texture = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surface);
	SDL_FreeSurface (surface);

	rect.w = 850;
	rect.h = 100;
	rect.x = (SCREEN_W - rect.w) / 2;
	rect.y = 200;
	
	if (initStatObject (game, &(game->options.signs[OPTIONS_SIGN_MUSIC]), rect, "./images/sign_music.png") != 0)
		ret = 1;

	btn_files[BTN_STATE_NORMAL ] = "./images/but_on_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_on_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_on_2.png";
	rect.y += 50 + rect.h;
	rect.w = 400;
	if (initButton (game, &(game->options.btns[OPTIONS_BTN_MUSIC_ON]), rect, funcMusicOn, btn_files) != 0)
		ret = 1;

	btn_files[BTN_STATE_NORMAL ] = "./images/but_off_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_off_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_off_2.png";
	rect.x += 50 + rect.w;
	if (initButton (game, &(game->options.btns[OPTIONS_BTN_MUSIC_OFF]), rect, funcMusicOff, btn_files) != 0)
		ret = 1;
	
	rect.x -= 50 + rect.w;
	rect.y += 50 + rect.h;
	rect.w = 850;
	if (initStatObject (game, &(game->options.signs[OPTIONS_SIGN_SOUND]), rect, "./images/sign_sounds.png") != 0)
		ret = 1;
	
	btn_files[BTN_STATE_NORMAL ] = "./images/but_on_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_on_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_on_2.png";
	rect.y += 50 + rect.h;
	rect.w = 400;
	if (initButton (game, &(game->options.btns[OPTIONS_BTN_SOUND_ON]), rect, funcSoundOn, btn_files) != 0)
		ret = 1;
	
	btn_files[BTN_STATE_NORMAL ] = "./images/but_off_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_off_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_off_2.png";
	rect.x += 50 + rect.w;
	if (initButton (game, &(game->options.btns[OPTIONS_BTN_SOUND_OFF]), rect, funcSoundOff, btn_files) != 0)
		ret = 1;

	return ret;
}
int initHelpResources    (struct Game* game)
{
	int ret = 0;
	struct FRect rect;
	SDL_Surface* surface;
	char* btn_files[BTN_STATES_COUNT];

	surface = IMG_Load ("./images/background_help.png");
	if (surface == NULL)
		ret = 1;
	game->help.background_texture = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surface);
	SDL_FreeSurface (surface);

	btn_files[BTN_STATE_NORMAL ] = "./images/but_ok_0.png";
	btn_files[BTN_STATE_HOVER  ] = "./images/but_ok_1.png";
	btn_files[BTN_STATE_CLICKED] = "./images/but_ok_2.png";
	rect.h = 100;
	rect.w = 400;
	rect.x = SCREEN_W - rect.w - 200;
	rect.y = SCREEN_H - rect.h - 50;
	if (initButton (game, &(game->help.btns[HELP_BTN_OK]), rect, funcMenu, btn_files) != 0)
		ret = 1;

	return ret;
}
int initResources        (struct Game* game)
{
	int ret = 0;

	if (SDL_Init (SDL_INIT_EVERYTHING) != 0)
	{
		ret = 1;
		SDL_Log("ERROR: Could not initialise SDL");
	} else
		SDL_Log("SDL initialised");

	if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		ret = 1;
		SDL_Log ("ERROR: Could not initialise Audio");
	} else
		SDL_Log ("Audio initialised");
	
	game->jump_sound   = Mix_LoadWAV ("./music/jump_sound.wav");
	if (game->jump_sound == NULL)
		ret = 1;
	game->flight_sound = Mix_LoadWAV ("./music/flight_sound.wav");
	if (game->flight_sound == NULL)
		ret = 1;

	game->game_state = MENU;
	game->game_state_processors[MENU]    = &menuProcessor;
	game->game_state_processors[WORLD]   = &worldProcessor;
	game->game_state_processors[OPTIONS] = &optionsProcessor;
	game->game_state_processors[HELP]    = &helpProcessor;

	game->should_exit = 0;
	game->music_state = ON;
	game->sound_state = ON;
	
	game->sdl_data.window = SDL_CreateWindow ("Doodle Underwater", 0, 0, (int) (SCREEN_W), (int) (SCREEN_H), SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (game->sdl_data.window == NULL)
		SDL_Log ("ERROR: Could not create a window");
	
	game->sdl_data.renderer = SDL_CreateRenderer (game->sdl_data.window, -1, 0);
	if (game->sdl_data.renderer == NULL)
		SDL_Log ("ERROR: Could not create a renderer");

	if (initMenuResources (game) != 0)
	{
		ret = 1;
		SDL_Log ("ERROR: Could not initialise menu resources");
	} else
		SDL_Log("Menu resources initialised");

	if (initWorldResources (game) != 0)
	{
		ret = 1;
		SDL_Log ("ERROR: Could not initialise world resources");
	} else
		SDL_Log("World resources initialised");

	if (initOptionsResources (game) != 0)
	{
		ret = 1;
		SDL_Log ("ERROR: Could not initialise options resources");
	} else
		SDL_Log("Options resources initialised");

	if (initHelpResources (game) != 0)
	{
		ret = 1;
		SDL_Log ("ERROR: Could not initialise help resources");
	} else
		SDL_Log("Help resources initialised");

	game->current_time = SDL_GetTicks ();
	Mix_PlayMusic (game->menu.music, -1);

	return ret;
}