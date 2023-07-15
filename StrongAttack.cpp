#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"
#include "UI.h"
#include "Context.h"
using namespace std;
StrongAttack::StrongAttack(Character& originator)
	:SpecialAbility(originator, CONTEXT.GetSpecialAbilitiesAttributes().STRONG_ATTACK_PROC_CHANCE)
{
}

bool StrongAttack::ConditionsAreMet() {
	return originator.IsDead() == false && originator.target != nullptr && MANHATTAN_DISTANCE_BETWEEN_ORIGINATOR_AND_TARGET <= 1;
}
void StrongAttack::Execute()
{
	_UI.StrongAttack(originator.PlayerIndex);
	auto oldMultiplier = originator.DamageMultiplier;
	originator.DamageMultiplier = 2.0f;
	originator.Attack(originator.target);
	originator.DamageMultiplier = oldMultiplier;
}