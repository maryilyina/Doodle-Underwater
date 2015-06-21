#ifndef QUEUE_H_2014_05_08
#define QUEUE_H_2014_05_08

#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "physics.h"

float randomBetween (float min, float max);
struct Queue* createQueue ( );
int  initQueue       (struct Game* game);
void updatePlatQueue (struct Game* game);
void enqueue         (struct Queue* queue, struct StatObject new_object);
void dequeue         (struct Queue* queue);
void deleteQueue     (struct Queue* queue);

#endif