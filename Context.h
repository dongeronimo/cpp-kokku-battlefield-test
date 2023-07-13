#pragma once
#include <exception>
///Para coisas do contexto da app, como inicialização e término. No momento só tem o término.
class QuitGameSignal : public std::exception
{
public:
	virtual char const* what() const { return "Signal to end the game"; }
};
void Quit();