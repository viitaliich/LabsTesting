#include <fstream>
#include <iostream>
#include <random>

#include "TestGen.h"

#define FIRST_ASCII_LOW_LETTER 97
#define LAST_ASCII_LOW_LETTER 122
#define FIRST_ASCII_UP_LETTER 65
#define LAST_ASCII_UP_LETTER 90
#define FIRST_ASCII_NUMBER 48
#define LAST_ASCII_NUMBER 57
#define ASCII_ZERO 48
#define ASCII_ONE 49



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



void TestGen::PatternToText() {
	std::vector <PatternElement*>::iterator it;		
	for (it = pattern.begin(); it != pattern.end(); it++) {
		test += (*it)->GetValue();
	}
	correct_tests.push_back(test);
	test = "";
}

void TestGen::SpaceTestGen(const int space_num) {
	// space
	std::string val_sp(space_num, ' ');	// space as char

	(*it)->SetValue(val_sp);
	PatternToText();

	// tab
	std::string val_tab(space_num, '\t');	// space as char

	(*it)->SetValue(val_tab);
	PatternToText();
}

void TestGen::FuncNameTestGen(RuleName rule) {
	std::string val = "";

	std::default_random_engine generator;
	const int min_len = 1;
	const int max_len = 10;		// ???

	std::uniform_int_distribution<int> distribution(min_len, max_len);
	int len = distribution(generator);		// length of name

	switch (rule) {
	case RuleName::UPPER_CASE: {

		std::uniform_int_distribution<int> distribution(FIRST_ASCII_UP_LETTER, LAST_ASCII_UP_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		(*it)->SetValue(val);
		PatternToText();

		break;
	}

	case RuleName::LOWER_CASE: {

		std::uniform_int_distribution<int> distribution(FIRST_ASCII_LOW_LETTER, LAST_ASCII_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		(*it)->SetValue(val);
		PatternToText();

		break;
	}
	case RuleName::NUMBER: {

		std::uniform_int_distribution<int> distribution_one(FIRST_ASCII_LOW_LETTER, LAST_ASCII_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution_one(generator);		// append symbol to string
		}

		std::uniform_int_distribution<int> distribution_two(FIRST_ASCII_NUMBER, LAST_ASCII_NUMBER);
		val += distribution_two(generator);		// append number to string

		val += val;

		(*it)->SetValue(val);
		PatternToText();

		break;
	}
	case RuleName::UNDERSCORE: {

		std::uniform_int_distribution<int> distribution(FIRST_ASCII_LOW_LETTER, LAST_ASCII_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		val += "_";		// append underscore to string

		val += val;

		(*it)->SetValue(val);
		PatternToText();

		break;
	}
	default:
		// TODO
		break;
	}
}

void TestGen::Correct() {
	(*it)->SaveOrigElem();
	
	ElementType type = (*it)->GetType();

	if (type == ElementType::KEYWORD) {
		int mod = (*it)->GetMod();		// enum CLASS ???

		if (mod == KEYWORD_DEF) {
			// DO NOTHING
		}
		else if (mod == KEYWORD_RETURN) {
			// DO NOTHING
		}
	}
	else if (type == ElementType::SPACE) {
		// declare it somewhere
		int min_sp_num = 0;
		int rand_sp_num;		
		const int max_sp_num = 6;		// why 6 ???
		
		ElementType t = (*(it-1))->GetType();
		if (t == ElementType::KEYWORD || t == ElementType::NEW_LINE) {
			min_sp_num = 1;		
		}
		else if (t == ElementType::FUNC_NAME || 
				 t == ElementType::BRACKET || 
				 t == ElementType::COLON || 
				 t == ElementType::VALUE) {
			min_sp_num = 0;
		}

		// random
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(min_sp_num, max_sp_num);
		rand_sp_num = distribution(generator); 

		// generation
		SpaceTestGen(min_sp_num);
		SpaceTestGen(rand_sp_num);
		SpaceTestGen(max_sp_num);
	}
	else if (type == ElementType::FUNC_NAME) {
		// Currently only "main" supports	??? TODO
		FuncNameTestGen(RuleName::LOWER_CASE);
		FuncNameTestGen(RuleName::UPPER_CASE);
		FuncNameTestGen(RuleName::NUMBER);
		FuncNameTestGen(RuleName::UNDERSCORE);
	}
	else if (type == ElementType::BRACKET) {
		int mod = (*it)->GetMod();		// enum CLASS ???

		if (mod == BracketType::BRACKET_LPAREN) {
			// DO NOTHING
		}
		else if (mod == BracketType::BRACKET_RPAREN) {
			// DO NOTHING
		}
	}
	else if (type == ElementType::COLON) {
		// DO NOTHING
	}
	else if (type == ElementType::NEW_LINE) {
		// DO NOTHING
	}
	else if (type == ElementType::VALUE) {
		int mod = (*it)->GetMod();		// enum CLASS ???

		if (mod == ValueType::VALUE_INT_DEC) {
			
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(0, INT_MAX);
			int num = distribution(generator);
			
			std::string val = std::to_string(num);

			(*it)->SetValue(val);
			PatternToText();
		}
		else if (mod == ValueType::VALUE_INT_BIN) {
			
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(1, 28);
			int len = distribution(generator);

			std::string val = "0b0";
			for (int i = 0; i < len; i++) {
				std::uniform_int_distribution<int> dist(ASCII_ZERO, ASCII_ONE);		// is zero or/and one included in this range ???
				char sym = (char)dist(generator);
				val += sym;
			}

			(*it)->SetValue(val);
			PatternToText();
		}
		else if (mod == ValueType::VALUE_INT_OCT) {
			// TODO
		}
		else if (mod == ValueType::VALUE_INT_HEX) {
			// TODO
		}
		else if (mod == ValueType::VALUE_FLOAT) {
			// TODO
		}
		else if (mod == ValueType::VALUE_STR) {
			std::string val = "";
			const int len = 5;		// ???
			
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(FIRST_ASCII_LOW_LETTER, LAST_ASCII_LOW_LETTER);
			for (int i = 0; i <= len; i++) {
				val += distribution(generator);		// append symbol to string
			}

			(*it)->SetValue(val);
			PatternToText();
		}
	}

	(*it)->RestoreOrigElem();		// ???
}

void TestGen::Incorrect() {

}

void TestGen::Generate() {
	//std::vector <PatternElement*>::iterator it;		// iterator
	for (it = pattern.begin(); it != pattern.end(); it++) {
	//for (size_t i = 0; i < pattern.size(); i++) {
		Correct();
		//Correct(i);
		Incorrect();
		//Incorrect(i);
	}

	// TEMPORARY FOR TESTING PURPOSES
	// output correct_tests
	// to file
	std::ofstream file("./TESTFILE.txt");
	for (int i = 0; i < correct_tests.size(); i++) {
		file << "[" << i << "]\n";
		file << correct_tests[i];
		file << "\n";
	}
	file.close();

	//for (int i = 0; i < correct_tests.size(); i++) {
	//	std::cout << correct_tests[i] << std::endl;
	//}

	// TODO: ssbuf_cor, ssbuf_incor -> string -> file
}

void TestGen::GenPattern() {
	// TODO: pattern generation Program -> Data Base ???
	if (lab_num == 1) {
		pattern.push_back(new ElemKeyword(KeywordType::KEYWORD_DEF));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemFuncName("main"));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemLeftBracket(BracketType::BRACKET_LPAREN));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemRightBracket(BracketType::BRACKET_RPAREN));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemColon());
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemNewLine());
		pattern.push_back(new ElemSpace());		// ...
		pattern.push_back(new ElemKeyword(KeywordType::KEYWORD_RETURN));
		pattern.push_back(new ElemSpace());
		pattern.push_back(new ElemValue(ValueType::VALUE_INT_DEC));		// value as an argument
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