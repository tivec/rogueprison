#ifndef ATTACKER_HPP
#define ATTACKER_HPP

class Attacker
{
public:
	float power; // hit points!
	
	Attacker(float power);
	void attack(Actor *owner, Actor *target);

};

#endif // ATTACKER_HPP
