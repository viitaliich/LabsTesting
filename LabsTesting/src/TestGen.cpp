#include <fstream>
#include <iostream>
//#include <random>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

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
	//std::vector<Keyword>::iterator it;
	std::vector<Element>::iterator it;
	
	for (it = keywords.begin(); it != keywords.end(); it++) {
		if (it->mod == mod) {
			return it->val;
		}
	}
	//return "";
	std::cout << "ERROR: element not found [FindKeyword]\n";
	exit(1);
}



void TestGen::CorrectToText() {
	std::vector <PatternElement*>::iterator iter;		
	for (iter = pattern.begin(); iter != pattern.end(); iter++) {
		test += (*iter)->GetValue();
	}
	correct_tests.push_back(test);
	test = "";
}

void TestGen::IncorrectToText() {
	std::vector <PatternElement*>::iterator iter;
	for (iter = pattern.begin(); iter != pattern.end(); iter++) {
		test += (*iter)->GetValue();
	}
	incorrect_tests.push_back(test);
	test = "";
}

void TestGen::SpaceTestGen(Rules rule, const int space_num) {
	// TODO: add rules CORRECT_SPACES, INCORRECT_SPACES

	// space
	std::string val_sp(space_num, ' ');	// space as char

	(*it)->SetValue(val_sp);
	if(rule == Rules::CORRECT_SPACES) CorrectToText();
	else IncorrectToText();

	// tab
	std::string val_tab(space_num, '\t');	// space as char

	(*it)->SetValue(val_tab);
	if (rule == Rules::CORRECT_SPACES) CorrectToText();
	else IncorrectToText();

}

void TestGen::FuncNameTestGen(Rules rule) {
	std::string val = "";

	//std::default_random_engine generator;
	boost::mt19937 generator;
	const int min_len = 1;
	const int max_len = 10;		// ???

	//std::uniform_int_distribution<int> distribution(min_len, max_len);
	//int len = distribution(generator);		// length of name
	boost::uniform_int<> distribution(min_len, max_len);
	int len = distribution(generator);

	switch (rule) {
	case Rules::CORRECT_UPPER_CASE: {
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_UP_LETTER, ASCII_LAST_UP_LETTER);
		boost::uniform_int<> distribution(ASCII_FIRST_UP_LETTER, ASCII_LAST_UP_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		(*it)->SetValue(val);
		CorrectToText();

		break;
	}

	case Rules::CORRECT_LOWER_CASE: {
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);

		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}
		(*it)->SetValue(val);
		CorrectToText();

		break;
	}
	case Rules::CORRECT_ADD_NUMBER: {
		boost::uniform_int<> distribution_one(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution_one(generator);		// append symbol to string
		}
		boost::uniform_int<> distribution_two(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		//std::uniform_int_distribution<int> distribution_two(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		val += distribution_two(generator);		// append number to string
		val += val;

		(*it)->SetValue(val);
		CorrectToText();

		break;
	}
	case Rules::CORRECT_ADD_UNDERSCORE: {
		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		val += "_";		// append underscore to string
		val += val;

		(*it)->SetValue(val);
		CorrectToText();

		break;
	}
	case Rules::INCORRECT_ABSENT: {
		(*it)->SetValue(val);
		CorrectToText();
		break;
	}
	case Rules::INCORRECT_ADD_SPECIAL_SYM: {
		// TODO: not all symbols are taken into account
		val = (*it)->GetValue();
		
		//std::uniform_int_distribution<int> distribution(ASCII_EXCLAMATION, ASCII_SLASH);
		boost::uniform_int<> distribution(ASCII_EXCLAMATION, ASCII_SLASH);
		val += (char)distribution(generator);		

		val += (*it)->GetValue();

		(*it)->SetValue(val);
		CorrectToText();
		break;
	}
	case Rules::INCORRECT_TO_NUMBER: {
		//std::uniform_int_distribution<int> distribution(0, INT_MAX);
		boost::uniform_int<> distribution(0, INT_MAX);
		int num = distribution(generator);
		std::string val = std::to_string(num);

		(*it)->SetValue(val);
		CorrectToText();
		break;
	}
	case Rules::INCORRECT_TO_KEYWORD: {
		// TODO ...
		break;
	}
	case Rules::INCORRECT_FIRST_NUMBER: {
		boost::uniform_int<> distribution(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		val += (char)distribution(generator);
		val += (*it)->GetValue();

		(*it)->SetValue(val);
		CorrectToText();
		break;
	}

	default:
		std::cout << "ERROR: something went wrong.\n";
		exit(1);
		break;
	}
}

