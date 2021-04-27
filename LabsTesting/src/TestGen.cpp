#include <fstream>
#include <iostream>
#include <random>

#include "TestGen.h"

#define ASCII_FIRST_LOW_LETTER 97
#define ASCII_LAST_LOW_LETTER 122
#define ASCII_FIRST_UP_LETTER 65
#define ASCII_LAST_UP_LETTER 90
#define ASCII_FIRST_NUMBER 48
#define ASCII_LAST_NUMBER 57
#define ASCII_0 48
#define ASCII_1 49
#define ASCII_7 55
#define ASCII_9 57
#define ASCII_A 65
#define ASCII_F 70
#define ASCII_EXCLAMATION 33
#define ASCII_SLASH 47



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
	std::vector <PatternElement*>::iterator iter;		
	for (iter = pattern.begin(); iter != pattern.end(); iter++) {
		test += (*iter)->GetValue();
	}
	correct_tests.push_back(test);
	test = "";
}

void TestGen::SpaceTestGen(const int space_num) {
	// TODO: add rules

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

		std::uniform_int_distribution<int> distribution(ASCII_FIRST_UP_LETTER, ASCII_LAST_UP_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		(*it)->SetValue(val);
		PatternToText();

		break;
	}

	case RuleName::LOWER_CASE: {

		std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		(*it)->SetValue(val);
		PatternToText();

		break;
	}
	case RuleName::ADD_NUMBER: {

		std::uniform_int_distribution<int> distribution_one(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution_one(generator);		// append symbol to string
		}

		std::uniform_int_distribution<int> distribution_two(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		val += distribution_two(generator);		// append number to string

		val += val;

		(*it)->SetValue(val);
		PatternToText();

		break;
	}
	case RuleName::ADD_UNDERSCORE: {

		std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		val += "_";		// append underscore to string

		val += val;

		(*it)->SetValue(val);
		PatternToText();

		break;
	}
	case RuleName::ABSENT: {
		(*it)->SetValue(val);
		PatternToText();
		break;
	}
	case RuleName::ADD_SPECIAL_SYM: {
		// TODO: not all symbols are taken into account
		val = (*it)->GetValue();
		
		std::uniform_int_distribution<int> distribution(ASCII_EXCLAMATION, ASCII_SLASH);
		val += (char)distribution(generator);		

		val += (*it)->GetValue();

		(*it)->SetValue(val);
		PatternToText();
		break;
	}
	case RuleName::TO_NUMBER: {
		std::uniform_int_distribution<int> distribution(0, INT_MAX);
		int num = distribution(generator);
		std::string val = std::to_string(num);

		(*it)->SetValue(val);
		PatternToText();
		break;
	}
	case RuleName::TO_KEYWORD: {
		// TODO ...
		break;
	}
	case RuleName::FIRST_NUMBER: {
		std::uniform_int_distribution<int> distribution(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		val += (char)distribution(generator);
		val += (*it)->GetValue();

		(*it)->SetValue(val);
		PatternToText();
		break;
	}

	default:
		// TODO
		break;
	}
}

void TestGen::BracketTestGen(RuleName rule) {
	int mod = (*it)->GetMod();
	std::string val = "";

	switch (rule)
	{
	case RuleName::ABSENT:		// TODO absent rule as separate function
		(*it)->SetValue(val);
		PatternToText();
		break;
	case RuleName::SUBSTITUTE:
		// TODO
		if (mod == BracketType::BRACKET_LPAREN) {
			// TODO
		}
		else if (mod == BracketType::BRACKET_RPAREN) {
			// TODO
		}
		// ...
		// TODO
		break;
	case RuleName::TO_NUMBER:
		// TODO
		// TODO to_char
		break;
	case RuleName::ADD_COUNT: {
		// TODO
		// ...

		// as spaces...
	}


	


	default:
		break;
	}



}

void TestGen::IntDecTestGen() {
	// TODO: add rules

	std::default_random_engine generator;		// TODO: make it single instance as static outside all scopes in this file
	std::uniform_int_distribution<int> distribution(0, INT_MAX);
	int num = distribution(generator);

	std::string val = std::to_string(num);

	(*it)->SetValue(val);
	PatternToText();
}
void TestGen::IntBinTestGen() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 28);
	int len = distribution(generator);

	std::string val = "0b0";
	for (int i = 0; i < len; i++) {
		std::uniform_int_distribution<int> dist(ASCII_0, ASCII_1);		// is zero or/and one included in this range ???
		char sym = (char)dist(generator);
		val += sym;
	}

	(*it)->SetValue(val);
	PatternToText();
}

