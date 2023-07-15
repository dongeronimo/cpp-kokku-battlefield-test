#include "StatusEffect.h"
#include "Character.h"
#include "UI.h"
#include "Context.h"
using namespace std;
const int Heal::TypeID = 1;
const int Stun::TypeID = 2;
const int PulsaDinura::TypeID = 3;

StatusEffect::StatusEffect(Character& actor,
	Character& subject, unsigned int duration, const int type)
	:actor(actor), subject(subject), Duration(duration), Time(0), type(type)
{
}



Heal::Heal(Character& actor, Character& subject, float amount)
	:StatusEffect(actor, subject, CONTEXT.GetSpecialAbilitiesAttributes().HEAL_DURATION, Heal::TypeID), Amount(amount)
{
}
void Heal::Apply() {
	if (!IsFinished()) {
		Time++;
		subject.Health += Amount;
		_UI.HealApply(subject.PlayerIndex, Amount);
	}
}


Stun::Stun(Character& actor, Character& subject)
	:StatusEffect(actor, subject, CONTEXT.GetSpecialAbilitiesAttributes().STUN_DURATION,Stun::TypeID){}
void Stun::Apply() {
	if (!IsFinished()) {
		Time++;
		_UI.StunApply(subject.PlayerIndex);
	}
}

PulsaDinura::PulsaDinura(Character & actor, Character & subject)
	:StatusEffect(actor, subject, CONTEXT.GetSpecialAbilitiesAttributes().CURSE_DURATION, Stun::TypeID) {}
void PulsaDinura::Apply() {
	if (!IsFinished()) {
		Time++;
		_UI.PulsaDinuraApply(subject.PlayerIndex);
		subject.TakeDamage(CONTEXT.GetSpecialAbilitiesAttributes().CURSE_DAMAGE);
	}
}