void TestGen::BracketTestGen(Rules rule) {
	int mod = (*it)->GetMod();
	std::string val = "";

	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:		// TODO absent rule as separate function
		(*it)->SetValue(val);
		CorrectToText();
		break;
	case Rules::INCORRECT_SUBSTITUTE:		// substitute on left or right respectively or opposite
		// TODO
		if (mod == ModBracket::BRACKET_LPAREN) {
			// TODO
		}
		else if (mod == ModBracket::BRACKET_RPAREN) {
			// TODO
		}
		// ...
		// TODO
		break;
	case Rules::INCORRECT_TO_NUMBER:
		// TODO
		// TODO to_char
		break;
	case Rules::INCORRECT_ADD_COUNT: {  // TODO: also add it to CORRECT tests 
		// TODO
		// as spaces...
	}
	default:
		std::cout << "ERROR: something went wrong.\n";
		exit(1);
		break;
	}
}

void TestGen::ColonTestGen(Rules rule) {
	std::string val = "";
	
	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		CorrectToText();
		break;
	case Rules::INCORRECT_SUBSTITUTE:
		// TODO: other symbols
		val = ";";
		(*it)->SetValue(val);
		CorrectToText();
		break;
	//case RuleName::TO_CHAR:
		// TODO
		// TODO to_char
		// ???
		//break;
	default:
		std::cout << "ERROR: something went wrong.\n";
		exit(1);
		break;
	}
}

void TestGen::IntDecTestGen(Rules rule) {
	// TODO: add rules correctly
	std::string val;
	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		val = "";
		(*it)->SetValue(val);
		CorrectToText();
		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}

	//std::default_random_engine generator;		// TODO: make it single instance as static outside all scopes in this file
	//std::uniform_int_distribution<int> distribution(0, INT_MAX);
	//int num = distribution(generator);

	boost::mt19937 generator;
	boost::uniform_int<> distribution(0, INT_MAX);
	int num = distribution(generator);

	val = std::to_string(num);

	(*it)->SetValue(val);
	CorrectToText();
}
void TestGen::IntBinTestGen(Rules rule) {
	// TODO: add rules correctly
	std::string val;
	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		val = "";
		(*it)->SetValue(val);
		CorrectToText();
		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}

	//std::default_random_engine generator;
	//std::uniform_int_distribution<int> distribution(1, 28);
	//int len = distribution(generator);

	boost::mt19937 generator;
	boost::uniform_int<> distribution(1, 28);
	int len = distribution(generator);

	val = "0b0";
	for (int i = 0; i < len; i++) {
		//std::uniform_int_distribution<int> dist(ASCII_0, ASCII_1);		// is zero or/and one included in this range ???
		boost::uniform_int<> dist(ASCII_0, ASCII_1);		// is zero or/and one included in this range ???
		char sym = (char)dist(generator);
		val += sym;
	}

	(*it)->SetValue(val);
	CorrectToText();
}

void TestGen::IntOctTestGen(Rules rule) {
	// TODO: IN THIS VERSION OF MY PYTHON-ASM COMILER OCTALS ARE [0o...], NOT [0...] (0o11 / 011)

		// TODO: add rules correctly
	std::string val;
	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		CorrectToText();
		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}

	//std::default_random_engine generator;
	//std::uniform_int_distribution<int> distribution(1, 10);
	//int len = distribution(generator);

	boost::mt19937 generator;
	boost::uniform_int<> distribution(1, 10);
	int len = distribution(generator);

	val = "0o0";
	for (int i = 0; i < len; i++) {
		boost::uniform_int<> dist(ASCII_0, ASCII_7);		// is zero or/and one included in this range ???
		//std::uniform_int_distribution<int> dist(ASCII_0, ASCII_7);		// is zero or/and one included in this range ???
		char sym = (char)dist(generator);
		val += sym;
	}

	(*it)->SetValue(val);
	CorrectToText();
}

void TestGen::IntHexTestGen(Rules rule) {

	// TODO: add rules correctly
	std::string val;
	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		CorrectToText();
		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}

	//std::default_random_engine generator;

	boost::mt19937 generator;
	// len 3 + 4 = 7
	boost::uniform_int<> distr_num(1, 3);
	//std::uniform_int_distribution<int> distr_num(1, 3);
	boost::uniform_int<> distr_sym(1, 4);
	//std::uniform_int_distribution<int> distr_sym(1, 4);
	int len_num = distr_num(generator);
	int len_sym = distr_sym(generator);

	val = "0x0";
	for (int i = 0; i < len_num; i++) {
		boost::uniform_int<> dist(ASCII_0, ASCII_9);
		//std::uniform_int_distribution<int> dist(ASCII_0, ASCII_9);
		char sym = (char)dist(generator);
		val += sym;
	}
	for (int i = 0; i < len_sym; i++) {
		boost::uniform_int<> dist(ASCII_A, ASCII_F);
		//std::uniform_int_distribution<int> dist(ASCII_A, ASCII_F);
		char sym = (char)dist(generator);
		val += sym;
	}

	(*it)->SetValue(val);
	CorrectToText();
}

