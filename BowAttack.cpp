#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"
#include "UI.h"
#include "Context.h"
BowAttack::BowAttack(Character& originator) :SpecialAbility(originator, 
	CONTEXT.GetSpecialAbilitiesAttributes().BOW_ATTACK_PROC_CHANCE) {}
bool BowAttack::ConditionsAreMet() {
	if (originator.target == nullptr)
		return false;
	else {
		const int distanceToTarget = ManhattanDistance(originator.currentBox->Line(), originator.currentBox->Column(),
			originator.target->currentBox->Line(), originator.target->currentBox->Column());
		return distanceToTarget <= CONTEXT.GetSpecialAbilitiesAttributes().BOW_ATTACK_PROC_MAX_DISTANCE;
	}
}
void BowAttack::Execute() {
	_UI.BowAttack(originator.PlayerIndex, originator.target->PlayerIndex);
	auto oldMultiplier = originator.DamageMultiplier;
	originator.DamageMultiplier = 0.5f;
	originator.Attack(originator.target);
	originator.DamageMultiplier = 1.0f;
}