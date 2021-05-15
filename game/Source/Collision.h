#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Point.h"
#include "Map.h"
#include "Player.h"

class Collision
{
public:

	void CheckCollision(Map* map)
	{
		iPoint pos[4] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };
		
		// Collision detection: map vs player
		// Check if updated player position collides with next tile

		int doorLayer = map->properties.list.At(0)->data->value;
		//int interactLayer = map->properties.list.At(1)->data->value;
		int interactions = map->properties.list.At(1)->data->value;
		int wallLayer = map->properties.list.At(2)->data->value;
		
		if (player != NULL)
		{
			for (int i = 0; i < 4; i++)
			{
				pos[i] = map->WorldToMap(player->position.x + player->playerCollision[i].x, player->position.y + player->playerCollision[i].y);

				for (int y = 0; y < map->data.height; y++)
				{
					for (int x = 0; x < map->data.width; x++)
					{
						if (wallLayer != -1 && map->data.layers.At(wallLayer)->data->Get(pos[i].x, pos[i].y) != 0 &&
							Detect(map->GetTilemapRec(x, y), player->GetBounds()))
						{
							if (player->temPos.x != player->position.x) player->position.x = player->temPos.x;
							if (player->temPos.y != player->position.y) player->position.y = player->temPos.y;

							player->movingFlag = false;

							break;
						}

						if (doorLayer != -1 && map->data.layers.At(doorLayer)->data->Get(pos[i].x, pos[i].y) != 0 &&
							Detect(map->GetTilemapRec(x, y), player->GetBounds()))
						{
							if (player->temPos != player->position) player->position = player->temPos;
							player->movingFlag = false;
							map->doorHit = true;
							break;
						}

						if (interactions != -1)
						{
							ListItem<ObjectData*>* list;
							list = map->data.objLayers.At(0)->data->data.start;

							while (list != NULL)
							{
								iPoint tile = map->WorldToMap(list->data->rect.x, list->data->rect.y);
								iPoint tilePos = map->MapToWorld(tile.x, tile.y);

								SDL_Rect tileRect = { tilePos.x, tilePos.y, list->data->rect.w, list->data->rect.h };

								if (Detect(tileRect, player->GetBounds()))
								{
									currentInteraction.Clear();
									currentInteraction.operator=((const char*)list->data->properties.list.start->data->valueString.GetString());

									if (player->temPos != player->position)
									{
										player->position = player->temPos;
										player->movingFlag = false;
									}

									//interactRect = tileRect;
									interactRect = { tileRect.x - 10, tileRect.y - 10, tileRect.w + 20, tileRect.h + 20 };
								}

								list = list->next;
							}
						}

						if (currentInteraction.Length() != 0 && !Detect(interactRect, player->GetBounds()))  currentInteraction.Clear();

						/*else if (interactLayer != -1 && map->data.layers.At(interactLayer)->data->Get(pos[i].x, pos[i].y) != 0 &&
							Detect(map->GetTilemapRec(x, y), player->GetBounds()))
						{
							if (player->temPos.x != player->position.x) player->position.x = player->temPos.x;
							if (player->temPos.y != player->position.y) player->position.y = player->temPos.y;
							break;
						}*/
					}
				}
			}
		}
	}

	bool Detect(SDL_Rect rec1, SDL_Rect rec2)
	{
		if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
			(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
		else return false;
	}

	SDL_Rect interactRect = { 0, 0, 0, 0 };

	Player* player;

	SString currentInteraction = '/0';
};

#endif // __COLLISION_H__