void TestGen::FloatTestGen(Rules rule) {
	// TODO: proper random float generation

		// TODO: add rules correctly
	std::string val;
	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		CorrectToText();
		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}

	//std::default_random_engine generator;
	//std::uniform_int_distribution<int> dist_one(0, 10);
	//std::uniform_int_distribution<int> dist_two(1, 100);
	//int num_one = dist_one(generator);
	//int num_two = dist_two(generator);

	boost::mt19937 generator;
	boost::uniform_int<> distribution_one(0, 10);
	boost::uniform_int<> distribution_two(1, 100);
	int num_one= distribution_one(generator);
	int num_two = distribution_two(generator);

	val = std::to_string(num_one);
	val += '.';
	val += std::to_string(num_two);

	(*it)->SetValue(val);
	CorrectToText();
}

void TestGen::StringTestGen(Rules rule) {

	// TODO: add rules correctly
	std::string val = "";
	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		CorrectToText();
		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}

	//std::string val = "";
	const int len = 5;		// ???

	//std::default_random_engine generator;
	//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);

	boost::mt19937 generator;
	boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
	for (int i = 0; i <= len; i++) {
		val += distribution(generator);		// append symbol to string
	}

	(*it)->SetValue(val);
	CorrectToText();
}

void TestGen::KeywordTestGen(std::string value, Rules rule) {		// maybe do reference ???		get value before call ???


	//std::default_random_engine generator;
	boost::mt19937 generator;

	std::string val = value;

	switch (rule)
	{
	case Rules::INCORRECT_UPPER_CASE: {
		std::transform(val.begin(), val.end(), val.begin(), ::toupper);		// TODO: use boost library here ???

		(*it)->SetValue(val);
		CorrectToText();
		break;
	}
	
	case Rules::INCORRECT_ADD_NUMBER:
		// TODO: maybe
		break;
	case Rules::INCORRECT_ADD_UNDERSCORE:
		// TODO: maybe
		break;
	case Rules::INCORRECT_ADD_CHAR: {
		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		val += (char)distribution(generator);
		
		(*it)->SetValue(val);
		CorrectToText();
		break;
	}

	case Rules::INCORRECT_ABSENT: {
		val = "";
		
		(*it)->SetValue(val);
		CorrectToText();
		break;
	}

	case Rules::INCORRECT_SUBSTITUTE:
		// TODO

		break;
	default:
		std::cout << "ERROR: something went wrong\n";
		exit(1);
		break;
	}
	
	(*it)->SetValue(val);
	CorrectToText();
}

