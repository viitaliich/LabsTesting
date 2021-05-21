// TODO: ABSENT as separate function

#include <fstream>
#include <iostream>
//#include <random>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/lexical_cast.hpp"

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
//#define ASCII_EXCLAMATION 33
//#define ASCII_SLASH 47

std::string get_same_type_val(std::vector <Element>& vec, uint8_t mod) {
	std::string val = "";
	Element* elem = &(vec.front());		// do we need <&> here	???
	if (elem->mod == mod || mod == 0) {
		vec.push_back(vec.front());
		vec.erase(vec.begin());
		val = vec.front().val;
	}
	else {
		val = elem->val;
	}
	return val;
}

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


void TestGen::KeywordTestGen(Rules rule) {

	(*it)->SaveOrigElem();

	//std::default_random_engine generator;
	boost::mt19937 generator;

	std::string val = (*it)->GetValue();
	uint8_t m;

	switch (rule)
	{

	case Rules::INCORRECT_TO_UPPER_CASE: {
		boost::to_upper(val);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}

	case Rules::INCORRECT_TO_NAME: {
		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		val += (char)distribution(generator);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}

	case Rules::INCORRECT_ABSENT: {
		val = "";

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}

	case Rules::INCORRECT_SUBSTITUTION:
		m = (*it)->GetMod();
		val = get_same_type_val(keywords, m);
		// ...
		/*Element* elem = &(keywords.front());
		if (elem->mod == m) {
			keywords.push_back(keywords.front());
			keywords.erase(keywords.begin());
			val = keywords.front().val;
		}
		else {
			val = elem->val;
		}*/
		(*it)->SetValue(val);
		IncorrectToText();
		break;

	case Rules::INCORRECT_NO_EXP: {
		// could be errors ???
		// doesn't work properly ???
		m = (*it)->GetMod();
		if (m == KEYWORD_RETURN) {
			std::vector <PatternElement*>::iterator temp_it = ++it;		// ???
			while ((*it)->GetType() != ElementType::TYPE_NEW_LINE)
			{
				(*it)->SaveOrigElem();
				(*it)->SetValue("");
				it++;
			}
			IncorrectToText();
			
			it = temp_it;
			while ((*it)->GetType() != ElementType::TYPE_NEW_LINE)
			{
				(*it)->RestoreOrigElem();
				it++;
			}
			it = temp_it - 1;
		}

		//(*it)->SetValue(val);
		//IncorrectToText();
		break;
	}

	default:
		std::cout << "ERROR: [KeywordTestGen]\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();
}

void TestGen::SpaceTestGen(Rules rule, const int num) {
	(*it)->SaveOrigElem();

	std::string val = "";
	switch (rule)
	{
	case Rules::CORRECT_MULT_NEWLINES: {
		std::string val(num, '\n');			// ???
		(*it)->SetValue(val);
		CorrectToText();
		break;
	}

	case Rules::CORRECT_SPACES: {
		// space
		std::string val_sp(num, ' ');	// space as char
		(*it)->SetValue(val_sp);
		CorrectToText();

		// tab
		std::string val_tab(num, '\t');	// space as char
		(*it)->SetValue(val_tab);
		CorrectToText();

		break;
	}

	case Rules::INCORRECT_SPACES: {
		// space
		std::string val_sp(num, ' ');	// space as char
		(*it)->SetValue(val_sp);
		IncorrectToText();

		// tab
		std::string val_tab(num, '\t');	// space as char
		(*it)->SetValue(val_tab);
		IncorrectToText();

		break;
	}

	case Rules::INCORRECT_FUNC_PARAMS:
	case Rules::INCORRECT_TO_NAME: {
		// TODO: gen once, not for every rule
		val = "";

		//std::default_random_engine generator;
		boost::mt19937 generator;
		const int min_len = 1;
		const int max_len = 10;		// ???

		//std::uniform_int_distribution<int> distribution(min_len, max_len);
		//int len = distribution(generator);		// length of name
		boost::uniform_int<> dist_len(min_len, max_len);
		int len = dist_len(generator);

		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);

		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}
		(*it)->SetValue(val);
		IncorrectToText();

		break;
	}
	default:
		break;
	}
	(*it)->RestoreOrigElem();
}

