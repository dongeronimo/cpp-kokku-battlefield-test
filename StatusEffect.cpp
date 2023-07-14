#include "StatusEffect.h"
#include "Character.h"
#include <iostream>
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
		cout << "Player " << subject.PlayerIndex << " will heal "<<Amount << endl;
	}
}