void TestGen::IntOctTestGen() {
	// TODO: IN THIS VERSION OF MY PYTHON-ASM COMILER OCTALS ARE [0o...], NOT [0...] (0o11 / 011)

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 10);
	int len = distribution(generator);

	std::string val = "0o0";
	for (int i = 0; i < len; i++) {
		std::uniform_int_distribution<int> dist(ASCII_0, ASCII_7);		// is zero or/and one included in this range ???
		char sym = (char)dist(generator);
		val += sym;
	}

	(*it)->SetValue(val);
	PatternToText();
}

void TestGen::IntHexTestGen() {
	std::default_random_engine generator;
	// len 3 + 4 = 7
	std::uniform_int_distribution<int> distr_num(1, 3);
	std::uniform_int_distribution<int> distr_sym(1, 4);
	int len_num = distr_num(generator);
	int len_sym = distr_sym(generator);

	std::string val = "0x0";
	for (int i = 0; i < len_num; i++) {
		std::uniform_int_distribution<int> dist(ASCII_0, ASCII_9);
		char sym = (char)dist(generator);
		val += sym;
	}
	for (int i = 0; i < len_sym; i++) {
		std::uniform_int_distribution<int> dist(ASCII_A, ASCII_F);
		char sym = (char)dist(generator);
		val += sym;
	}

	(*it)->SetValue(val);
	PatternToText();
}

void TestGen::FloatTestGen() {
	// TODO: proper random float generation

	std::default_random_engine generator;
	std::uniform_int_distribution<int> dist_one(0, 10);
	std::uniform_int_distribution<int> dist_two(1, 100);
	int num_one = dist_one(generator);
	int num_two = dist_two(generator);

	std::string val = std::to_string(num_one);
	val += '.';
	val += std::to_string(num_two);

	(*it)->SetValue(val);
	PatternToText();
}

void TestGen::StringTestGen() {
	std::string val = "";
	const int len = 5;		// ???

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
	for (int i = 0; i <= len; i++) {
		val += distribution(generator);		// append symbol to string
	}

	(*it)->SetValue(val);
	PatternToText();
}

void TestGen::KeywordTestGen(std::string value, RuleName rule) {		// maybe do reference ???
	std::default_random_engine generator;
	std::string val = value;

	switch (rule)
	{
	case RuleName::UPPER_CASE: {
		std::transform(val.begin(), val.end(), val.begin(), ::toupper);		// TODO: use boost library here ???

		(*it)->SetValue(val);
		PatternToText();
		break;
	}
	
	case RuleName::ADD_NUMBER:
		// TODO: maybe
		break;
	case RuleName::ADD_UNDERSCORE:
		// TODO: maybe
		break;
	case RuleName::ADD_CHAR: {
		std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		val += (char)distribution(generator);
		
		(*it)->SetValue(val);
		PatternToText();
		break;
	}

	case RuleName::ABSENT: {
		val = "";
		
		(*it)->SetValue(val);
		PatternToText();
		break;
	}

	case RuleName::SUBSTITUTE:
		// TODO

		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}
	
	(*it)->SetValue(val);
	PatternToText();
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
		// declare it somewhere ???
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
		FuncNameTestGen(RuleName::ADD_NUMBER);
		FuncNameTestGen(RuleName::ADD_UNDERSCORE);
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
			
			IntDecTestGen();
			IntDecTestGen();

		}
		else if (mod == ValueType::VALUE_INT_BIN) {
			
			IntBinTestGen();
			IntBinTestGen();

		}
		else if (mod == ValueType::VALUE_INT_OCT) {
			IntOctTestGen();
			IntOctTestGen();
		}
		else if (mod == ValueType::VALUE_INT_HEX) {
			IntHexTestGen();
			IntHexTestGen();
		}
		else if (mod == ValueType::VALUE_FLOAT) {
			FloatTestGen();
			FloatTestGen();

		}
		else if (mod == ValueType::VALUE_STR) {
			StringTestGen();
			StringTestGen();
		}
	}

	(*it)->RestoreOrigElem();		
}

