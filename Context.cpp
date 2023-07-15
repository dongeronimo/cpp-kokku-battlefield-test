#include "Context.h"
using namespace std;

shared_ptr<Context> Context::instance = make_shared<Context>();
shared_ptr<Context> Context::Instance() {
	return instance;
}

