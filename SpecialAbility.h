#pragma once
#include <memory>

class Battlefield;
class Character;

using namespace std;
#define STRONG_ATTACK_PROC_CHANCE 0.33f
#define TELEPORT_PROC_CHANCE 0.33f
#define TELEPORT_PROC_DISTANCE 3
class SpecialAbility
{
private:
	const float proc;
protected:
	Character& originator;
public:
	SpecialAbility(Character& originator, const float proc);
	bool RollDice();
	virtual bool ConditionsAreMet() = 0;
	virtual void Execute() = 0;
};

class StrongAttack :public SpecialAbility {
public:
	StrongAttack(Character& originator);
	bool ConditionsAreMet() override;
	void Execute() override;
};

class Teleport : public SpecialAbility {
public:
	Teleport(Character& originator);
	bool ConditionsAreMet() override;
	void Execute() override;
};
