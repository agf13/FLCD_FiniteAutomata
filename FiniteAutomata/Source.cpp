#include <iostream>
#include <string>
#include <vector>

#include "FiniteAutomata.h"

using namespace std;

void displayHelp()
{
	string output = "";
	output += "1 - display states\n";
	output += "2 - display alphabet\n";
	output += "3 - display initial states\n";
	output += "4 - display final states\n";
	output += "5 - display rules\n";
	output += "6 - check dfa\n";
	output += "0 - close\n";
	

	cout << output;
}

void checkDfa(FiniteAutomata* fa)
{
	char startState_char[255], symbols_char[255];

	string startState;
	string symbols;

	cout << "start state: ";
	cin.getline(startState_char, 255);

	cout << "symbols: ";
	cin.getline(symbols_char, 255);

	startState = startState_char;
	symbols = symbols_char;

	string result = fa->checkSequence(startState, symbols);

	if (result != "")
	{
		cout << "Sequence accepted. Final state is: " + result + "\n";
	}
	else
	{
		cout<<"Sequence not accepted\n";
	}
}

int main()
{
	string fileName = "FA_input.txt";
	FiniteAutomata *fa = new FiniteAutomata{ fileName };
	fa->read();

	

	while (true)
	{
		cout << "\n";
		displayHelp();
		cout << "input: ";

		//read a line
		string line;
		char line_char[250];
		cin.getline(line_char,255);
		line = line_char;

		cout << "\n";

		if (line == "1")
			fa->printStates();
		else if (line == "2")
			fa->printAlphabet();
		else if (line == "3")
			fa->printInitialPositions();
		else if (line == "4")
			fa->printFinalPositions();
		else if (line == "5")
			fa->printRules();
		else if (line == "6")
			checkDfa(fa);
		else if (line == "exit" || line == "quit" || line == "-1" || line == "e" || line == "q" || line == "0")
			break;

			
	}

	delete fa;

	return 0;
}