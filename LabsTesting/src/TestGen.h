#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "common.h"
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

enum class Rules : uint8_t {
	// 0 for combination of rules maybe
	CORRECT_SPACES = 1,
	CORRECT_MULT_NEWLINES,
	CORRECT_TO_NAME,
	CORRECT_ADD_NUM,
	CORRECT_ADD_UNDERSCORE,
	CORRECT_TO_UPPER_CASE,
	CORRECT_SUBSTITUTE_TYPE,
	CORRECT_SUBSTITUTE_NUMERAL_SYS,
	CORRECT_RANDOM_VAL,
	CORRECT_SUBSTITUTION,

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
	INCORRECT_NO_EXP,
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
	std::vector <PatternElement*> pattern;
	std::vector <PatternElement*>::iterator it;

	// Do we need this ???
	//std::stringstream ssbuf_cor;
	//std::stringstream ssbuf_incor;

	std::vector <Element> keywords;		// Element -> Keyword if there are problems 
	std::vector <Element> brackets;		// Element -> Bracket if there are problems 
	std::vector <Element> special_syms;
	std::vector <uint8_t> supported_types;
	std::vector<uint8_t>::iterator st_iter /*= supported_types.begin()*/;		// supported_types iter
	std::vector <uint8_t> unsupported_types;
	std::vector<uint8_t>::iterator ust_iter /*= unsupported_types.begin()*/;		// supported_types iter
	std::vector <uint8_t> supported_bases;		// bin, oct, hex, dec
	std::vector<uint8_t>::iterator sb_iter /*= supported_bases.begin()*/;		// supported_types iter
	std::vector <uint8_t> unsupported_bases;		// bin, oct, hex, dec
	std::vector<uint8_t>::iterator usb_iter /*= unsupported_bases.begin()*/;		// supported_types iter
	
	std::vector <Element> supported_un_ops;		
	std::vector <Element>::iterator suo_iter;		
	std::vector <Element> unsupported_un_ops;		
	std::vector <Element>::iterator usuo_iter;
	std::vector <Element> supported_bin_ops;
	std::vector <Element>::iterator sbo_iter;
	std::vector <Element> unsupported_bin_ops;
	std::vector <Element>::iterator usbo_iter;

	//std::vector <Element> operations;			// ???

	std::string test = "";					// generated test
	std::vector <std::string> correct_tests;
	std::vector <std::string> incorrect_tests;

	std::string random_name = "";

public:
	char* status = (char*)"---";
	char path_compiler[1024] = "---";
	char path_source[1024] = "---";
	char name[64] = "";
	char group[64] = "";
	int lab_num;
	int lab_var;
	int item_current_lab = 0;		// ??? for UI Combo box purposes
	int item_current_var = 0;		// ??? for UI Combo box purposes

	// for marking algorithm
	int tests_num = 0;				// whole number of tests
	int correct_tests_num = 0;		// tests that passed

	int max_mark;
	double percent;
	double mark = 0.0;

	// TODO: output buffer for single test		???
	// TODO: output buffer for all tests		???

private:
	std::string ReadFile(const std::string& file);		// do we need this here ???
	
	void Correct();
	void Incorrect();

	void GenPattern(); 
	void CorrectToText();
	//void CorrectToTextPV();		// ???
	void IncorrectToText();

	std::string FindKeyword(int mod);

	void KeywordTestGen(Rules rule);
	void SpaceTestGen(Rules rule, const int space_num);
	void NameTestGen(Rules rule);
	void BracketTestGen(Rules rule);
	void ColonTestGen(Rules rule);
	void ValueTestGen(std::vector<ElemValue*>::iterator, Rules rule);
	void OperationTestGen(Rules rule);

	// ???
	void IntDecTestGen(Rules rule);
	void IntBinTestGen(Rules rule);
	void IntOctTestGen(Rules rule);
	void IntHexTestGen(Rules rule);
	void FloatTestGen(Rules rule);
	void StringTestGen(Rules rule);

public:
	TestGen();
	~TestGen();
	
	void Generate();

};
