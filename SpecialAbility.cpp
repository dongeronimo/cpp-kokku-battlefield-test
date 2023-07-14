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
