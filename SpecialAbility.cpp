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
	return originator.Health <= SMITE_MAX_HP_PROC && MANHATTAN_DISTANCE_BETWEEN_ORIGINATOR_AND_TARGET <= 1;
}
void Smite::Execute() {
	//1) empurra o target para trás se for possivel.
	cout << "Player " << originator.PlayerIndex << " is smiting " << originator.target->PlayerIndex << endl;
	int dI = originator.currentBox->Line() - originator.target->currentBox->Line();
	int dJ = originator.currentBox->Column() - originator.target->currentBox->Column();
	int pushbackI = originator.target->currentBox->Line() - dI; //se A está está a esquerda de B, B será empurrado pra direita
	int pushbackJ = originator.target->currentBox->Column() - dJ; // se A está acima de B, B será empurrado pra baixo.
	Types::GridBox* pushbackGridbox = originator.battlefield.grid->GetIfEmpty(pushbackI, pushbackJ);
	if (pushbackGridbox != nullptr) {
		originator.target->currentBox->ocupied = false;
		originator.target->currentBox = pushbackGridbox;
		pushbackGridbox->ocupied = true;
	}
	//2) aplica o efeito de stun
	shared_ptr<Stun> stunEffect = std::make_shared<Stun>(originator, *originator.target);
	originator.target->AddEffect(stunEffect);
}
////////////////////////////////////////////////////////////////////////////////////////
Curse::Curse(Character& originator, const int turnsToRechargeCurse, const int range) : 
	SpecialAbility(originator, CURSE_PROC_CHANCE), 
	turnsSinceLastCurse(0), range(range),
	turnsToRechargeCurse(turnsToRechargeCurse)
{}

bool Curse::ConditionsAreMet() {
	if (turnsSinceLastCurse < turnsToRechargeCurse) {
		turnsSinceLastCurse++; //Como conditionsAreMet é invocado somente uma vez por turno isso aqui n tem problema.
		return false;
	}
	else
		return true;
}
void Curse::Execute()
{
	///Pega todos os inimigos no raio
	for (auto enemy : originator.battlefield.EnemyTeam) {
		auto distance = std::abs(originator.currentBox->Line() - enemy->currentBox->Line()) +
			std::abs(originator.currentBox->Column() - enemy->currentBox->Column());
		if (distance <= range) {
			//Aplica a maldição nos inimigs
			shared_ptr<PulsaDinura> pulsaDinura = make_shared<PulsaDinura>(originator, *enemy);
			enemy->AddEffect(pulsaDinura);
		}
	}
	//Pega todos os aliados no raio
	for (auto aFriend : originator.battlefield.EnemyTeam) {
		auto distance = std::abs(originator.currentBox->Line() - aFriend->currentBox->Line()) +
			std::abs(originator.currentBox->Column() - aFriend->currentBox->Column());
		if (distance <= range) {
			//Aplica a cura nos amigos
			shared_ptr<Heal> heal = make_shared<Heal>(originator, *aFriend, 20);
			aFriend->AddEffect(heal);
		}
	}
	turnsSinceLastCurse = 0;
}

Reanimate::Reanimate(Character& originator):SpecialAbility(originator, REANIMATE_PROC_CHANCE){}
bool Reanimate::ConditionsAreMet() {
	return false;
}
void Reanimate::Execute() {

}
