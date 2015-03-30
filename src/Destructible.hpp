#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

class Destructible
{
public:
	float maxHp;	// max health points
	float hp;		// current health points
	float defense;	// deflected hit points
	const char *corpseName; // actor's name once destroyed/dead
	
	Destructible(float maxHp, float defense, const char *corpseName);
	inline bool isDead() { return hp <= 0; }
	float takeDamage(Actor *owner, float damage);
	virtual void die(Actor *owner);
	
	~Destructible();

};

class MonsterDestructible : public Destructible {
public:
	MonsterDestructible(float maxHp, float defense, const char *corpseName);
	void die(Actor *owner);
};

class PlayerDestructible : public Destructible {
public:
	PlayerDestructible(float maxHp, float defense, const char *corpseName);
	void die(Actor *owner);
};


#endif // DESTRUCTIBLE_HPP
