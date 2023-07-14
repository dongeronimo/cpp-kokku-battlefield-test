#pragma once
#include <memory>
#define HEAL_DURATION 1
#define STUN_DURATION 3
using namespace std;
class Character;
class StatusEffect
{
private:
	const int type;
protected:
	Character& actor;
	Character& subject;
public:

	StatusEffect(Character& actor, Character& subject, unsigned int duration, const int type);
	const unsigned int Duration;
	unsigned int Time;
	virtual void Apply() = 0;
	const int Type()const {
		return type;
	}
	bool IsFinished() { return Time > Duration; }
};

class Heal:public StatusEffect
{
private:
	const int Amount;
public:
	static const int TypeID;
	Heal(Character& actor, Character& subject, int amount);
	void Apply()override;
};

class Stun : public StatusEffect
{
public:
	static const int TypeID;
	Stun(Character& actor, Character& subject);
	void Apply() override;
};