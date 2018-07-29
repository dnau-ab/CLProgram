
#include "CLProgram.h"

void CLProgram::run() {
	printHeader();
	while (!_shouldQuit) {
		prompt();
	}
	// reset flag
	_shouldQuit = false;
}

void CLProgram::addSubprogram(CLProgram* subprogram) {
	if (canAddSubprogram()) {
		_subprograms.push_back(subprogram);
	}
}

bool CLProgram::canAddSubprogram() {
	return _subprograms.size() < MAX_NUM_SUBPROGRAMS;
}

void CLProgram::printHeader(std::ostream& out) {
	out << "----[[ " << _name << " ]]----\n";
	if (_description != "")
		out << _description << "\n";
}

void CLProgram::printOptions(std::ostream& out) {
	//out << "Select one of the following options:\n";
	for (size_t i = 0; i < _subprograms.size(); i++) {
		out << "[" << char('a' + i) << "]" << "\t" << _subprograms[i]->getName() << "\n";
	}
	out << "[" << quitChar << "]" << "\tExit " << _name << "\n";
}

void CLProgram::prompt(std::ostream& out, std::istream& in) {

	// handle std::getline(), >> issues
	in.clear();
	in.sync();

	printOptions(out);

	std::string response = "";
	// prompt until response is valid
	while (in >> response && !isValid(response)) {
		out << "ERROR: That option is not valid\n";
		//printOptions(out);
	}

	// now have a valid response
	if (response[0] == quitChar) {
		_shouldQuit = true;
		return;
	}
	unsigned selectedOpt = response[0] - 'a';

	system("CLS");
	_subprograms[selectedOpt]->run();
	system("CLS");

	// after finishing with the subprogram, display the name of the program we are backing into
	printHeader();

}

bool CLProgram::isValid(std::string& response) {
	if (response.length() == 0) return false;

	// character to quit program is valid
	if (response[0] == quitChar) return true;

	// option in range [0, _subprograms.size()-1] is valid
	unsigned selectedOpt = response[0] - 'a';
	if (selectedOpt >= 0 && selectedOpt < _subprograms.size()) return true;

	return false;
}