/* 
 CLBanking

 This class demonstrates a CLProgram which saves other
 runtime-persistant state information such as a map of accounts and balances.

 */

#ifndef CL_BANKING_H
#define CL_BANKING_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>

#include "CLProgram.h"
#include "CLFunction.h"

class CLBanking;

/*
 CLBankFunction is a wrapper for a CLBanking member function 
 so that the functions show as options in the banking menu
*/
class CLBankFunction : public CLProgram {

	typedef void(CLBanking::*BankFunction)(void);

public:

	CLBankFunction(std::string name, CLBanking* bank, BankFunction func) : CLProgram(name), _bank(bank), _func(func) {}

	void run() override {
		printHeader();
		(_bank->*_func)();
		prompt();
	}

protected:

private:

	CLBanking* _bank;
	BankFunction _func;
};

class CLBanking : public CLProgram {
public:

	CLBanking() : CLProgram("Bank"), _database() {
		// initialize our "database" with some account data
		_database[1234] = 1000.01f;
		_database[3310] = 6400.32f;

		// add the wrapped functions as subprograms
		addSubprogram(new CLBankFunction("Check Balance", this, &CLBanking::checkBalance));
		addSubprogram(new CLBankFunction("Make Deposit", this, &CLBanking::deposit));
		addSubprogram(new CLBankFunction("Withdraw", this, &CLBanking::withdraw));
		addSubprogram(new CLBankFunction("Log Out", this, &CLBanking::logout));
	}

	void printHeader(std::ostream& out = std::cout) override {
		CLProgram::printHeader(out);
		if (isLoggedIn()) {
			out << "Account#: " << _acct << "\n";
		}
	}

	void run() override {
		printHeader();
		// prompt for login or exit
		while (!_shouldQuit) {
			login();
			// while logged in, prompt for options
			while (isLoggedIn() && !_shouldQuit) {
				prompt();
			}
		}

		// should exit so logout
		logout();

		// reset flag
		_shouldQuit = false;
	}

private:
	unsigned _acct = -1;
	float _balance = 0.00f;
	std::unordered_map<unsigned, float> _database;

	void checkBalance() {
		if (isLoggedIn()) {
			std::cout << "You currently have $" << _balance << " in your account\n";
		}
		else {
			std::cout << "You are not logged in\nPlease login to view your balance\n";
		}
	}

	void deposit() {
		if (isLoggedIn()) {
			std::cout << "Enter the amount to deposit: $";
			std::string input;
			float depositAmt = 0.00f;
			if (std::cin.peek() == '\n')
				std::getchar();
			std::getline(std::cin, input);
			try {
				depositAmt = std::stof(input);
				if (depositAmt < 0) {
					throw std::invalid_argument("Cannot deposit negative dollar amount");
				}
				_balance += depositAmt;
				std::cout << "Deposit successful\n";
				checkBalance();
			}
			catch (std::invalid_argument e) {
				std::cout << "Failed to deposit\nPlease enter a valid dollar amount\n";
			}
		}
		else {
			std::cout << "You are not logged in\nPlease login to make a deposit\n";
		}
	}

	void withdraw() {
		if (isLoggedIn()) {
			std::cout << "Enter the amount to withdraw: $";
			std::string input;
			float withdrawAmt = 0.00f;
			if (std::cin.peek() == '\n')
				std::getchar();
			std::getline(std::cin, input);
			try {
				withdrawAmt = std::stof(input);
				if (withdrawAmt > _balance) {
					std::cout << "Cannot withdraw an amount exceeding the current balance\n";
				}
				else if (withdrawAmt < 0) {
					throw std::invalid_argument("Cannot withdraw negative dollar amount");
				}
				else {
					_balance -= withdrawAmt;
					std::cout << "$" << withdrawAmt << " has been withdrawn\n";
					checkBalance();
				}
			}
			catch (std::invalid_argument e) {
				std::cout << "Failed to withdraw\nPlease enter a valid dollar amount\n";
			}
		}
		else {
			std::cout << "You are not logged in\nPlease login to make a withdrawal\n";
		}
	}

	void login() {
		std::cout << "Enter your account number or 0 to exit: ";
		std::string input;
		unsigned acctNum = 0;
		if (std::cin.peek() == '\n')
			std::getchar();
		std::getline(std::cin, input);
		try {
			acctNum = std::stoi(input);
			if (acctNum == 0) {
				_shouldQuit = true;
			}
			if (_database.find(acctNum) == _database.end())
				throw std::invalid_argument("Failed to login\nPlease enter a valid account number\n");
			_acct = acctNum;
			_balance = _database[_acct];
		}
		catch (std::invalid_argument e) {
			std::cout << "Failed to login\nPlease enter a valid account number\n";
		}
	}

	void logout() {
		if (isLoggedIn()) {
			// store changes
			_database[_acct] = _balance;
			_acct = -1;
			_balance = 0;
			std::cout << "You have logged out successfully\n";
		}
	}

private:

	bool isLoggedIn() {
		return _acct != -1;
	}

};

#endif