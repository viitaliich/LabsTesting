#include <fstream>
#include <iostream>

#include "TestGen.h"

// TODO: not sure about realization ???
std::string TestGen::ReadFile(const std::string& path) {
	std::ifstream file(path);
	std::string content;
	content.assign((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	return content;
}

void TestGen::Correct() {

}

void TestGen::Incorrect() {

}

void TestGen::Generate() {
	Correct();
	Incorrect();
}

void TestGen::GenPattern() {
	if (lab_num == 1) {
		pattern.push_back(new ElemKeyword(KeywordType::KEYWORD_FUNC));
		pattern.push_back(new ElemSpace(SpaceType::SPACE_SPACE));
		pattern.push_back(new ElemFuncName());
		pattern.push_back(new ElemSpace(SpaceType::SPACE_SPACE));
		pattern.push_back(new ElemParentheses(ParanType::PARAN_PARENTHESES));
		pattern.push_back(new ElemSpace(SpaceType::SPACE_SPACE));
		pattern.push_back(new ElemParentheses(ParanType::PARAN_PARENTHESES));
		pattern.push_back(new ElemNewLine());
		pattern.push_back(new ElemSpace(SpaceType::SPACE_SPACE));
		pattern.push_back(new ElemKeyword(KeywordType::KEYWORD_RETURN));
		pattern.push_back(new ElemSpace(SpaceType::SPACE_SPACE));
		pattern.push_back(new ElemValue(ValueType::VALUE_INT));
	}
	else {
		std::cout << "ERROR: undefined lab number\n";
		exit(1);
	}
}

TestGen::TestGen(uint8_t lab_num)
	:
	lab_num(lab_num)
{
	GenPattern();
}

TestGen::~TestGen(){

}