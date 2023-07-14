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
	const shared_ptr<Character> originator;
public:
	SpecialAbility(const shared_ptr<Character> originator, const float proc);
	bool RollDice();
	virtual void Execute(shared_ptr<Character> target) = 0;
};

class StrongAttack :public SpecialAbility {
public:
	StrongAttack(const shared_ptr<Character> originator);
	void Execute(shared_ptr<Character> target) override;
};
