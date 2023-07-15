#include "SpecialAbility.h"
#include "Character.h"
#include "BattleField.h"
#include <iterator>
#include <vector>
#include <algorithm>
#include "Context.h"
#include "UI.h"
Reanimate::Reanimate(Character& originator) :SpecialAbility(originator, REANIMATE_PROC_CHANCE) {}
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
	std::shuffle(deadAllies.begin(), deadAllies.end(), CONTEXT->RNG());
	auto chosen = deadAllies[0];
	//altera os estados dele para ele voltar pra partida
	chosen->Health = 20;
	chosen->IsDead(false);
	//posiciona ele perto do cleric. Se não houver como posicionar perto do cleric posiciona random
	Types::GridBox* box = nullptr;
	box = originator.battlefield.grid->GetIfEmpty(originator.currentBox->Line() - 1,
		originator.currentBox->Column());
	if (!box)
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
	_UI->Reanimate(originator.PlayerIndex, chosen->PlayerIndex);
	originator.battlefield.DrawBattlefield();
}
