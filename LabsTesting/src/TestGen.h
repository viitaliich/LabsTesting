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

class TestGen
{
private:
	uint8_t lab_num;
	std::vector <PatternElement*> pattern;
	std::stringstream ssbuf_cor;
	std::stringstream ssbuf_incor;

	std::vector <Keyword> keywords;

	std::string test;
	std::vector <std::string> tests;

public:
	// TODO: output buffer for single test
	// TODO: output buffer for all tests

private:
	std::string ReadFile(const std::string& file);
	//void Correct(const size_t index);
	//void Incorrect(const size_t index);
	void Correct(std::vector <PatternElement*>::iterator it);
	void Incorrect(std::vector <PatternElement*>::iterator it);
	void GenPattern();

	void PatternToText();

	std::string FindKeyword(int mod);

	void SpaceTestGen(std::vector <PatternElement*>::iterator it, const int space_num);

public:
	TestGen(uint8_t lab_num);
	~TestGen();
	
	void Generate();

};