void TestGen::NameTestGen(Rules rule) {
	(*it)->SaveOrigElem();

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
	case Rules::CORRECT_TO_UPPER_CASE: {
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_UP_LETTER, ASCII_LAST_UP_LETTER);
		boost::uniform_int<> distribution(ASCII_FIRST_UP_LETTER, ASCII_LAST_UP_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}

		(*it)->SetValue(val);
		CorrectToText();

		break;
	}

	case Rules::CORRECT_TO_NAME: {
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);

		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		// append symbol to string
		}
		(*it)->SetValue(val);
		CorrectToText();

		break;
	}
	case Rules::CORRECT_ADD_NUM: {
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
		IncorrectToText();
		break;
	}
	case Rules::INCORRECT_ADD_SPECIAL_SYM: {
		val = (*it)->GetValue();
		val += get_same_type_val(special_syms, 0);
		val += val;

		//std::uniform_int_distribution<int> distribution(ASCII_EXCLAMATION, ASCII_SLASH);
		//boost::uniform_int<> distribution(ASCII_EXCLAMATION, ASCII_SLASH);
		//val += (char)distribution(generator);

		//val += (*it)->GetValue();

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}
	case Rules::INCORRECT_TO_NUMBER: {
		//std::uniform_int_distribution<int> distribution(0, INT_MAX);
		boost::uniform_int<> distribution(0, INT_MAX);
		int num = distribution(generator);
		std::string val = std::to_string(num);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}
	case Rules::INCORRECT_TO_KEYWORD: {
		// Maybe could be problems ???
		val = get_same_type_val(keywords, 0);
		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}
	case Rules::INCORRECT_ADD_NUM: {
		boost::uniform_int<> distribution(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		//std::uniform_int_distribution<int> distribution(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		val += (char)distribution(generator);
		val += (*it)->GetValue();

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}

	default:
		std::cout << "ERROR: [NameTestGen]\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();
}

void TestGen::BracketTestGen(Rules rule) {
	(*it)->SaveOrigElem();

	uint8_t mod = (*it)->GetMod();
	std::string val = "";

	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:		
		(*it)->SetValue(val);
		IncorrectToText();
		break;
	case Rules::INCORRECT_SUBSTITUTION:		
		val = get_same_type_val(brackets, mod);
		(*it)->SetValue(val);
		IncorrectToText();
		break;

	case Rules::INCORRECT_WRONG_NUM: 
		// TODO: this cause problems with SWITCH statement	???
		// this rule as IF statement

		//boost::mt19937 generator;
		//boost::uniform_int<> distribution(2, 5);
		//uint8_t num = distribution(generator);

		//char v = (char)((*it)->GetValue()).c_str();		
		//std::string val(num, v);	
		//(*it)->SetValue(val);
		//IncorrectToText();

		break;
	
	default:
		std::cout << "ERROR: BracketTestGen\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();
}

void TestGen::ColonTestGen(Rules rule) {
	(*it)->SaveOrigElem();

	std::string val = "";

	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		IncorrectToText();
		break;
	case Rules::INCORRECT_TO_SPECIAL_SYM:
		val += get_same_type_val(special_syms, 0);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	default:
		std::cout << "ERROR: ColonTestGen\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();
}

