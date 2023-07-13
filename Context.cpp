#include "Context.h"

void Quit() {
	throw QuitGameSignal();
}