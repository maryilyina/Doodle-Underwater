#ifndef PHYSICS_H_2014_05_08
#define PHYSICS_H_2014_05_08

#include "structs.h"

struct FRect convertToGlobal (float cx, float cy, struct FRect rect);
struct FRect convertToCamera (float camera_depth, struct FRect rect);

void calculateDoodlePhysics    (struct Game* game, struct PhObject* body);
void checkDoodleIsOnPlatform   (struct Game* game, struct PhObject* body, struct StatObject platform);
void checkDoodleScreenPosition (struct Game* game, struct PhObject* body);
void checkCameraPosition       (struct PhObject body, struct Camera* camera);

void updateMenuPhysics  (struct Game* game);
void updateWorldPhysics (struct Game* game);

#endif