#include "physics.h"

struct FRect convertToGlobal (float cx, float cy, struct FRect rect)
{
	struct FRect global_rect;

	global_rect.x = rect.x + cx;
	global_rect.y = rect.y + cy;
	global_rect.w = rect.w;
	global_rect.h = rect.h;

	return global_rect;
}
struct FRect convertToCamera (float camera_depth, struct FRect rect)
{
	struct FRect cam_rect;

	cam_rect.x = rect.x;
	cam_rect.y = rect.y - camera_depth;
	cam_rect.w = rect.w;
	cam_rect.h = rect.h;
	return cam_rect;
}

void calculateDoodlePhysics    (struct Game* game, struct PhObject* body)
{
	unsigned int new_current_time = SDL_GetTicks();
	double dt = (((double)(new_current_time - game->current_time)) / 1000.0 );
	assert (dt > 0.0);
	game->current_time = new_current_time;

	body->vy += (float) (GRAVITY * dt);
	body->vy -= (float) (body->vy * RESISTANCE * dt);
	
	if (body->vx != 0.0)
		body->vx -= (float) (body->vx * RESISTANCE * dt);

	if (body->vx >= MAX_X_SPEED)
		body->vx  = MAX_X_SPEED;

	if (body->vx <= - MAX_X_SPEED)
		body->vx  = - MAX_X_SPEED;

	if (body->vy <= MAX_Y_SPEED)
		body->vy  = MAX_Y_SPEED;

	body->cy += (float) (body->vy * dt);
	body->cx += (float) (body->vx * dt);
}
void checkDoodleIsOnPlatform   (struct Game* game, struct PhObject* body, struct StatObject platform)
{
	struct FRect glob_doodle_rect = convertToGlobal (body->cx, body->cy, body->rect);
	
	if ( (glob_doodle_rect.y >= platform.rect.y - DOODLE_H) && (glob_doodle_rect.y <= platform.rect.y - 50.0) && (glob_doodle_rect.x >= platform.rect.x - 80.0) && (glob_doodle_rect.x <= platform.rect.x + platform.rect.w - DOODLE_W + 80.0) && (body->vy >= 0 ) )
	{
		if (game->sound_state == ON)
			Mix_PlayChannel ( -1, game->jump_sound, 0);
		body->vy = Y_SPEED;
	}

}
void checkDoodleScreenPosition (struct Game* game, struct PhObject* body)
{
	int i;
	struct FRect glob_doodle_rect = convertToGlobal (body->cx, body->cy, body->rect);
	struct QElement* cur = game->world.plat_queue->head;
	
	assert (cur != NULL);

	if (glob_doodle_rect.x >= SCREEN_W)
		body->cx = - DOODLE_W / 2;

	if (glob_doodle_rect.x < -DOODLE_W)
		body->cx = SCREEN_W + DOODLE_W / 2;

	for (i = 0; i < game->world.plat_queue->length; i++)
	{	
		checkDoodleIsOnPlatform (game, body, cur->object);
		cur = cur->next;
	}
	
	cur = game->world.plat_queue->tail;

	if (glob_doodle_rect.y > cur->object.rect.y - 90.0)
	{
		if (glob_doodle_rect.y > cur->object.rect.y + 400.0)
		{
			game->world.life = DEAD;
			SDL_Log ("The game is over");
		}
		else if (game->sound_state == ON)
			Mix_PlayChannel ( -1, game->flight_sound, 0);
	}

}
void checkCameraPosition       (struct PhObject body, struct Camera* camera)
{
	float speed = 0.05;
	struct FRect glob_doodle_rect = convertToGlobal (body.cx, body.cy, body.rect);
	struct FRect cam_rect = convertToCamera (camera->display_depth, glob_doodle_rect);
	
	if (cam_rect.y < SCREEN_H / 4)
		camera->depth -= SCREEN_H / 100;

	if (cam_rect.y > 3 * SCREEN_H / 4)
		camera->depth += SCREEN_H / 100;

	camera->display_depth += (camera->depth - camera->display_depth) * speed;

}

void updateMenuPhysics  (struct Game* game)
{
	checkDoodleIsOnPlatform (game, &(game->menu.doodle.ph_body), game->menu.platform);
	calculateDoodlePhysics (game, &(game->menu.doodle.ph_body));
}
void updateWorldPhysics (struct Game* game)
{
	checkDoodleScreenPosition  (game, &(game->world.doodle.ph_body));
	calculateDoodlePhysics (game, &(game->world.doodle.ph_body));
	checkCameraPosition (game->world.doodle.ph_body, &(game->world.camera));
}