// TODO ??? ...
void TestGen::ValueTestGen(std::vector<ElemValue*>::iterator iter, Rules rule) {
	(*it)->SaveOrigElem();

	std::string val = "";
	uint8_t m = (*iter)->GetMod();
	//ElemValue* original = new ElemValue(m, {});
	//BaseValue* base = static_cast<BaseValue*>(*it);
	//for ((*base).pv_iter; (*base).pv_iter != (*base).possible_values.end(); (*base).pv_iter++) {
		//uint8_t m = (*(*base).pv_iter)->GetMod();		// ???

	// TODO: IN THIS VERSION OF MY PYTHON-ASM COMILER OCTALS ARE [0o...], NOT [0...] (0o11 / 011)

	boost::mt19937 generator;


	switch (rule)
	{
	case Rules::CORRECT_RANDOM_VAL:
		switch (m) {
		case VALUE_INT_DEC: {
			//std::default_random_engine generator;		
			//std::uniform_int_distribution<int> distribution(0, INT_MAX);
			//int num = distribution(generator);

			boost::mt19937 generator;		// TODO: make it single instance as static outside all scopes in this file
			boost::uniform_int<> distribution(0, INT_MAX);
			int num = distribution(generator);

			val = std::to_string(num);

			(*it)->SetValue(val);
			CorrectToText();
			break;
		}
		case VALUE_INT_BIN: {
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
			break;

		}
		case VALUE_INT_OCT: {
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
			break;
		}
		case VALUE_INT_HEX: {
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
			break;

		}
		case VALUE_FLOAT: {
			//std::default_random_engine generator;
			//std::uniform_int_distribution<int> dist_one(0, 10);
			//std::uniform_int_distribution<int> dist_two(1, 100);
			//int num_one = dist_one(generator);
			//int num_two = dist_two(generator);

			boost::mt19937 generator;
			boost::uniform_real<float> distribution(0.0, FLT_MAX);		// ???
			boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(generator, distribution);
			float num = gen();
			val = boost::lexical_cast<std::string>(num);


			// ***

			//boost::mt19937 generator;
			//boost::uniform_int<> distribution_one(0, 10);
			//boost::uniform_int<> distribution_two(1, 100);
			//int num_one = distribution_one(generator);
			//int num_two = distribution_two(generator);

			//val = std::to_string(num_one);
			//val += '.';
			//val += std::to_string(num_two);

			(*it)->SetValue(val);
			//(*iter)->SetValue(val);
			CorrectToText();
			//(*it)->RestoreOrigElem();		// ???

			break;

		}
		case VALUE_STR: {
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
			break;
		}
		default:
			std::cout << "ERROR: [ValueTestGen]\n";
			exit(1);
		}
		break;
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		IncorrectToText();
		break;
	case Rules::INCORRECT_SUBSTITUTE_TYPE:
		// TODO
		switch (m) {
		case VALUE_INT_DEC: {

			break;
		}
		case VALUE_INT_BIN: {
			break;

		}
		case VALUE_INT_OCT: {
			break;

		}
		case VALUE_INT_HEX: {
			break;

		}
		case VALUE_FLOAT: {
			break;

		}
		case VALUE_STR: {
			break;

		}
		default:
			std::cout << "ERROR: [ValueTestGen]\n";
			exit(1);

		}
		break;
	case Rules::INCORRECT_SUBSTITUTE_NUMERAL_SYS:
		// TODO
		switch (m) {
		case VALUE_INT_DEC: {

			break;
		}
		case VALUE_INT_BIN: {
			break;

		}
		case VALUE_INT_OCT: {
			break;

		}
		case VALUE_INT_HEX: {
			break;

		}
		case VALUE_FLOAT: {
			break;

		}
		case VALUE_STR: {
			break;

		}
		default:
			std::cout << "ERROR: [ValueTestGen]\n";
			exit(1);

		}
		break;
	case Rules::INCORRECT_TO_SPECIAL_SYM: {
		val = get_same_type_val(special_syms, 0);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}

	case Rules::INCORRECT_TO_KEYWORD:
		val = get_same_type_val(keywords, 0);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	case Rules::INCORRECT_TO_NAME:
		
		// TODO ...
		// take names from the list of already initialized ones. 
		// random needs some initialization and it doesn't work here because of SWITCH

		break;

	default:
		std::cout << "ERROR: [ValueTestGen]\n";
		exit(1);
		break;
	}
	//memcpy(*iter, original, sizeof(*original));
	//(*it)->RestoreOrigElem();		

	//}
	(*it)->RestoreOrigElem();
}