void TestGen::Correct() {
	(*it)->SaveOrigElem();

	ElementType type = (*it)->GetType();

	switch (type)
	{
	case ElementType::TYPE_KEYWORD: {

		uint8_t mod = (*it)->GetMod();

		switch (mod)
		{
		case KEYWORD_DEF:
			// DO NOTHING
			break;
		case KEYWORD_RETURN:
			// DO NOTHING
			break;
		default:
			std::cout << "ERROR: keyword mod error\n";
			exit(1);
			break;
		}
		break;
	}
	case ElementType::TYPE_SPACE: {
		// declare it somewhere ???
		int min_sp_num = 0;
		int rand_sp_num;
		const int max_sp_num = 6;		// why 6 ???

		ElementType t = (*(it - 1))->GetType();
		if (t == ElementType::TYPE_KEYWORD || t == ElementType::TYPE_NEW_LINE) {
			min_sp_num = 1;
		}
		else if (t == ElementType::TYPE_NAME ||
			t == ElementType::TYPE_BRACKET ||
			t == ElementType::TYPE_COLON ||
			t == ElementType::TYPE_VALUE) {
			min_sp_num = 0;
		}

		// random
		boost::mt19937 generator;
		boost::uniform_int<> distribution(min_sp_num, max_sp_num);
		rand_sp_num = distribution(generator);

		//std::default_random_engine generator;
		//std::uniform_int_distribution<int> distribution(min_sp_num, max_sp_num);
		//rand_sp_num = distribution(generator);

		// generation
		SpaceTestGen(Rules::CORRECT_SPACES, min_sp_num);
		SpaceTestGen(Rules::CORRECT_SPACES, rand_sp_num);
		SpaceTestGen(Rules::CORRECT_SPACES, max_sp_num);
		break;

	}
	case ElementType::TYPE_NAME: {
		// Currently only "main" supports	??? TODO
		FuncNameTestGen(Rules::CORRECT_LOWER_CASE);
		FuncNameTestGen(Rules::CORRECT_UPPER_CASE);
		FuncNameTestGen(Rules::CORRECT_ADD_NUMBER);
		FuncNameTestGen(Rules::CORRECT_ADD_UNDERSCORE);
		break;

	}
	case ElementType::TYPE_BRACKET: {
		int mod = (*it)->GetMod();		

		if (mod == ModBracket::BRACKET_LPAREN) {
			// DO NOTHING
		}
		else if (mod == ModBracket::BRACKET_RPAREN) {
			// DO NOTHING
		}
		break;

	}
	case ElementType::TYPE_COLON: {
		// DO NOTHING
		break;

	}
	case ElementType::TYPE_NEW_LINE: {
		// DO NOTHING
		break;

	}
	case ElementType::TYPE_VALUE: {
		int mod = (*it)->GetMod();		// enum CLASS ???

		if (mod == ModValue::VALUE_INT_DEC) {

			IntDecTestGen(Rules::CORRECT_INT_DEC);	// rule
			IntDecTestGen(Rules::CORRECT_INT_DEC);

		}
		else if (mod == ModValue::VALUE_INT_BIN) {

			IntBinTestGen(Rules::CORRECT_INT_BIN);
			IntBinTestGen(Rules::CORRECT_INT_BIN);

		}
		else if (mod == ModValue::VALUE_INT_OCT) {
			IntOctTestGen(Rules::CORRECT_INT_OCT);
			IntOctTestGen(Rules::CORRECT_INT_OCT);
		}
		else if (mod == ModValue::VALUE_INT_HEX) {
			IntHexTestGen(Rules::CORRECT_INT_HEX);
			IntHexTestGen(Rules::CORRECT_INT_HEX);
		}
		else if (mod == ModValue::VALUE_FLOAT) {
			FloatTestGen(Rules::CORRECT_FLOAT);
			FloatTestGen(Rules::CORRECT_FLOAT);

		}
		else if (mod == ModValue::VALUE_STR) {
			StringTestGen(Rules::CORRECT_STR);
			StringTestGen(Rules::CORRECT_STR);
		}
		break;

	}
	default:
		std::cout << "ERROR: correct test error\n";
		exit(1);
	}
	(*it)->RestoreOrigElem();
}

