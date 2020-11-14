#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#include "TransitionRule.h"

class FiniteAutomata
{
public:
	FiniteAutomata(std::string inputFileName);
	~FiniteAutomata();

	void read();
	bool checkIfStateExists(std::string state);
	bool checkIfAlphabetSymbolExists(std::string symbol);
	bool checkIfInitialPositionExists(std::string state);
	bool checkIfFinalPositionExists(std::string state);

	/*
		def: looks into this->rules to see if any rule starts from the given state and has a transition with the given symbol
		in: state - should be an entry in this->states (std::string)
			symbol - should be an entry in this->alphabet (std::string)
		out: the result of the transition - if one is found
		     empty string - if no transition found
	*/
	std::string doTransition(std::string state, std::string symbol);

	/*
		def: returns the result of the transitions made from startState using the symbols from symbolSequence
		in: startState - should be a start state
			symbolSequence - the sequence of symbols used for transitions
		out: an end state - if the transitions result to one
			 empty string - if the input is wrong, or if the transition does not result in an end state
	*/
	std::string checkSequence(std::string startState, std::string symbolSequence);

	void printStates();
	void printAlphabet();
	void printInitialPositions();
	void printFinalPositions();
	void printRules();


	/*
		def:: reads the input and returns a vector of strings with the strings we want as result
		in:
			form - a string representing the input form from which we want to read. The strings we want to read appears as @ in form string (ex.: (@,@) - outputx the strings in the positions of the @'s from the input
			inptu - should contain the form string, which acts as some kinf od regex
		out:
			a vector of strings. First element represnts the frist @ and so on
					
	*/
	std::vector<std::string> readByForm(std::string form, std::string input);

private:
	void readStates();
	void readAlphabet();
	void readInitialPositions();
	void readFinalPositions();
	void readRules();

	void storePosition();
	void restorePosition();

	std::string inputFileName;
	std::ifstream inputFile;

	std::vector<std::string> states, alphabet, initialPositions, finalPositions;
	std::vector<TransitionRule*> rules;

	std::ifstream::streampos positionToKeep;
	bool needsRestore = false;
};