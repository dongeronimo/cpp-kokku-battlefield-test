#pragma once
#include <memory>

class Battlefield;
class Character;

using namespace std;
#define STRONG_ATTACK_PROC_CHANCE 0.33f
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
