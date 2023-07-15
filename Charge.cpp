#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
Charge::Charge(Character& originator) :SpecialAbility(originator, CHARGE_PROC_CHANCE) {}
bool Charge::ConditionsAreMet() {
	return originator.target != nullptr;
}
void Charge::Execute() {
	cout << "Player " << originator.PlayerIndex << " is charging against " << originator.target->PlayerIndex << endl;
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