#include <fstream>
#include <iostream>
#include <random>

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

void TestGen::SpaceTestGen(std::vector <PatternElement*>::iterator it, const int space_num){
	std::string val_sp(space_num, ' ');	// space as char
	(*it)->SetValue(val_sp);
	PatternToText();

	std::string val_tab(space_num, '\t');	// space as char
	(*it)->SetValue(val_tab);
	PatternToText();
}

void TestGen::PatternToText() {
	std::vector <PatternElement*>::iterator it;		
	for (it = pattern.begin(); it != pattern.end(); it++) {
		test += (*it)->GetValue();
	}
	tests.push_back(test);
	test = "";
}

void TestGen::Correct(std::vector <PatternElement*>::iterator it) {
	(*it)->SaveOrigElem();
	
	ElementType type = (*it)->GetType();

	if (type == ElementType::KEYWORD) {
		int mod = (*it)->GetMod();		// enum CLASS ???

		if (mod == KEYWORD_DEF) {
			// DO NOTHING

			//ssbuf_cor << FindKeyword(mod);
		}
		// TODO: return
	}
	else if (type == ElementType::SPACE) {
		// declare it somewhere
		int min_sp_num = 0;
		int rand_sp_num;		
		const int max_sp_num = 6;		// why 6 ???
		
		ElementType t = (*(it-1))->GetType();
		if (t == ElementType::KEYWORD) {
			min_sp_num = 1;		
		}

		// random
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(min_sp_num, max_sp_num);
		rand_sp_num = distribution(generator); 

		// generation
		SpaceTestGen(it, min_sp_num);
		SpaceTestGen(it, rand_sp_num);
		SpaceTestGen(it, max_sp_num);
	}

	(*it)->RestoreOrigElem();		// ???
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
	}
	else {
		std::cout << "ERROR: undefined lab number\n";
		exit(1);
	}
}

TestGen::TestGen(uint8_t lab_num)
	:
	lab_num(lab_num),
	test(""),
	keywords({ 
		{ KEYWORD_DEF, "def" },
		{ KEYWORD_RETURN, "return" }
		})		// ??? could be problems
	
{
	GenPattern();
}

TestGen::~TestGen(){
}