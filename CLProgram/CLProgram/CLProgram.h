#ifndef CL_PROGRAM_H
#define CL_PROGRAM_H

#include<iostream>
#include<string>
#include<vector>

class CLProgram {
public:

	CLProgram(std::string name, std::string description = "") : _name(name), _description(description), _subprograms() {}
	CLProgram(std::string name, std::vector<CLProgram*> subprograms, std::string description = "") : _name(name), _subprograms(subprograms), _description(description) {}
	virtual ~CLProgram() {
		for (CLProgram*& p : _subprograms)
		{
			delete p;
			p = nullptr;
		}
	}

	// enter program loop
	virtual void run();

	// adds a subprogram to the list if possible
	void addSubprogram(CLProgram* subprogram);

	// returns whether we have maxed out the number of subprograms
	bool canAddSubprogram();

	std::string getName() { return _name; }
	void setName(std::string name) { _name = name; }

	std::string getDescription() { return _description; }
	void setDescription(std::string description) { _description = description; }

protected:

	unsigned MAX_NUM_SUBPROGRAMS = 26;

	// name to display when displaying options
	std::string _name = "CLProgram";
	std::string _description = "";

	// character for quitting program
	char quitChar = '<';

	// should we stop executing our program loop?
	bool _shouldQuit = false;

	// list of subprograms we can run from the prompt
	std::vector<CLProgram*> _subprograms;


	// print header with information about program
	virtual void printHeader(std::ostream& out = std::cout);

	// displays all available subprograms
	virtual void printOptions(std::ostream& out = std::cout);

	// show prompt for optional sub-programs
	virtual void prompt(std::ostream& out = std::cout, std::istream& in = std::cin);

	// returns whether a response is valid given the first character of the response
	virtual bool isValid(std::string& response);

private:

};

#endif