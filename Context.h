#pragma once
#include <exception>
///Para coisas do contexto da app, como inicializa��o e t�rmino. No momento s� tem o t�rmino.
class QuitGameSignal : public std::exception
{
public:
	virtual char const* what() const { return "Signal to end the game"; }
};
void Quit();