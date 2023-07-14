#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"
#include <iostream>
using namespace std;
StrongAttack::StrongAttack(Character& originator)
	:SpecialAbility(originator, STRONG_ATTACK_PROC_CHANCE)
{
}

bool StrongAttack::ConditionsAreMet() {
	return originator.IsDead() == false && originator.target != nullptr && MANHATTAN_DISTANCE_BETWEEN_ORIGINATOR_AND_TARGET <= 1;
}
void StrongAttack::Execute()
{
	cout << "Player " << originator.PlayerIndex << " will do a strong attack!" << endl;
	auto oldMultiplier = originator.DamageMultiplier;
	originator.DamageMultiplier = 2.0f;
	originator.Attack(originator.target);
	originator.DamageMultiplier = oldMultiplier;
}