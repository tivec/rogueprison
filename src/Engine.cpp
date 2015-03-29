#include <vector>

#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Engine::Engine() : fovRadius(10), gameStatus(STARTUP)
{
	TCODConsole::initRoot(80,50, "libtcod C++ tutorial", false);
	TCODConsole::root->setKeyboardRepeat(50,75);
	player = new Actor(40,25,'@', "player", TCODColor::white);
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
	if (gameStatus== STARTUP) map->computeFov();
	gameStatus=IDLE;
	
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	int dx=0,dy=0;
	switch(key.vk) {
		case TCODK_KP8:		dy=-1; break;
		case TCODK_UP:		dy=-1; break;
					
		case TCODK_KP2: 	dy= 1; break;
		case TCODK_DOWN:	dy= 1; break;
		
		case TCODK_KP4: 	dx=-1; break;
		case TCODK_LEFT:	dx=-1; break;
		
		case TCODK_KP6:		dx= 1; break;
		case TCODK_RIGHT:	dx= 1; break;
			
		default: break;
	}
	if (dx !=0 || dy != 0) {
		gameStatus=NEW_TURN;
		if (player->moveOrAttack(player->x+dx, player->y+dy)) {
			map->computeFov();
		}
	}
	
	if (gameStatus == NEW_TURN) {
		for (Actor **iterator=actors.begin(); iterator != actors.end(); iterator++) {
			Actor *actor = *iterator;
			if ( actor != player) {
				actor->update();
			}
		}
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