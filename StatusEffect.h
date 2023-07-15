#pragma once
#include <memory>

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
	const float Amount;
public:
	static const int TypeID;
	Heal(Character& actor, Character& subject, float amount);
	void Apply()override;
};

class Stun : public StatusEffect
{
public:
	static const int TypeID;
	Stun(Character& actor, Character& subject);
	void Apply() override;
};

class PulsaDinura : public StatusEffect
{
public:
	static const int TypeID;
	PulsaDinura(Character& actor, Character& subject);
	void Apply()override;
};