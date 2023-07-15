#include "StatusEffect.h"
#include "Character.h"
#include "UI.h"
using namespace std;


StatusEffect::StatusEffect(Character& actor,
	Character& subject, unsigned int duration, const int type)
	:actor(actor), subject(subject), Duration(duration), Time(0), type(type)
{
}

const int Heal::TypeID = 1;

Heal::Heal(Character& actor, Character& subject, int amount)
	:StatusEffect(actor, subject, HEAL_DURATION, Heal::TypeID), Amount(amount)
{
}

void Heal::Apply() {
	if (!IsFinished()) {
		Time++;
		subject.Health += Amount;
		_UI->HealApply(subject.PlayerIndex, Amount);
	}
}

const int Stun::TypeID = 2;
Stun::Stun(Character& actor, Character& subject)
	:StatusEffect(actor, subject, STUN_DURATION,Stun::TypeID){}

void Stun::Apply() {
	if (!IsFinished()) {
		Time++;
		_UI->StunApply(subject.PlayerIndex);
	}
}

const int PulsaDinura::TypeID = 3;

PulsaDinura::PulsaDinura(Character & actor, Character & subject)
	:StatusEffect(actor, subject, CURSE_DURATION, Stun::TypeID) {}

void PulsaDinura::Apply() {
	if (!IsFinished()) {
		Time++;
		_UI->PulsaDinuraApply(subject.PlayerIndex);
		subject.TakeDamage(CURSE_DAMAGE);
	}
}
