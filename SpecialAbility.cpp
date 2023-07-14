#include "SpecialAbility.h"
#include "Character.h"
#include "BattleField.h"
#include <random>
using namespace std;
//Gerador de numeros aleatórios da STL
random_device randomDevice;
std::mt19937 randomNumberGenerator(randomDevice());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

SpecialAbility::SpecialAbility(Character& originator,
	const float proc) :proc(proc), originator(originator) {

}

bool SpecialAbility::RollDice()
{
	auto dice = distribution(randomNumberGenerator);
	return dice <= proc;
}

StrongAttack::StrongAttack(Character& originator)
	:SpecialAbility(originator, STRONG_ATTACK_PROC_CHANCE)
{
}

bool StrongAttack::ConditionsAreMet() {
	return originator.IsDead() == false && originator.target != nullptr;
}
void StrongAttack::Execute()
{
	cout << "Player " << originator.PlayerIndex << " will do a strong attack!" << endl;
	auto oldMultiplier = originator.DamageMultiplier;
	originator.DamageMultiplier = 2.0f;
	originator.Attack(originator.target);
	originator.DamageMultiplier = oldMultiplier;
}

Teleport::Teleport(Character& originator) :SpecialAbility(originator, TELEPORT_PROC_CHANCE)
{
}

bool Teleport::ConditionsAreMet()
{
	if (originator.target == nullptr)
		return false;
	else {
		const int distanceToTarget = std::abs(originator.target->currentBox->Line() - originator.currentBox->Line()) +
			std::abs(originator.target->currentBox->Column() - originator.currentBox->Column());
		return distanceToTarget <= TELEPORT_PROC_DISTANCE;
	}
}

void Teleport::Execute()
{
	cout << "Player " << originator.PlayerIndex << " will teleport away!"<< endl;
	//procura um gridbox pra entrar
	auto emptyGridbox = originator.battlefield.GetEmptyGridbox();
	//troca a localização do originator
	originator.currentBox->ocupied = false;
	originator.currentBox = emptyGridbox;
	originator.currentBox->ocupied = true;
}
