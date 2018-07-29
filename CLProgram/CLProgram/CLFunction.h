/*
 CLFunction

 This class demonstrates a CLProgram which wraps a function
 allowing any function to be added as an option in a CLProgram menu

*/

#ifndef CL_FUNCTION_H
#define CL_FUNCTION_H

#include <iostream>
#include <string>

#include "CLProgram.h"

class CLFunction : public CLProgram {

	typedef void(*Function)(void);

public:

	CLFunction(std::string name, Function func) : CLProgram(name), _func(func) {}

	void run() override {
		printHeader();
		_func();
		prompt();
	}

protected:

private:
	Function _func;
};

#endif