#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "PatternElement.h"

struct Element {
	int8_t mod;
	std::string val;
};

// ???
struct Keyword {
	ModKeyword mod;
	std::string str;
};
// ???
struct Bracket {
	ModBracket mod;
	std::string str;
};

enum class LabNumber : uint8_t {
	LAB1 = 1
};

enum class Rules : uint8_t{
	// 0 for combination of rules maybe
	CORRECT_SPACES = 1,
	CORRECT_TO_NAME,
	CORRECT_ADD_NUM,
	CORRECT_ADD_UNDERSCORE,
	CORRECT_TO_UPPER_CASE,
	CORRECT_SUBSTITUTE_TYPE,
	CORRECT_SUBSTITUTE_NUMERAL_SYS,
	CORRECT_RANDOM_VAL,

	INCORRECT_ABSENT,
	INCORRECT_TO_UPPER_CASE,
	INCORRECT_SPACES,
	INCORRECT_FUNC_PARAMS,
	INCORRECT_ADD_NUM,
	INCORRECT_ADD_SPECIAL_SYM,
	INCORRECT_TO_NUMBER,
	INCORRECT_SUBSTITUTION,
	INCORRECT_WRONG_NUM,
	INCORRECT_SUBSTITUTE_TYPE,
	INCORRECT_SUBSTITUTE_NUMERAL_SYS,
	INCORRECT_TO_SPECIAL_SYM,
	INCORRECT_TO_KEYWORD,
	INCORRECT_TO_NAME,
};

enum class IncorrectRules : uint8_t {
	// 0 for combination of rules maybe
	INCORRECT_UPPER_CASE = 1,
	INCORRECT_LOWER_CASE,
	INCORRECT_ADD_NUMBER,
	INCORRECT_ADD_UNDERSCORE,
	INCORRECT_SPACES,

	INCORRECT_ADD_CHAR,
	INCORRECT_ABSENT,
	INCORRECT_SUBSTITUTE,

	INCORRECT_ADD_SPECIAL_SYM,
	INCORRECT_TO_NUMBER,
	INCORRECT_TO_KEYWORD,
	INCORRECT_FIRST_NUMBER,
	INCORRECT_ADD_COUNT,
};

class TestGen
{
private:
	uint8_t lab_num;
	std::vector <PatternElement*> pattern;
	std::vector <PatternElement*>::iterator it;

	// Do we need this ???
	std::stringstream ssbuf_cor;
	std::stringstream ssbuf_incor;

	std::vector <Element> keywords;		// Element -> Keyword if there are problems 
	std::vector <Element> brackets;		// Element -> Bracket if there are problems 

	std::string test;					// generated test
	std::vector <std::string> correct_tests;
	std::vector <std::string> incorrect_tests;

public:
	// TODO: output buffer for single test		???
	// TODO: output buffer for all tests		???

private:
	std::string ReadFile(const std::string& file);		// do we need this here ???
	void Correct();
	void Incorrect();

	void GenPattern();
	void CorrectToText();
	void CorrectToTextPV();		// ???
	void IncorrectToText();

	std::string FindKeyword(int mod);

	void KeywordTestGen(Rules rule);
	void SpaceTestGen(Rules rule, const int space_num);
	void NameTestGen(Rules rule);
	void BracketTestGen(Rules rule);
	void ColonTestGen(Rules rule);

	void ValueTestGen(std::vector<ElemValue*>::iterator, Rules rule);

	// ???
	void IntDecTestGen(Rules rule);
	void IntBinTestGen(Rules rule);
	void IntOctTestGen(Rules rule);
	void IntHexTestGen(Rules rule);
	void FloatTestGen(Rules rule);
	void StringTestGen(Rules rule);

public:
	TestGen(uint8_t lab_num /* variant*/);		// ???
	~TestGen();
	
	void Generate();

};

