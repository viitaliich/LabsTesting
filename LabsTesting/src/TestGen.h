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
	KeywordType mod;
	std::string str;
};
// ???
struct Bracket {
	BracketType mod;
	std::string str;
};

enum class LabNumber : uint8_t {
	LAB1 = 1
};

enum class RuleName : int {
	// 0 for combination of rules maybe
	UPPER_CASE = 1,
	LOWER_CASE,
	ADD_NUMBER,
	ADD_UNDERSCORE,

	ADD_CHAR,
	ABSENT,
	SUBSTITUTE,

	ADD_SPECIAL_SYM,
	TO_NUMBER,
	TO_KEYWORD,
	FIRST_NUMBER,
	ADD_COUNT,
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
	void PatternToText();

	std::string FindKeyword(int mod);

	void KeywordTestGen(std::string value, RuleName rule);
	void SpaceTestGen(const int space_num);
	void FuncNameTestGen(RuleName rule);
	void BracketTestGen(RuleName rule);
	void ColonTestGen(RuleName rule);
	void IntDecTestGen(RuleName rule);
	void IntBinTestGen(RuleName rule);
	void IntOctTestGen(RuleName rule);
	void IntHexTestGen(RuleName rule);
	void FloatTestGen(RuleName rule);
	void StringTestGen(RuleName rule);

public:
	TestGen(uint8_t lab_num /* variant*/);		// ???
	~TestGen();
	
	void Generate();

};

