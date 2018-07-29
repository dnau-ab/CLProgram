#include "CLProgram.h"
#include "CLEcho.h"
#include "CLFunction.h"
#include "CLBanking.h"

void add() {
	int a, b;

	std::cout << "Enter first number: ";
	std::cin >> a;

	std::cout << "Enter second number: ";
	std::cin >> b;

	std::cout << a << " + " << b << " = " << (a + b) << "\n";
}

void subtract() {
	int a, b;

	std::cout << "Enter first number: ";
	std::cin >> a;

	std::cout << "Enter second number: ";
	std::cin >> b;

	std::cout << a << " - " << b << " = " << (a - b) << "\n";
}

int main() {
	CLProgram* examples = new CLProgram("Example Programs");
	examples->addSubprogram(new CLFunction("Simple add", add));
	examples->addSubprogram(new CLFunction("Simple subtract", subtract));
	examples->addSubprogram(new CLEcho());
	examples->addSubprogram(new CLBanking());
	
	CLProgram* tests = new CLProgram("Tests");

	CLProgram* full = new CLProgram("Large list");
	unsigned index = 1;
	while (full->canAddSubprogram()) {
		full->addSubprogram(new CLProgram("Sub-program " + std::to_string(index++), "A sub-program"));
	}

	CLProgram* root = new CLProgram("Main Menu");
	root->addSubprogram(new CLProgram("About", "This program was made by David Naughton\nIt is a useful way for organizing examples, tests, and other command line applications."));
	root->addSubprogram(examples);
	root->addSubprogram(tests);
	root->addSubprogram(full);

	root->run();

	return 0;
}