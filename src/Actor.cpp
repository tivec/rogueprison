#include <stdio.h>
#include "main.hpp"

Actor::Actor(int x, int y, int ch, const char* name, const TCODColor& col) :
	x(x), y(y), ch(ch), col(col),
	blocks(true), attacker(NULL), destructible(NULL), ai(NULL) {
	strcpy(this->name, name);
}

void Actor::render() const {
	TCODConsole::root->setChar(x,y,ch);
	TCODConsole::root->setCharForeground(x,y,col);
}

void Actor::update()
{
	if (ai) ai->update(this);
}
