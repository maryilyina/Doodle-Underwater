#ifndef ACTIONS_H_2014_05_08
#define ACTIONS_H_2014_05_08

#include "structs.h"
#include "initialisations.h"


void funcNewGame  (struct Game* game);
void funcMenu     (struct Game* game);
void funcScores   (struct Game* game);
void funcHelp     (struct Game* game);
void funcOptions  (struct Game* game);
void funcExit     (struct Game* game);
void funcMusicOn  (struct Game* game);
void funcMusicOff (struct Game* game);
void funcSoundOn  (struct Game* game);
void funcSoundOff (struct Game* game);

#endif