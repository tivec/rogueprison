#ifndef ACTOR_HPP
#define ACTOR_HPP

static const int MAX_NAME_LENGTH = 32;

class Actor
{
public:
	int x,y; 	// position on map
	int ch; 	// ascii code
	TCODColor	col; // color
	char name[ MAX_NAME_LENGTH ]; // name of the actor
	
	bool blocks;	// can the actor be walked on?
	Attacker *attacker;	// does it deal damage?
	Destructible *destructible; // can it be damaged?
	Ai *ai; // self-updating?
	
	Actor(int x, int y, int ch, const char *name, const TCODColor &col);
	void update();
	void render() const;
};

#endif // ACTOR_HPP
