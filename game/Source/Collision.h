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
		
		for (int i = 0; i < 4; i++)
		{
			pos[i] = map->WorldToMap(player->position.x + player->playerCollision[i].x, player->position.y + player->playerCollision[i].y);

			for (int y = 0; y < map->data.height; y++)
			{
				for (int x = 0; x < map->data.width; x++)
				{
					if (map->data.layers.At(map->properties.list.At(1)->data->value)->data->Get(pos[i].x, pos[i].y) != 0 &&
						Detect(map->GetTilemapRec(x, y), player->GetBounds()))
					{
						if (player->temPos.x != player->position.x) player->position.x = player->temPos.x;
						if (player->temPos.y != player->position.y) player->position.y = player->temPos.y;
						break;
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

	Player* player = nullptr;
};

#endif // __COLLISION_H__