void TestGen::OperationTestGen(Rules rule) {
	(*it)->SaveOrigElem();

	std::string val = ""; 
	uint8_t mod = (*it)->GetMod();

	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		(*it)->SetValue(val);
		IncorrectToText();
		break;
	case Rules::CORRECT_SUBSTITUTION: {
		switch (mod)
		{
		case ModOp::OP_UN_BITCOMP:
		case ModOp::OP_UN_NEG:
		case ModOp::OP_UN_NOT: {
			val = get_same_type_val(unary_ops, 0);
			(*it)->SetValue(val);
			CorrectToText();
			break;
		}
		case ModOp::OP_BIN_ADD:
		case ModOp::OP_BIN_DIV:
		case ModOp::OP_BIN_NEG:
		case ModOp::OP_BIN_MUL: {
			val = get_same_type_val(binary_ops, 0);
			(*it)->SetValue(val);
			CorrectToText();
			break;
		}
		default:
			std::cout << "ERROR: [OperationTestGen]\n";
			exit(1);
			break;
		}
		
		break;
	}
	case Rules::INCORRECT_SUBSTITUTION:		// to op which is not supported
		// TODO
		break;
	case Rules::INCORRECT_WRONG_NUM:
		// TODO like spaces
		break;
	case Rules::INCORRECT_SUBSTITUTE_TYPE:	// binary to unary and vice versa
		if (mod == OP_UN_BITCOMP || mod == OP_UN_NEG || mod == OP_UN_NOT) {
			val = get_same_type_val(binary_ops, 0);
			(*it)->SetValue(val);
			IncorrectToText();
		}
		else if (mod == OP_BIN_ADD || mod == OP_BIN_NEG || mod == OP_BIN_MUL || mod == OP_BIN_DIV) {
			val = get_same_type_val(unary_ops, 0);
			(*it)->SetValue(val);
			IncorrectToText();
		}
		else {
			std::cout << "ERROR: [OperationTestGen]\n";
			exit(1);
		}
		break;

	default:
		std::cout << "ERROR: [OperationTestGen]\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();

}

void TestGen::Correct() {
	(*it)->SaveOrigElem();

	ElementType type = (*it)->GetType();

	switch (type)
	{
	case ElementType::TYPE_KEYWORD: {

		//uint8_t mod = (*it)->GetMod();

		//switch (mod)
		//{
		//case KEYWORD_DEF:
		//	// DO NOTHING
		//	break;
		//case KEYWORD_RETURN:
		//	// DO NOTHING
		//	break;
		//default:
		//	std::cout << "ERROR: keyword mod error\n";
		//	exit(1);
		//	break;
		//}
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
		NameTestGen(Rules::CORRECT_TO_NAME);
		NameTestGen(Rules::CORRECT_ADD_NUM);
		NameTestGen(Rules::CORRECT_ADD_UNDERSCORE);
		NameTestGen(Rules::CORRECT_TO_UPPER_CASE);
		break;

	}

	case ElementType::TYPE_BRACKET: {
		//uint8_t mod = (*it)->GetMod();

		//if (mod == ModBracket::BRACKET_LPAREN) {
		//	// DO NOTHING
		//}
		//else if (mod == ModBracket::BRACKET_RPAREN) {
		//	// DO NOTHING
		//}
		break;

	}
	case ElementType::TYPE_COLON: {
		// DO NOTHING
		break;

	}
	case ElementType::TYPE_NEW_LINE: {
		// Multiple new lines
		SpaceTestGen(Rules::CORRECT_MULT_NEWLINES, 3);
		break;

	}
	case ElementType::TYPE_VALUE: {
		ElemValue* base = static_cast<ElemValue*>(*it);
		for (base->pv_iter = base->possible_values.begin(); base->pv_iter != base->possible_values.end(); base->pv_iter++) {
			ValueTestGen(base->pv_iter, Rules::CORRECT_SUBSTITUTE_TYPE);
			ValueTestGen(base->pv_iter, Rules::CORRECT_SUBSTITUTE_NUMERAL_SYS);
			ValueTestGen(base->pv_iter, Rules::CORRECT_RANDOM_VAL);
		}
		break;
	}
	case ElementType::TYPE_OP: {
		OperationTestGen(Rules::CORRECT_SUBSTITUTION);
		break;
	}

	default:
		std::cout << "ERROR: correct test error\n";
		exit(1);
	}
	//(*it)->RestoreOrigElem();
}

