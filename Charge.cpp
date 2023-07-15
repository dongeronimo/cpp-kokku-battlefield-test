#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"

#include "BattleField.h"
#include "UI.h"
#include "Context.h"
Charge::Charge(Character& originator) :SpecialAbility(originator, CONTEXT.GetSpecialAbilitiesAttributes().CHARGE_PROC_CHANCE) {}
bool Charge::ConditionsAreMet() {
	return originator.target != nullptr;
}
void Charge::Execute() {
	_UI.Charge(originator.PlayerIndex, originator.target->PlayerIndex);
	auto result = originator.MoveToTarget();
	if (result.size() != 0) {
		originator.battlefield.DrawBattlefield();
		result = originator.MoveToTarget();
	}
	if (result.size() != 0) {
		originator.battlefield.DrawBattlefield();
		result = originator.MoveToTarget();
	}
	if (result.size() != 0) {
		originator.battlefield.DrawBattlefield();
	}
}