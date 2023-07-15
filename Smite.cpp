#include "SpecialAbility.h"
#include "Character.h"
#include "BattleField.h"
#include "StatusEffect.h"
#include "UI.h"
Smite::Smite(Character& originator) :SpecialAbility(originator, SMITE_PROC_CHANCE) {}
bool Smite::ConditionsAreMet() {
	return originator.target != nullptr && originator.Health <= SMITE_MAX_HP_PROC && MANHATTAN_DISTANCE_BETWEEN_ORIGINATOR_AND_TARGET <= 1;
}
void Smite::Execute() {
	//1) empurra o target para trás se for possivel.
	_UI->Smite(originator.PlayerIndex, originator.target->PlayerIndex);

	originator.battlefield.DrawBattlefield();
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
	originator.battlefield.DrawBattlefield();
}