void TestGen::Incorrect() {
	(*it)->SaveOrigElem();

	ElementType type = (*it)->GetType();

	switch (type) {
	case ElementType::TYPE_KEYWORD: {
		//int mod = (*it)->GetMod();		// enum CLASS ???

		KeywordTestGen(Rules::INCORRECT_TO_UPPER_CASE);
		KeywordTestGen(Rules::INCORRECT_TO_NAME);
		KeywordTestGen(Rules::INCORRECT_ABSENT);
		KeywordTestGen(Rules::INCORRECT_SUBSTITUTION);
		KeywordTestGen(Rules::INCORRECT_NO_EXP);

		break;
	}
	case ElementType::TYPE_SPACE: {
		// TODO: make cosmetic enhancements ???

		ElementType t = (*(it - 1))->GetType();
		int m = (*(it - 1))->GetMod();
		if (t == ElementType::TYPE_KEYWORD) {
			int min_sp_num = 0;
			SpaceTestGen(Rules::INCORRECT_SPACES, min_sp_num);
			SpaceTestGen(Rules::INCORRECT_TO_NAME, 0);	// ???
		}
		else if (t == ElementType::TYPE_BRACKET && m == BRACKET_LPAREN) {
			// def main ( [name here] ). Incorrect test
			SpaceTestGen(Rules::INCORRECT_FUNC_PARAMS, 0);
		}
		// else DO NOTHING		???
		break;

	}
	case ElementType::TYPE_NAME: {
		// Currently only "main" supports	??? TODO

		NameTestGen(Rules::INCORRECT_ABSENT);
		NameTestGen(Rules::INCORRECT_ADD_SPECIAL_SYM);
		NameTestGen(Rules::INCORRECT_TO_NUMBER);
		NameTestGen(Rules::INCORRECT_TO_KEYWORD);
		NameTestGen(Rules::INCORRECT_ADD_NUM);	// double it maybe ???
		//FuncNameTestGen(RuleName::FIRST_NUMBER);	// double it maybe ???

		break;

	}
	case ElementType::TYPE_BRACKET: {
		BracketTestGen(Rules::INCORRECT_ABSENT);
		BracketTestGen(Rules::INCORRECT_SUBSTITUTION);
		BracketTestGen(Rules::INCORRECT_WRONG_NUM);
		break;

	}
	case ElementType::TYPE_COLON: {
		ColonTestGen(Rules::INCORRECT_ABSENT);
		ColonTestGen(Rules::INCORRECT_TO_SPECIAL_SYM);
		//ColonTestGen(RuleName::...);
		break;

	}
	case ElementType::TYPE_NEW_LINE: {
		std::string val = " ";
		(*it)->SetValue(val);
		IncorrectToText();
		break;

	}
	case ElementType::TYPE_VALUE: {
		ElemValue* base = static_cast<ElemValue*>(*it);
		for (base->pv_iter = base->possible_values.begin(); base->pv_iter != base->possible_values.end(); base->pv_iter++) {
			ValueTestGen(base->pv_iter, Rules::INCORRECT_ABSENT);
			ValueTestGen(base->pv_iter, Rules::INCORRECT_SUBSTITUTE_TYPE);
			ValueTestGen(base->pv_iter, Rules::INCORRECT_SUBSTITUTE_NUMERAL_SYS);
			ValueTestGen(base->pv_iter, Rules::INCORRECT_TO_SPECIAL_SYM);
			ValueTestGen(base->pv_iter, Rules::INCORRECT_TO_KEYWORD);
			ValueTestGen(base->pv_iter, Rules::INCORRECT_TO_NAME);
		}
		break;
	}
	case ElementType::TYPE_OP: {
		OperationTestGen(Rules::INCORRECT_ABSENT);
		OperationTestGen(Rules::INCORRECT_SUBSTITUTION);
		OperationTestGen(Rules::INCORRECT_WRONG_NUM);
		break;
	}
	default:
		std::cout << "ERROR: incorrect gen type\n";
		exit(1);
		break;
	}

	/*(*it)->RestoreOrigElem();*/
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
	file << "CORRECT\n\n";
	for (int i = 0; i < correct_tests.size(); i++) {
		file << "[" << i << "]\n";
		file << correct_tests[i];
		file << "\n";
	}
	file << "INCORRECT\n\n";
	for (int i = 0; i < incorrect_tests.size(); i++) {
		file << "[" << i << "]\n";
		file << incorrect_tests[i];
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
			//new ElemKeyword(ModKeyword::KEYWORD_DEF),
			//new ElemSpace(),
			//new ElemName("main"),
			//new ElemSpace(),
			//new ElemLeftBracket(ModBracket::BRACKET_LPAREN),
			//new ElemSpace(),
			//new ElemRightBracket(ModBracket::BRACKET_RPAREN),
			//new ElemSpace(),
			//new ElemColon(),
			//new ElemSpace(),
			//new ElemNewLine(),
			//new ElemSpace(),		// ...
			new ElemKeyword(ModKeyword::KEYWORD_RETURN),
			//new ElemSpace(),
			//// -1+(not 2)*(~3)/4
			//new ElemUnOperation(ModOp::OP_UN_NEG),
			//new ElemSpace(),
			new ElemValue(ModValue::VALUE_BASE, {
				new ElemValue(ModValue::VALUE_INT_DEC, {}),
				new ElemValue(ModValue::VALUE_FLOAT, {}),
				}),
			//new ElemSpace(),
			//new ElemBinOperation(ModOp::OP_BIN_ADD),
			//new ElemSpace(),
			//new ElemLeftBracket(ModBracket::BRACKET_LPAREN),
			//new ElemSpace(),
			//new ElemUnOperation(ModOp::OP_UN_NOT),
			//new ElemSpace(),
			//new ElemValue(ModValue::VALUE_BASE, {
				//new ElemValue(ModValue::VALUE_INT_DEC, {}),
				//new ElemValue(ModValue::VALUE_FLOAT, {}),
				//}),
			//new ElemSpace(),
			//new ElemRightBracket(ModBracket::BRACKET_RPAREN),
			//new ElemSpace(),
			//new ElemBinOperation(ModOp::OP_BIN_MUL),
			//new ElemSpace(),
			//new ElemLeftBracket(ModBracket::BRACKET_LPAREN),
			//new ElemSpace(),
			//new ElemUnOperation(ModOp::OP_UN_BITCOMP),
			//new ElemSpace(),
			//new ElemValue(ModValue::VALUE_BASE, {
				//new ElemValue(ModValue::VALUE_INT_DEC, {}),
				//new ElemValue(ModValue::VALUE_FLOAT, {}),
				//}),
			//new ElemSpace(),
			//new ElemRightBracket(ModBracket::BRACKET_RPAREN),
			//new ElemSpace(),
			//new ElemBinOperation(ModOp::OP_BIN_DIV),
			//new ElemValue(ModValue::VALUE_BASE, {
				//new ElemValue(ModValue::VALUE_INT_DEC, {}),
				//new ElemValue(ModValue::VALUE_FLOAT, {}),
				//}),
			//new ElemSpace()
			new ElemNewLine()
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
	name(""),
	group(""),
	lab_num(lab_num),
	test(""),		// generated test
	keywords({
		{ KEYWORD_DEF, "def" },
		{ KEYWORD_RETURN, "return" },
		{ KEYWORD_NOT, "not" },
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
	}),
	unary_ops({
		{OP_UN_NEG, "-"},
		{OP_UN_BITCOMP, "~"},
		{OP_UN_NOT, "not"},
	}),
	binary_ops({
		{OP_BIN_NEG, "-"},
		{OP_BIN_ADD, "+"},
		{OP_BIN_MUL, "*"},
		{OP_BIN_DIV, "/"}
	}),
	//operations({
	//	{OP_UNARY, "-"},
	//	{OP_UNARY, "~"},
	//	{OP_UNARY, "not"},
	//	{OP_BINARY, "-"},
	//	{OP_BINARY, "+"},
	//	{OP_BINARY, "*"},
	//	{OP_BINARY, "/"}
	//}),

	special_syms({
		{SP_SYM_AND, "&"},
		{SP_SYM_DOL, "$"},
		{SP_SYM_PERC, "%"},
		{SP_SYM_COLON, ":"},
		{SP_SYM_SEMI, ";"},
		{SP_SYM_QUEST, "?"},
		{SP_SYM_DOG, "@"},
		{SP_SYM_LINE, "|"}
		
	})
{
	GenPattern();
}

TestGen::~TestGen() {
}