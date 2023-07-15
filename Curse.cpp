#include "SpecialAbility.h"
#include "Character.h"
#include "BattleField.h"
#include "UI.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include "StatusEffect.h"
#include "Context.h"
Curse::Curse(Character& originator, const int turnsToRechargeCurse, const int range) :
	SpecialAbility(originator, CONTEXT.GetSpecialAbilitiesAttributes().CURSE_PROC_CHANCE),
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
	_UI.Curse(originator.PlayerIndex);
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