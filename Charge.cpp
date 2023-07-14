#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"
#include <iostream>
Charge::Charge(Character& originator) :SpecialAbility(originator, CHARGE_PROC_CHANCE) {}
bool Charge::ConditionsAreMet() {
	return originator.target != nullptr;
}
void Charge::Execute() {
	cout << "Player " << originator.PlayerIndex << " is charging against " << originator.target->PlayerIndex << endl;
	originator.MoveToTarget();
	originator.MoveToTarget();
	originator.MoveToTarget();
}