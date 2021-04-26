#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "PatternElement.h"

struct Keyword {
	KeywordType mod;
	std::string str;
};

enum class LabNumber : uint8_t {
	LAB1 = 1
};

enum class RuleName : int {
	// 0 for combination of rules maybe
	UPPER_CASE = 1,
	LOWER_CASE,
	NUMBER,
	UNDERSCORE,

	CHANGE,
	ABSENT,
	CHECK_KEYWORD,
};

class TestGen
{
private:
	uint8_t lab_num;
	std::vector <PatternElement*> pattern;
	std::vector <PatternElement*>::iterator it;
	std::stringstream ssbuf_cor;
	std::stringstream ssbuf_incor;

	std::vector <Keyword> keywords;

	std::string test;
	std::vector <std::string> correct_tests;
	std::vector <std::string> incorrect_tests;

public:
	// TODO: output buffer for single test
	// TODO: output buffer for all tests

private:
	std::string ReadFile(const std::string& file);
	//void Correct(const size_t index);
	//void Incorrect(const size_t index);
	void Correct();
	void Incorrect();
	void GenPattern();

	void PatternToText();

	std::string FindKeyword(int mod);

	void KeywordTestGen(std::string value, RuleName rule);
	void SpaceTestGen(const int space_num);
	void FuncNameTestGen(RuleName rule);
	void IntDecTestGen();
	void IntBinTestGen();
	void IntOctTestGen();
	void IntHexTestGen();
	void FloatTestGen();
	void StringTestGen();

public:
	TestGen(uint8_t lab_num);
	~TestGen();
	
	void Generate();

};

