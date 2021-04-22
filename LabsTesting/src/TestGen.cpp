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

std::string TestGen::FindKeyword(int mod) {
	std::vector<Keyword>::iterator it;
	
	for (it = keywords.begin(); it != keywords.end(); it++) {
		if (it->mod == mod) {
			return it->str;
		}
	}
	//return "";
	std::cout << "ERROR: element not found [FindKeyword]\n";
	exit(1);
}


void TestGen::Correct(std::vector <PatternElement*>::iterator it) {
	ElementType type = (*it)->GetType();
	//ElementType type = pattern[index]->GetType();
	// TODO: switch ???

	// TODO: save original value of the pattern
	
	if (type == ElementType::KEYWORD) {
		int mod = (*it)->GetMod();		// enum CLASS ???
		if (mod == KEYWORD_DEF) {
			ssbuf_cor << FindKeyword(mod);

		}
		// ... return
		// TODO: ssbuf_cor, ssbuf_incor -> string -> file
	}
	else if (type == ElementType::SPACE) {
		
		// declare it somewhere
		int min_sp_num;
		int avrg_sp_num = 4;		// random
		int max_sp_num = 6;
		
		ElementType t = (*(it-1))->GetType();
		if (t == ElementType::KEYWORD) {
			min_sp_num = 1;		


		}


	}

	// TODO: restore original value of the pattern

	
	
}

void TestGen::Incorrect(std::vector <PatternElement*>::iterator it) {

}

void TestGen::Generate() {
	std::vector <PatternElement*>::iterator it;		// iterator
	for (it = pattern.begin(); it != pattern.end(); it++) {
	//for (size_t i = 0; i < pattern.size(); i++) {
		Correct(it);
		//Correct(i);
		Incorrect(it);
		//Incorrect(i);
	}

	// TODO: ssbuf_cor, ssbuf_incor -> string -> file

}

void TestGen::GenPattern() {
	// TODO: pattern generation Program -> Data Base ???
	if (lab_num == 1) {
		pattern.push_back(new ElemKeyword(KeywordType::KEYWORD_DEF));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemFuncName("main"));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemLeftBracket(BracketType::BRACKET_PAREN));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemRightBracket(BracketType::BRACKET_PAREN));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemNewLine());
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemKeyword(KeywordType::KEYWORD_RETURN));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemValue(ValueType::VALUE_INT));		// value as an argument

		std::cout << pattern[0]->GetMod();
	}
	else {
		std::cout << "ERROR: undefined lab number\n";
		exit(1);
	}
}

TestGen::TestGen(uint8_t lab_num)
	:
	lab_num(lab_num),
	keywords({ 
		{ KEYWORD_DEF, "def" },
		{ KEYWORD_RETURN, "return" }
		})		// ??? could be problems

	
{
	GenPattern();
}

TestGen::~TestGen(){

}