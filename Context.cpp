#include "Context.h"

using namespace std;
//Gerador de numeros aleatórios da STL
random_device rd;
std::mt19937 rng(rd());
Context* Context::instance = nullptr;

Context::Context()
	:PaladinAttrs({ 100, 20, 1.0f }), WarriorAttrs({ 100,20,1.0f }), 
	ClericAttrs({ 100,20,1.0f }),ArcherAttrs({ 100,20,1.0f })
{

}

Context& Context::Instance() {
	if (instance == nullptr) {
		instance = new Context();
		
	}
	return *instance;
}

std::mt19937& Context::RNG()
{
	return rng;
}

const int Context::RandomInteger(const int a, const int b)
{
	uniform_int_distribution<int> uni(a, b);
	auto randomInteger = uni(rng);
	return randomInteger;
}

const Types::ClassBaseAttributes Context::GetBaseAttributes(Types::CharacterClass cls)
{
	switch (cls) {
	case Types::CharacterClass::Paladin:
		return PaladinAttrs;
		break;
	case Types::CharacterClass::Warrior:
		return WarriorAttrs;
		break;
	case Types::CharacterClass::Cleric:
		return ClericAttrs;
		break;
	case Types::CharacterClass::Archer:
		return ArcherAttrs;
		break;
	}
}

