#include "Context.h"

using namespace std;
//Gerador de numeros aleatórios da STL
random_device rd;
std::mt19937 rng(rd());

shared_ptr<Context> Context::instance = make_shared<Context>();
shared_ptr<Context> Context::Instance() {
	return instance;
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

