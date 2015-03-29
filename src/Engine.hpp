#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine
{
public:
	int fovRadius;
	
	TCODList<Actor *> actors;
	Actor *player;
	Map *map;
	
	Engine();
	~Engine();
	
	void update();
	void render();
private:
	bool computeFov;
};

extern Engine engine;
#endif // ENGINE_HPP
