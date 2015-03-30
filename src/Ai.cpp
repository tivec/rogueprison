#include <stdio.h>
#include <math.h>
#include "main.hpp"

void PlayerAi::update(Actor *owner) {
	if (owner->destructible && owner->destructible->isDead() ) {
		return;
	}
	
	int dx=0,dy=0;
	switch(engine.lastKey.vk) {
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
		engine.gameStatus=Engine::NEW_TURN;
		if (moveOrAttack(owner, owner->x+dx, owner->y+dy)) {
			engine.map->computeFov();
		}
	}
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx, int targety) {
	if (engine.map->isWall(targetx, targety)) return false;
	// look for living actors to attack
	for (Actor **iterator=engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->destructible && !actor->destructible->isDead()
			&& actor->x == targetx && actor->y == targety) {
				owner->attacker->attack(owner, actor);
				return false;			
		}
	}
	
	for (Actor **iterator=engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->destructible && actor->destructible->isDead()) {
			printf("There's a %s here\n", actor->name);
		}
	}
	owner->x=targetx;
	owner->y=targety;
	return true;
}

void MonsterAi::update(Actor *owner) {
	if (owner->destructible && owner->destructible->isDead()) {
		return;
	}
	
	if (engine.map->isInFov(owner->x, owner->y)) {
		moveOrAttack(owner, engine.player->x, engine.player->y);
	}
}

void MonsterAi::moveOrAttack(Actor *owner, int targetx, int targety) {
	int dx = targetx - owner->x;
	int dy = targety - owner->y;
	float distance=sqrtf(dx*dx+dy*dy);
	
	if (distance >= 2) {
		dx = (int)(round(dx/distance));
		dy = (int)(round(dy/distance));
		if (engine.map->canWalk(owner->x+dx, owner->y+dy)) {
			owner->x += dx;
			owner->y += dy;
		}
	} else if (owner->attacker) {
		owner->attacker->attack(owner, engine.player);
	}
	
	
}