#ifndef INPUT_PROCESS_H_2014_05_08
#define INPUT_PROCESS_H_2014_05_08

#include "actions.h"

void handleMouse          (struct Game* game, SDL_Event event, struct Button btns [], int btns_count);
void handleWorldKey       (struct Game* game, SDL_Event event);

void processMenuInput     (struct Game* game);
void processWorldInput    (struct Game* game);
void processOptionsInput  (struct Game* game);
void processHelpInput     (struct Game* game);
void processGameOverInput (struct Game* game);

#endif