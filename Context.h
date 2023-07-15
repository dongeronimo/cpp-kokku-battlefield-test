#pragma once
#include <memory>
#include <exception>
#include <random>
#include "Types.h"
///Para coisas do contexto da app, como inicialização e término. No momento só tem o término.
class QuitGameSignal : public std::exception
{
public:
	virtual char const* what() const { return "Signal to end the game"; }
};


#define CONTEXT Context::Instance()

class Context {
private:
	static Context* instance;
	Context();
	Context(const Context&);
	~Context() {}
	const Types::ClassBaseAttributes PaladinAttrs, WarriorAttrs, ClericAttrs, ArcherAttrs;
	const Types::AbilitiesAndEffecsAttributes SpecialAbilitiesAttrs;
public:
	static Context& Instance();
	void Quit() { throw QuitGameSignal(); }
	void Release() { delete instance; }
	std::mt19937& RNG();
	const int RandomInteger(const int a, const int b);
	const Types::ClassBaseAttributes GetBaseAttributes(Types::CharacterClass cls);
	const Types::AbilitiesAndEffecsAttributes GetSpecialAbilitiesAttributes() {
		return SpecialAbilitiesAttrs;
	}
};