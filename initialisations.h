#ifndef INITIALISATIONS_H_2014_05_08
#define INITIALISATIONS_H_2014_05_08

#include "structs.h"
#include "processors.h"
#include "queue.h"

int initStatObject (struct Game* game, struct StatObject* object, struct FRect rect, char* file);
int initPhObject   (struct PhObject* object,  float cx, float cy, struct FRect rect, float vx, float vy, SDL_Texture *texture);
int initDoodle     (struct Game* game, struct Doodle* doodle, float cx, float cy, struct FRect rect, float vx, float vy, char* files[], int visible_state);
int initButton     (struct Game* game, struct Button* t_btn, struct FRect rect, void (*action) (struct Game*), char* files []);

int initMenuResources    (struct Game* game);
int initWorldResources   (struct Game* game);
int initOptionsResources (struct Game* game);
int initHelpResources    (struct Game* game);
int initResources        (struct Game* game);

#endif