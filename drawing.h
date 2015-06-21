#ifndef DRAWING_H_2014_05_08
#define DRAWING_H_2014_05_08

#include "structs.h"
#include "physics.h"

void drawButtons (struct Game* game, struct Button btns[], int btns_count);
void drawObject  (struct Game* game, struct FRect rect, SDL_Texture* texture);
void drawPlatQueue (struct Game* game, struct Queue* queue);

#endif
