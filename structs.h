#ifndef STRUCTS_H_2014_05_08
#define STRUCTS_H_2014_05_08

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <assert.h>

/*screen definitions*/

#define SCREEN_W        1366
#define SCREEN_H         768

struct SDL_Data
{
	SDL_Window *window;
	SDL_Renderer *renderer;
};
struct Camera
{
	float depth;
	float display_depth;
};



/*physical definitions*/

#define GRAVITY        1500.0
#define RESISTANCE        0,3
#define Y_SPEED       -1000.0
#define X_SPEED         150.0
#define MAX_X_SPEED     400.0
#define MAX_Y_SPEED   -1200.0



/*objects definitions*/

struct FRect
{
	float x;
	float y;
	float h;
	float w;
};
struct StatObject
{
	struct FRect rect;
	SDL_Texture *texture;
}; 

struct PhObject
{	
	struct FRect rect;
	float vx;
	float vy;
	float cx;
	float cy;
	SDL_Texture *texture;
};

#define DOODLE_STATES_COUNT  2

#define LEFT                 0
#define RIGHT                1

#define DOODLE_W           150.0
#define DOODLE_H           100.0

struct Doodle
{
	int visible_state;
	struct PhObject ph_body;
	SDL_Texture *textures[DOODLE_STATES_COUNT];
};



/*button definitions*/

#define BTN_SPEED            0.1

#define BTN_STATES_COUNT     3

#define BTN_STATE_NORMAL     0
#define BTN_STATE_HOVER      1
#define BTN_STATE_CLICKED    2

struct Game;
struct Button
{
	int visible_state;
	void (*action) (struct Game* game);
	struct FRect display_rect;
	struct FRect rects[BTN_STATES_COUNT];
	SDL_Texture *textures[BTN_STATES_COUNT];
};


#define MENU_BTN_COUNT        5

#define MENU_BTN_NEW_GAME     0
#define MENU_BTN_SCORES       1
#define MENU_BTN_OPTIONS      2
#define MENU_BTN_EXIT         3
#define MENU_BTN_HELP         4

#define OPTIONS_BTN_COUNT     4

#define OPTIONS_BTN_MUSIC_ON  0
#define OPTIONS_BTN_MUSIC_OFF 1
#define OPTIONS_BTN_SOUND_ON  2
#define OPTIONS_BTN_SOUND_OFF 3

#define ON                    0
#define OFF                   1

#define OPTIONS_SIGN_COUNT    2

#define OPTIONS_SIGN_MUSIC    0
#define OPTIONS_SIGN_SOUND    1

#define HELP_BTN_COUNT        1
#define HELP_BTN_OK           0





/*queue definitions*/

#define PLAT_COUNT           20
#define DISTANCE            120.0
struct QElement
{
	struct StatObject object;
	struct QElement* next;
};
struct Queue
{
	struct QElement* head;
	struct QElement* tail;
	int length;
	float plat_w;
	float plat_h;
	SDL_Texture *texture;
};




/*game definitions*/

#define ALIFE                0
#define DEAD                 1

#define GAME_STATES_COUNT    5

#define MENU                 0
#define WORLD                1
#define OPTIONS              2
#define HELP                 3
#define SCORES               4

struct Menu
{
	struct Button btns[MENU_BTN_COUNT];
	struct StatObject platform;
	struct Doodle doodle;

	SDL_Texture *background_texture;
	Mix_Music* music;
};
struct World
{
	struct Doodle doodle;
	struct Queue* plat_queue;
	struct StatObject sign_game_over;

	struct Camera camera;
	int life;

	SDL_Texture *background_texture;
	Mix_Music* music;
};
struct Options
{
	struct Button     btns[OPTIONS_BTN_COUNT];
	struct StatObject signs[OPTIONS_SIGN_COUNT];
	SDL_Texture *background_texture;
};
struct Help
{
	struct Button btns[HELP_BTN_COUNT];
	SDL_Texture *background_texture;
};
struct Game
{
	int should_exit;
	int game_state;
	int music_state;
	int sound_state;

	unsigned int current_time;
	struct SDL_Data sdl_data;
	void (*game_state_processors[GAME_STATES_COUNT]) (struct Game* game);
	
	struct Menu menu;
	struct World world;
	struct Options options;
	struct Help help;
	
	Mix_Chunk* jump_sound;
	Mix_Chunk* flight_sound;
};

#endif