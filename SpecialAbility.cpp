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
	return originator.target != nullptr && originator.Health <= SMITE_MAX_HP_PROC && MANHATTAN_DISTANCE_BETWEEN_ORIGINATOR_AND_TARGET <= 1;
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
	//Quem é amigo e quem é inimigo varia de acordo com o time do character.
	cout << "Player " << originator.PlayerIndex << " is cursing enemies and blessing friends." << endl;
	vector<shared_ptr<Character>> enemies;
	vector<shared_ptr<Character>> allies;
	if (originator.GetTeam() == TeamA) {
		std::copy_if(originator.battlefield.EnemyTeam.begin(),
			originator.battlefield.EnemyTeam.end(),
			std::back_inserter(enemies),
			[](auto e) {
				return !e->IsDead();
			});
		std::copy_if(originator.battlefield.PlayerTeam.begin(),
			originator.battlefield.PlayerTeam.end(),
			std::back_inserter(allies),
			[](auto a) {
				return !a->IsDead();
			});
	}
	else {
		std::copy_if(originator.battlefield.EnemyTeam.begin(),
			originator.battlefield.EnemyTeam.end(),
			std::back_inserter(allies),
			[](auto a) {
				return !a->IsDead();
			});
		std::copy_if(originator.battlefield.PlayerTeam.begin(),
			originator.battlefield.PlayerTeam.end(),
			std::back_inserter(enemies),
			[](auto e) {
				return !e->IsDead();
			});
	}
	
	///Pega todos os inimigos no raio
	for (auto enemy : enemies) {
		auto distance = std::abs(originator.currentBox->Line() - enemy->currentBox->Line()) +
			std::abs(originator.currentBox->Column() - enemy->currentBox->Column());
		if (distance <= range) {
			//Aplica a maldição nos inimigs
			shared_ptr<PulsaDinura> pulsaDinura = make_shared<PulsaDinura>(originator, *enemy);
			enemy->AddEffect(pulsaDinura);
		}
	}
	//Pega todos os aliados no raio
	for (auto ally : allies) {
		auto distance = std::abs(originator.currentBox->Line() - ally->currentBox->Line()) +
			std::abs(originator.currentBox->Column() - ally->currentBox->Column());
		if (distance <= range) {
			//Aplica a cura nos amigos
			shared_ptr<Heal> heal = make_shared<Heal>(originator, *ally, 20);
			ally->AddEffect(heal);
		}
	}
	turnsSinceLastCurse = 0;
}

Reanimate::Reanimate(Character& originator):SpecialAbility(originator, REANIMATE_PROC_CHANCE){}
bool Reanimate::ConditionsAreMet() {
	vector<shared_ptr<Character>> allies;
	if (originator.GetTeam() == TeamA)
		allies = originator.battlefield.PlayerTeam;
	else
		allies = originator.battlefield.EnemyTeam;
	for (auto ally : allies) {
		if (ally->IsDead())
			return true;
	}
	return false;
}
void Reanimate::Execute() {
	
	//Escolhe o defunto pra ressussitar
	vector<shared_ptr<Character>> allies;
	if (originator.GetTeam() == TeamA)
		allies = originator.battlefield.PlayerTeam;
	else
		allies = originator.battlefield.EnemyTeam;
	vector<shared_ptr<Character>> deadAllies;
	std::copy_if(allies.begin(), allies.end(), std::back_inserter(deadAllies),
		[](auto ally) {
			return ally->IsDead();
		});
	std::shuffle(deadAllies.begin(), deadAllies.end(), randomNumberGenerator);
	auto chosen = deadAllies[0];
	//altera os estados dele para ele voltar pra partida
	chosen->Health = 20;
	chosen->IsDead(false);
	//posiciona ele perto do cleric. Se não houver como posicionar perto do cleric posiciona random
	Types::GridBox* box = nullptr;
	box = originator.battlefield.grid->GetIfEmpty(originator.currentBox->Line()-1,
		originator.currentBox->Column());
	if(!box)
		box = originator.battlefield.grid->GetIfEmpty(originator.currentBox->Line() + 1,
			originator.currentBox->Column());
	if (!box)
		box = originator.battlefield.grid->GetIfEmpty(originator.currentBox->Line(),
			originator.currentBox->Column() - 1);
	if (!box)
		box = originator.battlefield.grid->GetIfEmpty(originator.currentBox->Line(),
			originator.currentBox->Column() + 1);
	if (!box) {
		box = originator.battlefield.GetRandomUnocupied();
	}
	chosen->currentBox = box;
	box->ocupied = true;
	cout << "Player " << originator.PlayerIndex << " ressurected "<<chosen->PlayerIndex << endl;
}
