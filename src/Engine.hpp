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

	enum GameStatus {
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} gameStatus;

};

extern Engine engine;
#endif // ENGINE_HPP
