#pragma once

#define NON_DEFINED '_'

#include <string>

class TransitionRule
{
public:
	TransitionRule(std::string state, std::string sequence);
	TransitionRule(std::string state, std::string symbol, std::string resultState);
	~TransitionRule();

	std::string getState();
	std::string getSymbol();
	std::string getResultState();

private:
	std::string state;
	std::string symbol;

	std::string restultState;
};

