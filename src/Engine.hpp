#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine
{
public:
	int fovRadius;
	int screenWidth;
	int screenHeight;
	
	TCODList<Actor *> actors;
	Actor *player;
	Map *map;
	TCOD_key_t lastKey;
	
	Engine(int screenWidth, int screenHeight);
	~Engine();
	
	void update();
	void render();
	void sendToBack(Actor *actor);

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
