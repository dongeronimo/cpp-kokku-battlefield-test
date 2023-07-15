#include "SpecialAbility.h"
#include "Character.h"
#include "StatusEffect.h"
#include "UI.h"
#include "Context.h"
SelfHeal::SelfHeal(Character& originator) :SpecialAbility(originator, CONTEXT.GetSpecialAbilitiesAttributes().SELF_HEAL_PROC_CHANCE) {
}

bool SelfHeal::ConditionsAreMet() {
	return !originator.HasEffect(Heal::TypeID);
}

void SelfHeal::Execute() {
	shared_ptr<Heal> effect = make_shared<Heal>(originator, originator, 25);
	_UI.SelfHeal(originator.PlayerIndex);
	originator.AddEffect(effect);
}