#include "SpecialAbility.h"
#include "Character.h"
#include "BattleField.h"
#include <random>
using namespace std;
//Gerador de numeros aleatórios da STL
random_device randomDevice;
std::mt19937 randomNumberGenerator(randomDevice());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

SpecialAbility::SpecialAbility(const shared_ptr<Character> originator, 
	const float proc) :proc(proc), originator(originator) {

}

bool SpecialAbility::RollDice()
{
	auto dice = distribution(randomNumberGenerator);
	return dice <= proc;
}

StrongAttack::StrongAttack(const shared_ptr<Character> originator)
	:SpecialAbility(originator, STRONG_ATTACK_PROC_CHANCE)
{
}

void StrongAttack::Execute(shared_ptr<Character> target)
{
	cout << "Player " << originator->PlayerIndex << " will do a strong attack!" << endl;
	auto oldMultiplier = originator->DamageMultiplier;
	originator->DamageMultiplier = 2.0f;
	originator->Attack(target);
	originator->DamageMultiplier = oldMultiplier;
}
