#pragma once
#include <memory>

class Battlefield;
class Character;

using namespace std;

class SpecialAbility
{
private:
	const float proc;
public:
	SpecialAbility(const float proc);
	bool RollDice();
	virtual void Execute(shared_ptr<Character> target) = 0;
};