void TestGen::Incorrect() {
	(*it)->SaveOrigElem();

	ElementType type = (*it)->GetType();

	switch (type) {
	case ElementType::TYPE_KEYWORD: {
		int mod = (*it)->GetMod();		// enum CLASS ???

		if (mod == KEYWORD_DEF) {

			// TODO
			KeywordTestGen((*it)->GetValue(), Rules::INCORRECT_UPPER_CASE);
			KeywordTestGen((*it)->GetValue(), Rules::INCORRECT_ADD_CHAR);
			KeywordTestGen((*it)->GetValue(), Rules::INCORRECT_ABSENT);
			KeywordTestGen((*it)->GetValue(), Rules::INCORRECT_SUBSTITUTE);
			// ...

		}
		else if (mod == KEYWORD_RETURN) {
			// ...
		}
		break;
	}
	case ElementType::TYPE_SPACE: {
		// TODO: make cosmetic enhancements ???

		ElementType t = (*(it - 1))->GetType();
		int m = (*(it - 1))->GetMod();
		if (t == ElementType::TYPE_KEYWORD) {
			int min_sp_num = 0;
			SpaceTestGen(Rules::INCORRECT_SPACES, min_sp_num);
		}
		else if (t == ElementType::TYPE_BRACKET && m == BRACKET_LPAREN) {
			// def main ( [name here] ). Incorrect test

			std::string val = "";
			boost::mt19937 generator;
			const int min_len = 1;
			const int max_len = 10;		// ???
			boost::uniform_int<> distribution_len(min_len, max_len);
			int len = distribution_len(generator);
			boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
			//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
			for (int i = 0; i <= len; i++) {
				val += distribution(generator);		// append symbol to string
			}

			(*it)->SetValue(val);
			CorrectToText();
		}
		// else DO NOTHING		???
		break;

	}
	case ElementType::TYPE_NAME : {
		// Currently only "main" supports	??? TODO

		FuncNameTestGen(Rules::INCORRECT_ABSENT);
		FuncNameTestGen(Rules::INCORRECT_ADD_SPECIAL_SYM);
		FuncNameTestGen(Rules::INCORRECT_TO_NUMBER);
		FuncNameTestGen(Rules::INCORRECT_TO_KEYWORD);
		FuncNameTestGen(Rules::INCORRECT_FIRST_NUMBER);	// double it maybe ???
		//FuncNameTestGen(RuleName::FIRST_NUMBER);	// double it maybe ???

		break;

	}
	case ElementType::TYPE_BRACKET: {
		BracketTestGen(Rules::INCORRECT_ABSENT);
		break;

	}
	case ElementType::TYPE_COLON: {
		ColonTestGen(Rules::INCORRECT_ABSENT);
		ColonTestGen(Rules::INCORRECT_SUBSTITUTE);
		//ColonTestGen(RuleName::...);
		break;

	}
	case ElementType::TYPE_NEW_LINE: {
		std::string val = " ";
		(*it)->SetValue(val);
		CorrectToText();
		break;

	}
	case ElementType::TYPE_VALUE: {
		int mod = (*it)->GetMod();

		if (mod == ModValue::VALUE_INT_DEC) {

			IntDecTestGen(Rules::INCORRECT_INT_DEC);	// rule
			IntDecTestGen(Rules::INCORRECT_INT_DEC);

		}
		else if (mod == ModValue::VALUE_INT_BIN) {

			IntBinTestGen(Rules::INCORRECT_INT_BIN);
			IntBinTestGen(Rules::INCORRECT_INT_BIN);

		}
		else if (mod == ModValue::VALUE_INT_OCT) {
			IntOctTestGen(Rules::INCORRECT_INT_OCT);
			IntOctTestGen(Rules::INCORRECT_INT_OCT);
		}
		else if (mod == ModValue::VALUE_INT_HEX) {
			IntHexTestGen(Rules::INCORRECT_INT_HEX);
			IntHexTestGen(Rules::INCORRECT_INT_HEX);
		}
		else if (mod == ModValue::VALUE_FLOAT) {
			FloatTestGen(Rules::INCORRECT_FLOAT);
			FloatTestGen(Rules::INCORRECT_FLOAT);

		}
		else if (mod == ModValue::VALUE_STR) {
			StringTestGen(Rules::INCORRECT_STR);
			StringTestGen(Rules::INCORRECT_STR);
		}
		break;

	}
	default:
		std::cout << "ERROR: incorrect gen type\n";
		exit(1);
		break;
		// TODO
		// ...
	}
	
	(*it)->RestoreOrigElem();
}

void TestGen::Generate() {
	for (it = pattern.begin(); it != pattern.end(); it++) {
		Correct();
		Incorrect();
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

	// TODO: ssbuf_cor, ssbuf_incor -> string -> file
}

void TestGen::GenPattern() {
	// TODO: pattern generation Program -> Data Base ???
	switch (lab_num)
	{
	case 1: {
		pattern = {
			// instead of push_back
			new ElemKeyword(ModKeyword::KEYWORD_DEF),
			new ElemSpace(),
			new ElemName("main"),
			new ElemSpace(),
			new ElemLeftBracket(ModBracket::BRACKET_LPAREN),
			new ElemSpace(),
			new ElemRightBracket(ModBracket::BRACKET_RPAREN),
			new ElemSpace(),
			new ElemColon(),
			new ElemSpace(),
			new ElemNewLine(),
			new ElemSpace(),		// ...
			new ElemKeyword(ModKeyword::KEYWORD_RETURN),
			new ElemSpace(),
			new ElemValue(ModValue::VALUE_INT_DEC)		// value as an argument
		};
		break;
	}
	default:
		std::cout << "ERROR: undefined lab number\n";
		exit(1);
		break;
	}
	
		//pattern.push_back(new ElemValue(ModValue::VALUE_INT_DEC));		// value as an argument
		//pattern.push_back(new ElemValue(ModValue::VALUE_INT_BIN));		// value as an argument
		//pattern.push_back(new ElemValue(ModValue::VALUE_INT_OCT));		// value as an argument
		//pattern.push_back(new ElemValue(ModValue::VALUE_INT_HEX));		// value as an argument
		//pattern.push_back(new ElemValue(ModValue::VALUE_FLOAT));		// value as an argument
		//pattern.push_back(new ElemValue(ModValue::VALUE_STR));		// value as an argument
}

TestGen::TestGen(uint8_t lab_num)
	:
	lab_num(lab_num),
	test(""),		// generated test
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