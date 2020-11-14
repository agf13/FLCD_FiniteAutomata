#include "TransitionRule.h"

TransitionRule::TransitionRule(std::string state, std::string symbol)
{
	this->state = state;
	this->symbol = symbol;
	this->restultState = NON_DEFINED;
}

TransitionRule::TransitionRule(std::string state, std::string symbol, std::string resultState)
{
	this->state = state;
	this->symbol = symbol;
	this->restultState = resultState;
}

TransitionRule::~TransitionRule()
{
}

std::string TransitionRule::getState()
{
	return this->state;
}

std::string TransitionRule::getSymbol()
{
	return this->symbol;
}

std::string TransitionRule::getResultState()
{
	return this->restultState;
}
