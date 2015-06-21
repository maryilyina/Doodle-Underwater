#include "drawing.h"

void drawButtons   (struct Game* game, struct Button btns[], int btns_count)
{
	int i;
	struct Button* t_btn_p;
	struct FRect t_rect;
	SDL_Rect int_rect;

	for (i = 0; i < btns_count; i++)
	{
		t_btn_p = &(btns[i]);

		t_btn_p->display_rect.x += (t_btn_p->rects[t_btn_p->visible_state].x - t_btn_p->display_rect.x) * BTN_SPEED;
		t_btn_p->display_rect.y += (t_btn_p->rects[t_btn_p->visible_state].y - t_btn_p->display_rect.y) * BTN_SPEED;
		t_btn_p->display_rect.h += (t_btn_p->rects[t_btn_p->visible_state].h - t_btn_p->display_rect.h) * BTN_SPEED;
		t_btn_p->display_rect.w += (t_btn_p->rects[t_btn_p->visible_state].w - t_btn_p->display_rect.w) * BTN_SPEED;

		t_rect.x = t_btn_p->display_rect.x;
		t_rect.y = t_btn_p->display_rect.y;
		t_rect.h = t_btn_p->display_rect.h;
		t_rect.w = t_btn_p->display_rect.w;

		int_rect.x = (int)(t_rect.x);
		int_rect.y = (int)(t_rect.y);
		int_rect.w = (int)(t_rect.w);
		int_rect.h = (int)(t_rect.h);
		SDL_RenderCopy (game->sdl_data.renderer, t_btn_p->textures[t_btn_p->visible_state], NULL, &(int_rect));
	}
}
void drawObject    (struct Game* game, struct FRect rect, SDL_Texture* texture)
{
	SDL_Rect t_rect;

	t_rect.x = (int) (rect.x);
	t_rect.y = (int) (rect.y);
	t_rect.w = (int) (rect.w);
	t_rect.h = (int) (rect.h);

	assert (texture != NULL);
	
	SDL_RenderCopy (game->sdl_data.renderer, texture, NULL, &(t_rect));
}
void drawPlatQueue (struct Game* game, struct Queue* queue)
{
	struct  QElement* cur;

	cur = queue->head;

	while (cur != NULL)
	{
		drawObject (game, convertToCamera (game->world.camera.display_depth, cur->object.rect) , cur->object.texture);
		cur = cur->next;
	}
}
