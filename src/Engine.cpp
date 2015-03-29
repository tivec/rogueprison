#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Engine::Engine() : fovRadius(10), computeFov(true)
{
	TCODConsole::initRoot(80,50, "libtcod C++ tutorial", false);
	TCODConsole::root->setKeyboardRepeat(50,75);
	player = new Actor(40,25,'@', TCODColor::white);
	actors.push(player);
	map = new Map(80,45);
}

Engine::~Engine()
{
	actors.clearAndDelete();
	delete map;
}

void Engine::update() {
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	
	switch(key.vk) {
		case TCODK_KP8:
		case TCODK_UP:
			if ( !map->isWall(player->x, player->y-1)) {
				player->y--;
			}
			computeFov=true;
			break;
		
		case TCODK_KP2:
		case TCODK_DOWN:
			if ( !map->isWall(player->x, player->y+1)) {
				player->y++;
			}
			computeFov=true;
			break;
		
		case TCODK_KP4:
		case TCODK_LEFT:
			if ( !map->isWall(player->x-1, player->y)) {
				player->x--;
			}
			computeFov=true;
			break;
		
		case TCODK_KP6:
		case TCODK_RIGHT:
			if ( !map->isWall(player->x+1, player->y)) {
				player->x++;
			}
			computeFov=true;
			break;
			
		default: break;
	}
	if (computeFov) {
		map->computeFov();
		computeFov=false;
	}
}

void Engine::render() {
	TCODConsole::root->clear();
	// draw the map
	map->render();
	for (Actor **iterator=actors.begin(); iterator != actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (map->isInFov(actor->x, actor->y)) {
			actor->render();
		}
	}
}