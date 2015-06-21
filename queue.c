#include "queue.h"

float randomBetween (float min, float max)
{
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float ret = random * diff + min;
	
	assert (ret <= max);
	assert (ret >= min);
    
	return ret;
}

struct Queue* createQueue ( )
{
	struct Queue* queue = (struct Queue*) malloc (sizeof (struct Queue));
	assert (queue != NULL);

	queue->head = NULL;
	queue->tail = NULL;
	queue->length = 0;

	return queue;
}
int  initQueue       (struct Game* game)
{
	int i;
	int ret = 0;
	struct StatObject new_object;
	SDL_Surface* surface;
	float h1, h2;
	
	srand ( (unsigned) (time (NULL)));

	game->world.plat_queue = createQueue ();
	game->world.plat_queue->plat_w = 200;
	game->world.plat_queue->plat_h = 50;

	surface = IMG_Load("./images/platform.png");
	if (surface == NULL)
		ret = 1;
	game->world.plat_queue->texture = SDL_CreateTextureFromSurface (game->sdl_data.renderer, surface);
	SDL_FreeSurface (surface);

	h1 = SCREEN_H - 150.0;

	for (i = 0; i < PLAT_COUNT; i++)
	{
		new_object.texture = game->world.plat_queue->texture;
		new_object.rect.w = game->world.plat_queue->plat_w;
		new_object.rect.h = game->world.plat_queue->plat_h;
		
		if (i == 0)
		{
			new_object.rect.x = 1000.0;
			new_object.rect.y =  700.0;
		} else {
			h2 = h1 - (float) DISTANCE;
			new_object.rect.x = randomBetween (0.0, SCREEN_W - new_object.rect.w);
			new_object.rect.y = randomBetween (h2, h1);
			h1 = h2;
		}
		
		enqueue (game->world.plat_queue, new_object);
	}
	
	return ret;
}
void updatePlatQueue (struct Game* game)
{
	struct StatObject new_object;

	assert (game->world.plat_queue != NULL);
	assert (game->world.plat_queue->tail->next == NULL);

	if (game->world.plat_queue->tail->object.rect.y - game->world.camera.display_depth > SCREEN_H)
		dequeue (game->world.plat_queue);

	if (game->world.plat_queue->length < PLAT_COUNT)
	{	
		new_object.rect.w = game->world.plat_queue->plat_w;
		new_object.rect.h = game->world.plat_queue->plat_h;
		new_object.texture = game->world.plat_queue->texture;
		
		new_object.rect.x = randomBetween (0.0, SCREEN_W - new_object.rect.w);
		new_object.rect.y = randomBetween (game->world.plat_queue->head->object.rect.y - 2 * (float) DISTANCE, game->world.plat_queue->head->object.rect.y);
		
		enqueue (game->world.plat_queue, new_object);
	}
	
}
void enqueue         (struct Queue* queue, struct StatObject new_object)
{
	struct QElement* new_element = (struct QElement*) malloc (sizeof (struct QElement));
	assert (new_element != 0);

	if (queue->head == NULL)
	{
		queue->tail = new_element;
	}

	new_element->next = queue->head;
	new_element->object = new_object; 

	queue->head = new_element;
	queue->length ++;
}
void dequeue         (struct Queue* queue)
{
	struct QElement* cur = queue->head;

	if (queue->head != NULL)
		{
			cur = queue->head;
	
			while (cur->next != queue->tail)
				cur = cur->next;
				
			free (queue->tail);
			
			queue->tail = cur;
			queue->tail->next = NULL;
			queue->length --;
		}
}
void deleteQueue     (struct Queue* queue)
{
	struct  QElement* cur;
	struct  QElement* last;

	assert (queue != NULL);

	if (queue->head != NULL)
	{
		cur = queue->head;

		while( cur != NULL)
		{
			last = cur;
			cur = cur->next;
			free (last);
		}
	}
	
	free (queue);
}