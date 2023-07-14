#pragma once
#include <memory>

class Battlefield;
class Character;

using namespace std;
#define STRONG_ATTACK_PROC_CHANCE 0.33f
#define TELEPORT_PROC_CHANCE 0.33f
#define TELEPORT_PROC_DISTANCE 3
#define SELF_HEAL_PROC_CHANCE 0.33f
#define BOW_ATTACK_PROC_CHANCE 0.75f
#define BOW_ATTACK_PROC_MAX_DISTANCE 5 
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

class SelfHeal : public SpecialAbility {
public:
	SelfHeal(Character& originator);
	bool ConditionsAreMet() override;
	void Execute() override;
};

class BowAttack : public SpecialAbility {
public:
	BowAttack(Character& originator);
	bool ConditionsAreMet() override;
	void Execute()override;
};