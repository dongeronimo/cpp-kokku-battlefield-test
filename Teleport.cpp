#include "SpecialAbility.h"
#include "mathUtils.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
Teleport::Teleport(Character& originator) :SpecialAbility(originator, TELEPORT_PROC_CHANCE)
{
}

bool Teleport::ConditionsAreMet()
{
	if (originator.target == nullptr)
		return false;
	else {
		const int distanceToTarget = MANHATTAN_DISTANCE_BETWEEN_ORIGINATOR_AND_TARGET;
		return distanceToTarget <= TELEPORT_PROC_DISTANCE;
	}
}

void Teleport::Execute()
{
	cout << "Player " << originator.PlayerIndex << " will teleport away!" << endl;
	originator.battlefield.DrawBattlefield();
	
	//procura um gridbox pra entrar
	auto emptyGridbox = originator.battlefield.GetEmptyGridbox();
	//troca a localização do originator
	originator.currentBox->ocupied = false;
	originator.currentBox = emptyGridbox;
	originator.currentBox->ocupied = true;


}