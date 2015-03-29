#ifndef ACTOR_HPP
#define ACTOR_HPP


static const int MAX_NAME_LENGTH = 32;

class Actor
{
public:
	int x,y; 	// position on map
	int ch; 	// ascii code
	char name[ MAX_NAME_LENGTH ]; // name of the actor
	TCODColor	col; // color
	
	Actor(int x, int y, int ch, const char *name, const TCODColor &col);
	void update();
	bool moveOrAttack(int x, int y);
	void render() const;
};

#endif // ACTOR_HPP
