/*

 CLEcho

 This class demonstrates inheriting from CLProgram and overriding it's run function to run a simple program.

 Things to note:
 When overriding CLProgram::run, the program will immediately exit to the last CLProgram and not pause
 if CLProgram::prompt is not called at the end of the function

 CLFunction may be a better option if the code you are wrapping is rather simple

 */

#ifndef CL_ECHO_H
#define CL_ECHO_H

#include <iostream>
#include <string>

#include "CLProgram.h"

class CLEcho : public CLProgram {
public:
	CLEcho() : CLProgram("Echo") {}

	void printHeader(std::ostream& out = std::cout) override {
		CLProgram::printHeader(out);
		out << "This program echos to the console the text that you type!\n";
		out << "Press <Ctrl-Z> then <Enter> on a new line to finish\n";
	}

	void run() override {
		printHeader();
		std::cout << "Enter text: \n";
		std::string input, allText = "";
		std::cin.clear();
		std::cin.sync();
		if (std::cin.peek() == '\n')
			std::getchar();
		while (!std::cin.eof()) {
			std::getline(std::cin, input);
			allText += input + "\n";
		} 
		std::cout << "You typed: \n" << allText;
		prompt();
	}
};

#endif