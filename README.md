# __CLProgram__

## __What is CLProgram?__
CLProgram is simply a wrapper class for organizing tools, tests, examples which run in the command line

---

## __How to use__
``` C++
#include "CLProgram.h" // include the header file

// inherit from CLProgram
class CLDerived : public CLProgram {
public:
    CLDerived() : CLProgram("My Program") {
        // ...
    }

    // override the run function
    void run() override {
        // program code
    }
    
};

int main() {

    // create and add subprograms to program
    CLProgram* subprogram = new CLProgram("Derived Program", "Description");
    subprogram->addSubprogram(new CLDerived());

    // add subprograms to root program
    CLProgram* root = new CLProgram("Main Menu");
    root->addSubprogram(new CLProgram("About", "This is an example"));
    root->addSubprogram(submenu);

    // run the root program
    root->run();

    return 0;
}
```

Check out the CLFunction, CLEcho, and CLBanking examples for how to wrap your program

---

## __What does it look like?__

Here is what the above example prompt would look like
```
----[[ Main Menu ]]----
[a]     About
[b]     My Programs
[<]     Exit Main Menu

```

Selecting option [a] results in:
```
----[[ About ]]----
This is an example
[<]     Exit About

```

Selecting option [b] results in:
```
----[[ My Programs ]]----
[a]     Derived Program
[<]     Exit My Programs

```
The prompt function is also overridable so you can change this to look however you like!

---

## Examples

### __CLEcho__
```
----[[ Echo ]]----
This program echos to the console the text that you type!
Press <Ctrl-Z> then <Enter> on a new line to finish
Enter text:
This is a line!
And another
^Z
You typed:
This is a line!
And another

[<]     Exit Echo
```

<br>

### __CLFunction__

This class demonstrates inheriting from CLProgram and overriding it's run function to run a simple program.

Things to note:
When overriding CLProgram::run, the program will immediately exit to the last CLProgram and not pause
if CLProgram::prompt is not called at the end of the function

CLFunction may be a better option if the code you are wrapping is rather simple

<br>

Here we wrap this simple add function:
``` C++
void add() {
    int a, b;

    std::cout << "Enter first number: ";
    std::cin >> a;

    std::cout << "Enter second number: ";
    std::cin >> b;

    std::cout << a << " + " << b << " = " << (a + b) << "\n";
}
```
The output:
```
----[[ Simple add ]]----
Enter first number: 2
Enter second number: 2
2 + 2 = 4
[<]     Exit Simple add
```

<br>

### __CLBanking__

This class demonstrates a CLProgram which saves other
runtime-persistant state information such as a map of accounts and balances.

Check out the source for details