void TestGen::Incorrect() {
	(*it)->SaveOrigElem();

	ElementType type = (*it)->GetType();

	if (type == ElementType::KEYWORD) {
		int mod = (*it)->GetMod();		// enum CLASS ???

		if (mod == KEYWORD_DEF) {
			
			// TODO
			KeywordTestGen((*it)->GetValue(), RuleName::UPPER_CASE);
			KeywordTestGen((*it)->GetValue(), RuleName::ADD_CHAR);
			KeywordTestGen((*it)->GetValue(), RuleName::ABSENT);
			KeywordTestGen((*it)->GetValue(), RuleName::SUBSTITUTE);
			// ...

		}
		else if (mod == KEYWORD_RETURN) {
			// ...
		}
	}
	else if (type == ElementType::SPACE) {
		// TODO: make cosmetic enhancements ???

		ElementType t = (*(it - 1))->GetType();
		int m = (*(it - 1))->GetMod();
		if (t == ElementType::KEYWORD) {
			int min_sp_num = 0;
			SpaceTestGen(min_sp_num);
		}
		else if (t == ElementType::BRACKET && m == BRACKET_LPAREN) {
			// def main ( [name here] ). Incorrect test

			std::string val = "";
			std::default_random_engine generator;
			const int min_len = 1;
			const int max_len = 10;		// ???
			std::uniform_int_distribution<int> distribution(min_len, max_len);
			int len = distribution(generator);	
			std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
			for (int i = 0; i <= len; i++) {
				val += distribution(generator);		// append symbol to string
			}

			(*it)->SetValue(val);
			PatternToText();
		}
		// else DO NOTHING		???
	}
	else if (type == ElementType::FUNC_NAME) {
		// Currently only "main" supports	??? TODO

		FuncNameTestGen(RuleName::ABSENT);		
		FuncNameTestGen(RuleName::ADD_SPECIAL_SYM);
		FuncNameTestGen(RuleName::TO_NUMBER);
		FuncNameTestGen(RuleName::TO_KEYWORD);
		FuncNameTestGen(RuleName::FIRST_NUMBER);	// double it maybe ???
		//FuncNameTestGen(RuleName::FIRST_NUMBER);	// double it maybe ???

	}
	else if (type == ElementType::BRACKET) {
		BracketTestGen(RuleName::ABSENT);
x		

	}

	// TODO
	// ...

	(*it)->RestoreOrigElem();
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

		//pattern.push_back(new ElemValue(ValueType::VALUE_INT_DEC));		// value as an argument
		//pattern.push_back(new ElemValue(ValueType::VALUE_INT_BIN));		// value as an argument
		//pattern.push_back(new ElemValue(ValueType::VALUE_INT_OCT));		// value as an argument
		//pattern.push_back(new ElemValue(ValueType::VALUE_INT_HEX));		// value as an argument
		//pattern.push_back(new ElemValue(ValueType::VALUE_FLOAT));		// value as an argument
		//pattern.push_back(new ElemValue(ValueType::VALUE_STR));		// value as an argument

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
		}),		// ??? could be problems
	brackets({
		{ BRACKET_LPAREN, "(" },
		{ BRACKET_RPAREN, ")" },
		{ BRACKET_LSQUARE, "[" },
		{ BRACKET_RSQUARE, "]" },
		{ BRACKET_LBRACE, "{" },
		{ BRACKET_RBRACE, "}" },
		{ BRACKET_QUOTE, "\"" },
		{ BRACKET_SINGLE_QUOTE, "\'" },
		{ BRACKET_LANGLE, "<" },
		{ BRACKET_RANGLE, ">" },
		})

{
	GenPattern();
}

TestGen::~TestGen(){
}