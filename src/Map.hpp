#ifndef MAP_HPP
#define MAP_HPP


struct Tile {
	bool explored;	// visited?
	Tile() : explored(false) {}
};

class Map
{
public:
	int width, height;
	
	Map(int width, int height);
	~Map();
	
	bool isWall(int x, int y) const;
	bool canWalk(int x, int y) const;
	
	bool isInFov(int x, int y) const;
	bool isExplored(int x, int y) const;
	void computeFov();
	
	void render() const;
	
	
protected:
	Tile *tiles;
	TCODMap *map;
	friend class BspListener;
	
	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);
	
};

class BspListener : public ITCODBspCallback {
private:
	Map &map;		// map to dig
	int roomNum;	// room number
	int lastx,lasty;// center of last room
public:
	BspListener(Map &map) : map(map), roomNum(0) {}
	bool visitNode(TCODBsp *node, void *userData);
};


#endif // MAP_HPP
