#include "SpecialAbility.h"
#include "Character.h"
#include "BattleField.h"
#include <random>
#include "StatusEffect.h"
#include "mathUtils.h"
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

//////////////////////////////////////////////////////////////////////////////////////////////////////

Teleport::Teleport(Character& originator) :SpecialAbility(originator, TELEPORT_PROC_CHANCE)
{
}

bool Teleport::ConditionsAreMet()
{
	if (originator.target == nullptr)
		return false;
	else {
		const int distanceToTarget = ManhattanDistance(originator.currentBox->Line(), originator.currentBox->Column(),
			originator.target->currentBox->Line(), originator.target->currentBox->Column());
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
//////////////////////////////////////////////////////////////////////////////////////////////////////
SelfHeal::SelfHeal(Character& originator):SpecialAbility(originator, SELF_HEAL_PROC_CHANCE){
}

bool SelfHeal::ConditionsAreMet() {
	return !originator.HasEffect(Heal::TypeID);
}

void SelfHeal::Execute() {
	shared_ptr<Heal> effect = make_shared<Heal>(originator, originator, 25);
	cout << "Player " << originator.PlayerIndex << " is using self-heal" << endl;
	originator.AddEffect(effect);
}



Smite::Smite(Character& originator) :SpecialAbility(originator, SMITE_PROC_CHANCE) {}
bool Smite::ConditionsAreMet() {
	return originator.Health <= SMITE_MAX_HP_PROC;
}
void Smite::Execute() {
	
}
////////////////////////////////////////////////////////////////////////////////////////
Curse::Curse(Character& originator) :SpecialAbility(originator, CURSE_PROC_CHANCE) {}
bool Curse::ConditionsAreMet() {
	return false;
}
void Curse::Execute()
{

}

Reanimate::Reanimate(Character& originator):SpecialAbility(originator, REANIMATE_PROC_CHANCE){}
bool Reanimate::ConditionsAreMet() {
	return false;
}
void Reanimate::Execute() {

}
