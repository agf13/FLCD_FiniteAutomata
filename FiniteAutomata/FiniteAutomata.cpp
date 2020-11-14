#include "FiniteAutomata.h"

FiniteAutomata::FiniteAutomata(std::string inputFileName)
{
	this->inputFileName = inputFileName;
}

FiniteAutomata::~FiniteAutomata()
{
	if (this->inputFile.is_open())
	{
		this->inputFile.close();
	}

	for (unsigned int i = 0; i < this->rules.size(); i++)
	{
		delete this->rules[i];
	}
}

void FiniteAutomata::read()
{
	this->inputFile.open(this->inputFileName);
	if (this->inputFile.is_open() == false)
	{
		std::cout << "\tError opening input file!\n";
		return;
	}
	this->readStates();
	this->readAlphabet();
	this->readInitialPositions();
	this->readFinalPositions();
	this->readRules();
}

bool FiniteAutomata::checkIfStateExists(std::string state)
{
	for (unsigned int i = 0; i < this->states.size(); i++)
	{
		if (this->states[i] == state)
			return true;
	}
	return false;
}

bool FiniteAutomata::checkIfAlphabetSymbolExists(std::string symbol)
{
	for (unsigned int i = 0; i < this->alphabet.size(); i++)
	{
		if (this->alphabet[i] == symbol)
			return true;
	}
	return false;
}

bool FiniteAutomata::checkIfInitialPositionExists(std::string state)
{
	for (unsigned int i = 0; i < this->initialPositions.size(); i++)
	{
		if (this->initialPositions[i] == state)
			return true;
	}
	return false;
}

bool FiniteAutomata::checkIfFinalPositionExists(std::string state)
{
	for (unsigned int i = 0; i < this->finalPositions.size(); i++)
	{
		if (this->finalPositions[i] == state)
			return true;
	}
	return false;
}

std::string FiniteAutomata::checkSequence(std::string startState, std::string symbolSequence)
{
	if (checkIfFinalPositionExists(startState) == false)
		return "";

	std::string currState = startState;

	std::istringstream stringStream(symbolSequence);
	std::string token;
	while (std::getline(stringStream, token, ' '))
	{
		currState = this->doTransition(currState, token);
		if (currState == "")
			return currState;
	}
	if (this->checkIfFinalPositionExists(currState) == true)
		return currState;

	return "";
}

void FiniteAutomata::printStates()
{
	std::string output;
	for (unsigned int i = 0; i < this->states.size(); i++)
	{
		output += this->states[i] + " ";
	}
	std::cout << output << "\n";
}

void FiniteAutomata::printAlphabet()
{
	std::string output;
	for (unsigned int i = 0; i < this->alphabet.size(); i++)
	{
		output += this->alphabet[i] + " ";
	}
	std::cout << output << "\n";
}

void FiniteAutomata::printInitialPositions()
{
	std::string output;
	for (unsigned int i = 0; i < this->initialPositions.size(); i++)
	{
		output += this->initialPositions[i] + " ";
	}
	std::cout << output << "\n";
}

void FiniteAutomata::printFinalPositions()
{
	std::string output;
	for (unsigned int i = 0; i < this->finalPositions.size(); i++)
	{
		output += this->finalPositions[i] + " ";
	}
	std::cout << output << "\n";
}

void FiniteAutomata::printRules()
{
	std::string output = "";
	for (unsigned int i = 0; i < this->rules.size(); i++) 
	{
		output += this->rules[i]->getState() + " " + this->rules[i]->getSymbol() + " " + this->rules[i]->getResultState() + "\n";
	}
	std::cout << output;
}

std::string FiniteAutomata::doTransition(std::string state, std::string symbol)
{
	for (unsigned int i = 0; i < this->rules.size(); i++)
	{
		if (state == this->rules[i]->getState())
		{
			if (symbol == this->rules[i]->getSymbol())
			{
				return this->rules[i]->getResultState();
			}
		}
	}
	return "";
}

