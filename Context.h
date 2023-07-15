#pragma once
#include <memory>
#include <exception>
#include <random>
///Para coisas do contexto da app, como inicializa��o e t�rmino. No momento s� tem o t�rmino.
class QuitGameSignal : public std::exception
{
public:
	virtual char const* what() const { return "Signal to end the game"; }
};


#define CONTEXT Context::Instance()

class Context {
private:
	static std::shared_ptr<Context> instance;
public:
	static std::shared_ptr<Context> Instance();
	void Quit() { throw QuitGameSignal(); }
	std::mt19937& RNG();
	const int RandomInteger(const int a, const int b);
};