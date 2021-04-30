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
	CORRECT_UPPER_CASE = 1,
	CORRECT_LOWER_CASE,
	CORRECT_ADD_NUMBER,
	CORRECT_ADD_UNDERSCORE,
	CORRECT_SPACES,
	CORRECT_ADD_CHAR,
	CORRECT_ABSENT,
	CORRECT_SUBSTITUTE,
	CORRECT_ADD_SPECIAL_SYM,
	CORRECT_TO_NUMBER,
	CORRECT_TO_KEYWORD,
	CORRECT_FIRST_NUMBER,
	CORRECT_ADD_COUNT,
	CORRECT_INT_DEC,
	CORRECT_INT_BIN,
	CORRECT_INT_OCT,
	CORRECT_INT_HEX,
	CORRECT_FLOAT,
	CORRECT_STR,

	INCORRECT_INT_DEC,
	INCORRECT_INT_BIN,
	INCORRECT_INT_OCT,
	INCORRECT_INT_HEX,
	INCORRECT_FLOAT,
	INCORRECT_STR,

	INCORRECT_UPPER_CASE,
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
	void IncorrectToText();

	std::string FindKeyword(int mod);

	void KeywordTestGen(std::string value, Rules rule);
	void SpaceTestGen(Rules rule, const int space_num);
	void FuncNameTestGen(Rules rule);
	void BracketTestGen(Rules rule);
	void ColonTestGen(Rules rule);
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