std::vector<std::string> FiniteAutomata::readByForm(std::string form, std::string input)
{
	std::vector<std::string> result;

	unsigned int indexForm = 0;
	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (form[indexForm] == '@')
		{
			int startIndex = i;
			int nextFormCharacter = ' ';
			indexForm++;
			if (indexForm < form.size())
			{
				nextFormCharacter = form[indexForm];
			}
			while (i<input.size() && input[i] != nextFormCharacter) i++;
			result.push_back(input.substr(startIndex, i-startIndex));
		}
		if (input[i] == form[indexForm])
		{
			indexForm++;
		}
		if (indexForm == form.size())
		{
			i = input.size();
		}
	}

	return result;
}

void FiniteAutomata::readStates()
{
	//store current position
	this->storePosition();

	//read a line
	std::string line;
	std::getline(this->inputFile, line);

	//skip the part until the "=", so that we know from where our reading of states starts
	int index = 0;
	while (line[index] != '=')index++;
	index++;
	line = line.substr(index);

	//read the states
	std::istringstream lineStream(line);
	std::string token;
	while (getline(lineStream, token, '|'))
	{
		if (token.empty() == false &&  token != " " && this->checkIfStateExists(token) == false)
		{
			this->states.push_back(token);
		}
	}
}

void FiniteAutomata::readAlphabet()
{	
	//store current position
	this->storePosition();

	//read a line
	std::string line;
	std::getline(this->inputFile, line);

	//skip the part until the "=", so that we know from where our reading of states starts
	int index = 0;
	while (line[index] != '=')index++;
	index++;
	line = line.substr(index);

	//read the states
	std::istringstream lineStream(line);
	std::string token;
	while (getline(lineStream, token, '|'))
	{
		if (token.empty() == false && this->checkIfAlphabetSymbolExists(token) == false)
		{
			this->alphabet.push_back(token);
		}
	}
}

void FiniteAutomata::readInitialPositions()
{
	//store current position
	this->storePosition();

	//read a line
	std::string line;
	std::getline(this->inputFile, line);

	//skip the part until the "=", so that we know from where our reading of states starts
	int index = 0;
	while (line[index] != '=')index++;
	index++;
	line = line.substr(index);

	//read the states
	std::istringstream lineStream(line);
	std::string token;
	while (getline(lineStream, token, '|'))
	{
		if (token.empty() == false && this->checkIfFinalPositionExists(token) == false && this->checkIfStateExists(token) == true)
		{
			this->initialPositions.push_back(token);
		}
	}
}

void FiniteAutomata::readFinalPositions()
{
	//store current position
	this->storePosition();

	//read a line
	std::string line;
	std::getline(this->inputFile, line);

	//skip the part until the "=", so that we know from where our reading of states starts
	int index = 0;
	while (line[index] != '=')index++;
	index++;
	line = line.substr(index);

	//read the states
	std::istringstream lineStream(line);
	std::string token;
	while (getline(lineStream, token, '|'))
	{
		if (token.empty() == false && this->checkIfFinalPositionExists(token) == false && checkIfStateExists(token) == true)
		{
			this->finalPositions.push_back(token);
		}
	}
}

void FiniteAutomata::readRules()
{
	//store current position
	this->storePosition();

	//read a line
	std::string line;
	std::getline(this->inputFile, line);

	//skip the part until the "=", so that we know from where our reading of states starts
	int index = 0;
	while (line[index] != '=')index++;
	index++;
	line = line.substr(index);

	do
	{
		//read the states
		std::istringstream lineStream(line);
		std::string token;

		std::vector<std::string> rezult = this->readByForm("(@, @) -> @", line);
		std::string curState = rezult[0];
		std::string alph = rezult[1];
		std::string stateRez = rezult[2];

		TransitionRule* newRule = new TransitionRule{ curState, alph, stateRez };
		this->rules.push_back(newRule);
	} while (getline(this->inputFile, line));
}

void FiniteAutomata::storePosition()
{
	if (this->inputFile.is_open())
	{
		this->positionToKeep = this->inputFile.tellg();
	}
	else
	{
		this->positionToKeep = -1;
	}
}

void FiniteAutomata::restorePosition()
{
	if (this->inputFile.is_open() && this->positionToKeep != -1)
	{
		this->inputFile.seekg(this->positionToKeep);
	}
}

