#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"
#include <iostream>

BowAttack::BowAttack(Character& originator) :SpecialAbility(originator, BOW_ATTACK_PROC_CHANCE) {}
bool BowAttack::ConditionsAreMet() {
	if (originator.target == nullptr)
		return false;
	else {
		const int distanceToTarget = ManhattanDistance(originator.currentBox->Line(), originator.currentBox->Column(),
			originator.target->currentBox->Line(), originator.target->currentBox->Column());
		return distanceToTarget <= BOW_ATTACK_PROC_MAX_DISTANCE;
	}
}
void BowAttack::Execute() {
	cout << "Player " << originator.PlayerIndex << " is firing arrows at " << originator.target->PlayerIndex << endl;
	auto oldMultiplier = originator.DamageMultiplier;
	originator.DamageMultiplier = 0.5f;
	originator.Attack(originator.target);
	originator.DamageMultiplier = 1.0f;
}