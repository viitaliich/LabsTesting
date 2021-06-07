/*
	FILE: PatternElement.h
*/

#include <cstdint>
#include <vector>
#include <string>

enum ModKeyword : uint8_t {
	KEYWORD_DEF = 1,
	KEYWORD_RETURN,
	KEYWORD_NOT,
};

enum ModBracket : uint8_t {
	BRACKET_LPAREN = 1,
	BRACKET_RPAREN,
	BRACKET_LSQUARE,
	BRACKET_RSQUARE,
	BRACKET_LBRACE,
	BRACKET_RBRACE,
	BRACKET_QUOTE,
	BRACKET_SINGLE_QUOTE,
	BRACKET_LANGLE,
	BRACKET_RANGLE,
};

enum ModValue : uint8_t {
	VALUE_INT_DEC = 1,
	VALUE_INT_BIN,
	VALUE_INT_OCT,
	VALUE_INT_HEX,
	VALUE_FLOAT,
	VALUE_STR,
	VALUE_BASE,
};

enum ModOp : uint8_t {
	OP_UN_BITCOMP = 1,
	OP_UN_NOT,
	OP_UN_NEG,
	OP_BIN_NEG,
	OP_BIN_ADD,
	OP_BIN_MUL,
	OP_BIN_DIV,
};

enum ModSpSym : uint8_t {
	SP_SYM_AND = 1,
	SP_SYM_COL,
	SP_SYM_PERC,
	SP_SYM_COLON,
	SP_SYM_SEMI,
	SP_SYM_QUEST,
	SP_SYM_DOG,
	SP_SYM_LINE,
};

enum class ElementType : uint8_t {
	TYPE_KEYWORD = 1,
	TYPE_SPACE,
	TYPE_NAME,
	TYPE_BRACKET,
	TYPE_COLON,
	TYPE_NEW_LINE,
	TYPE_VALUE,
	TYPE_BASE_VALUE,
	TYPE_OP,
	TYPE_EOF,
};

class PatternElement
{
protected:
	ElementType type;
	std::string value;
	PatternElement* orig_val;
	// Методи
};

class ElemKeyword : public PatternElement
{
private:
	uint8_t mod;
public:
	ElemKeyword(uint8_t mod);
	~ElemKeyword();

	void SaveOrigElem();

	inline int GetMod() const { return mod; }
};

class ElemSpace : public PatternElement
{
public:
	ElemSpace();
	~ElemSpace();

	void SaveOrigElem();
};

class ElemName : public PatternElement
{
	// ...
};

class ElemLeftBracket : public PatternElement
{
	// ...
};

class ElemRightBracket : public PatternElement
{
	// ...
};

class ElemColon : public PatternElement
{
	// ...
};

class ElemNewLine : public PatternElement
{
	// ...
};

class ElemValue : public PatternElement
{
	// ...
};

class BaseValue : public PatternElement {
	// ...
};

class ElemUnOperation : public PatternElement
{
	// ...
};

class ElemBinOperation : public PatternElement
{
	// ...
};

class ElemEOF : public PatternElement
{
	// ...
};

/*
	FILE: PatternElement.cpp
*/

#include <iostream>
#include "PatternElement.h"

// Конструктор класу
PatternElement::PatternElement(ElementType type, std::string value)
	:
	type(type),
	value(value)
{}

// Метод відновлення елементу шаблону
void PatternElement::RestoreOrigElem() {
	memcpy(this, orig_val, sizeof(*orig_val));
}

void PatternElement::SetValue(std::string value) {
	this->value = value;
}

// ElemFuncKeyword
ElemKeyword::ElemKeyword(uint8_t mod)
	:
	mod(mod),
	PatternElement(ElementType::TYPE_KEYWORD, "")
{
	switch (mod) {

	case KEYWORD_DEF:
		value = "def";
		break;

	case KEYWORD_RETURN:
		value = "return";
		break;
	default:
		std::cout << "ERROR: ElemKeyword constructor\n";
		exit(1);
	}
}

void ElemKeyword::SaveOrigElem() {
	orig_val = new ElemKeyword(mod);
}

// ElemSpace
ElemSpace::ElemSpace()
	:
	PatternElement(ElementType::TYPE_SPACE, " ")
{}

void ElemSpace::SaveOrigElem() {
	orig_val = new ElemSpace();
}

// ElemName
ElemName::ElemName(std::string name)
	:
	PatternElement(ElementType::TYPE_NAME, name)
{}

// ElemLeftBracket
ElemLeftBracket::ElemLeftBracket(uint8_t mod)
	:
	mod(mod),
	PatternElement(ElementType::TYPE_BRACKET, "")
{
	switch (mod) {
	case BRACKET_LPAREN:
		value = "(";
		break;
	default:
		std::cout << "ERROR: ElemLeftBracket constructor\n";
		exit(1);
	}
}

// ElemRightBracket
ElemRightBracket::ElemRightBracket(uint8_t mod)
	:
	mod(mod),
	PatternElement(ElementType::TYPE_BRACKET, "")
{
	switch (mod) {
	case BRACKET_RPAREN:
		value = ")";
		break;
	default:
		std::cout << "ERROR: ElemRightBracket constructor\n";
		exit(1);
	}
}

// ElemValue
ElemValue::ElemValue(uint8_t mod, std::vector<ElemValue*> values)
	:
	possible_values(values),
	mod(mod),
	PatternElement(ElementType::TYPE_VALUE, "")
{
	switch (mod) {
	case VALUE_INT_DEC: {
		value = "2";
		break;
	}
	case VALUE_INT_BIN: {
		value = "0b11";
		break;
	}
	// ...
	}
	default:
		std::cout << "ERROR: ElemValue constructor\n";
		exit(1);
	}
}

void ElemValue::SaveOrigElem() {
	orig_val = new ElemValue(mod, possible_values);
}

BaseValue::BaseValue(std::vector<ElemValue*> values)
	:
	possible_values(values),
	pv_iter(possible_values.begin()),
	PatternElement(ElementType::TYPE_BASE_VALUE, "")
{}

void BaseValue::SaveOrigElem() {
}

// ElemUnOperation
ElemUnOperation::ElemUnOperation(uint8_t mod)
	:
	mod(mod),

	PatternElement(ElementType::TYPE_OP, "")
{
	switch (mod) {
	case OP_UN_BITCOMP: {
		value = "~";
		break;
	}
	// ...
	default:
		std::cout << "ERROR: ElemOperation constructor\n";
		exit(1);
	}
}

void ElemUnOperation::SaveOrigElem() {
	orig_val = new ElemUnOperation(mod);
}

// ElemBinOperation
ElemBinOperation::ElemBinOperation(uint8_t mod)
	:
	mod(mod),
	PatternElement(ElementType::TYPE_OP, "")
{
	switch (mod) {
	case OP_BIN_NEG: {
		value = "-";
		break;
	}
	case OP_BIN_ADD: {
		value = "+";
		break;
	}
	// ...
	default:
		std::cout << "ERROR: ElemOperation constructor\n";
		exit(1);
	}
}

void ElemBinOperation::SaveOrigElem() {
	orig_val = new ElemBinOperation(mod);
}

/*
	FILE: TestGen.h
*/

#include <string>
#include <vector>
#include <sstream>

#include "common.h"
#include "PatternElement.h"

struct Element {
	int8_t mod;
	std::string val;
};

enum class LabNumber : uint8_t {
	LAB1 = 1,
	//...
};

// Перелік правил, за якими генеруються тести
enum class Rules : uint8_t {
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

// Клас, відповідний за генерацію тестів
class TestGen
{
private:
	// Вектор шаблону, за яким генеруються тести
	std::vector <PatternElement*> pattern;
	std::vector <PatternElement*>::iterator it;

	std::vector <Element> keywords;		 
	std::vector <Element> brackets;		 
	std::vector <Element> special_syms;
	std::vector <uint8_t> supported_types;
	std::vector<uint8_t>::iterator st_iter;		
	std::vector <uint8_t> unsupported_types;
	std::vector<uint8_t>::iterator ust_iter;		
	std::vector <uint8_t> supported_bases;		
	std::vector<uint8_t>::iterator sb_iter;		
	std::vector <uint8_t> unsupported_bases;		
	std::vector<uint8_t>::iterator usb_iter;		

	std::vector <Element> supported_un_ops;
	std::vector <Element>::iterator suo_iter;
	std::vector <Element> unsupported_un_ops;
	std::vector <Element>::iterator usuo_iter;
	std::vector <Element> supported_bin_ops;
	std::vector <Element>::iterator sbo_iter;
	std::vector <Element> unsupported_bin_ops;
	std::vector <Element>::iterator usbo_iter;

	// Згенерований тест
	std::string test = "";					
	// Вектори згенерованих тестів
	std::vector <std::string> correct_tests;
	std::vector <std::string> incorrect_tests;
	// Випадково згенероване ім'я
	std::string random_name = "";

public:
	char* status = (char*)"---";
	char path_compiler[1024] = "---";
	char path_source[1024] = "---";
	char name[64] = "";
	char group[64] = "";
	int lab_num;
	int lab_var;
	int item_current_lab = 0;
	int item_current_var = 0;

	// Дані для висталення оцінки
	int tests_num = 0;				
	int correct_tests_num = 0;		
	int max_mark;
	double percent;
	double mark = 0.0;

private:
	// Методи
	// ...
};

/*
	FILE: TestGen.cpp
*/

#include <fstream>
#include <iostream>
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

// Функція отримання унікального елемента з вектора
std::string get_same_type_val(std::vector <Element>& vec, uint8_t mod) {
	// ...	
}

// Функція знаходження необхідного ключового слова
std::string TestGen::FindKeyword(int mod) {
	// ...
}

// Функція переводу коректного тесту у текст
void TestGen::CorrectToText() {
	std::vector <PatternElement*>::iterator iter;
	for (iter = pattern.begin(); iter != pattern.end(); iter++) {
		test += (*iter)->GetValue();
	}
	correct_tests.push_back(test);
	test = "";
}

// Функція переводу некоректного тесту у текст
void TestGen::IncorrectToText() {
	// ...
}

// Функція генерації тесту для елементу ключового слова
// в залежності від правила
void TestGen::KeywordTestGen(Rules rule) {
	// Збереження оригінального значення шаблону
	(*it)->SaveOrigElem();

	// Генератор випадкових значень
	boost::mt19937 generator;
	std::string val = (*it)->GetValue();
	uint8_t m;		

	// Вибір дії залежно від заданого правила
	switch (rule)
	{
	// Генерація неправильного тесту: перевод у верхній регістр
	case Rules::INCORRECT_TO_UPPER_CASE: {
		boost::to_upper(val);
		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}

	// Генерація неправильного тесту: заміна ключового слова іменем
	case Rules::INCORRECT_TO_NAME: {
		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		val += (char)distribution(generator);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}
	// Генерація неправильного тесту: відсутність ключового слова
	case Rules::INCORRECT_ABSENT: {
		val = "";

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}
	// Генерація неправильного тесту: заміна ключового слова на інше
	case Rules::INCORRECT_SUBSTITUTION:
		m = (*it)->GetMod();
		val = get_same_type_val(keywords, m);

		(*it)->SetValue(val);
		IncorrectToText();
		break;

	// Генерація неправильного тесту: відсутність виразу після ключового слова
	case Rules::INCORRECT_NO_EXP: {
		m = (*it)->GetMod();
		if (m == KEYWORD_RETURN) {
			std::vector <PatternElement*>::iterator temp_it = ++it;		// ???
			while (it != pattern.end())
			{
				(*it)->SaveOrigElem();
				(*it)->SetValue("");
				it++;
			}
			IncorrectToText();

			it = temp_it;
			while (it != pattern.end())
			{
				(*it)->RestoreOrigElem();
				it++;
			}
			it = temp_it - 1;
		}
		break;
	}

	default:
		std::cout << "ERROR: [KeywordTestGen]\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();
}

// Генерація тестів для пробілів, табуляції та пустих рядків, базуючись на заданому правилі
void TestGen::SpaceTestGen(Rules rule, const int num) {
	(*it)->SaveOrigElem();

	std::string val = "";
	switch (rule)
	{
	case Rules::CORRECT_MULT_NEWLINES: {
		std::string val(num, '\n');			
		(*it)->SetValue(val);
		CorrectToText();
		break;
	}

	case Rules::CORRECT_SPACES: {
		// space
		std::string val_sp(num, ' ');	
		(*it)->SetValue(val_sp);
		CorrectToText();

		// tab
		std::string val_tab(num, '\t');	
		(*it)->SetValue(val_tab);
		CorrectToText();
		break;
	}

	case Rules::INCORRECT_SPACES: {
		// space
		std::string val_sp(num, ' ');	
		(*it)->SetValue(val_sp);
		IncorrectToText();

		// tab
		std::string val_tab(num, '\t');	
		(*it)->SetValue(val_tab);
		IncorrectToText();

		break;
	}

	// Невідповідна кількість параметрів функції
	case Rules::INCORRECT_FUNC_PARAMS:
	case Rules::INCORRECT_TO_NAME: {
		val = "";

		boost::mt19937 generator;
		const int min_len = 1;
		const int max_len = 10;	

		boost::uniform_int<> dist_len(min_len, max_len);
		int len = dist_len(generator);

		boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
		for (int i = 0; i <= len; i++) {
			val += distribution(generator);		
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

	boost::mt19937 generator;
	const int min_len = 1;
	const int max_len = 10;		

	boost::uniform_int<> distribution(min_len, max_len);
	int len = distribution(generator);

	switch (rule) {
	case Rules::CORRECT_TO_UPPER_CASE: {
		// ...
	}

	case Rules::CORRECT_TO_NAME: {
		// ...
	}
	case Rules::CORRECT_ADD_NUM: {
		val = (*it)->GetValue();
		boost::uniform_int<> distribution_two(ASCII_FIRST_NUMBER, ASCII_LAST_NUMBER);
		val += distribution_two(generator);		
		val += val;
		(*it)->SetValue(val);
		CorrectToText();
		break;
	}
	case Rules::CORRECT_ADD_UNDERSCORE: {
		// ...
	}
	case Rules::INCORRECT_ABSENT: {
		// ...
	}
	case Rules::INCORRECT_ADD_SPECIAL_SYM: {
		val = (*it)->GetValue();
		val += get_same_type_val(special_syms, 0);
		val += val;

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}
	case Rules::INCORRECT_TO_NUMBER: {
		boost::uniform_int<> distribution(0, INT_MAX);
		int num = distribution(generator);
		std::string val = std::to_string(num);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}
	case Rules::INCORRECT_TO_KEYWORD: {
		// ...
	}
	case Rules::INCORRECT_ADD_NUM: {
		// ...
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

	uint8_t m = (*it)->GetMod();
	std::string val = "";
	std::string wrong_num_val(3, (*it)->GetValue()[0]);

	switch (rule)
	{
	case Rules::INCORRECT_ABSENT:
		// ...
	case Rules::INCORRECT_SUBSTITUTION:
		// ...
	case Rules::INCORRECT_WRONG_NUM:
		(*it)->SetValue(wrong_num_val);
		IncorrectToText();
		break;
	default:
		std::cout << "ERROR: BracketTestGen\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();
}

void TestGen::ColonTestGen(Rules rule) {
	// ...
}

void TestGen::ValueTestGen(std::vector<ElemValue*>::iterator iter, Rules rule) {
	(*it)->SaveOrigElem();

	std::string val = "";
	uint8_t m = (*iter)->GetMod();
	boost::mt19937 generator;

	switch (rule)
	{
	case Rules::CORRECT_SUBSTITUTE_TYPE:
		for (st_iter = supported_types.begin(); st_iter != supported_types.end(); st_iter++) {
			switch (*st_iter)
			{
			case ModValue::VALUE_INT_DEC: {
				boost::mt19937 generator;		
				boost::uniform_int<> distribution(0, INT_MAX);
				int num = distribution(generator);

				val = std::to_string(num);

				(*it)->SetValue(val);
				CorrectToText();
				(*it)->RestoreOrigElem();
				(*it)->SaveOrigElem();
				break;
			}

			case ModValue::VALUE_FLOAT: {
				boost::mt19937 generator;
				boost::uniform_real<float> distribution(0.0, FLT_MAX);		
				boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(generator, distribution);
				float num = gen();
				val = boost::lexical_cast<std::string>(num);

				(*it)->SetValue(val);
				CorrectToText();
				(*it)->RestoreOrigElem();
				(*it)->SaveOrigElem();

				break;
			}
			case ModValue::VALUE_STR: {
				const int len = 5;		

				boost::mt19937 generator;
				boost::uniform_int<> distribution(ASCII_FIRST_LOW_LETTER, ASCII_LAST_LOW_LETTER);
				for (int i = 0; i <= len; i++) {
					val += distribution(generator);		
				}

				(*it)->SetValue(val);
				CorrectToText();
				(*it)->RestoreOrigElem();
				(*it)->SaveOrigElem();

				break;
			}
			default:
				std::cout << "ERROR: CORRECT_SUBSTITUTE_TYPE\n";
				exit(1);
			}
		}
		break;

	case Rules::CORRECT_SUBSTITUTE_NUMERAL_SYS:
		for (sb_iter = supported_bases.begin(); sb_iter != supported_bases.end(); sb_iter++) {
			switch (*sb_iter)
			{
			case ModValue::VALUE_INT_DEC: {
				break;
			}

			case ModValue::VALUE_INT_BIN: {
				boost::mt19937 generator;
				boost::uniform_int<> distribution(1, 28);
				int len = distribution(generator);

				val = "0b0";
				for (int i = 0; i < len; i++) {
					boost::uniform_int<> dist(ASCII_0, ASCII_1);		
					char sym = (char)dist(generator);
					val += sym;
				}
				(*it)->SetValue(val);
				CorrectToText();
				(*it)->RestoreOrigElem();
				(*it)->SaveOrigElem();
				break;
			}
			case ModValue::VALUE_INT_OCT: {
				boost::mt19937 generator;
				boost::uniform_int<> distribution(1, 10);
				int len = distribution(generator);

				val = "0o0";
				for (int i = 0; i < len; i++) {
					boost::uniform_int<> dist(ASCII_0, ASCII_7);		
					char sym = (char)dist(generator);
					val += sym;
				}

				(*it)->SetValue(val);
				CorrectToText();
				(*it)->RestoreOrigElem();
				(*it)->SaveOrigElem();

				break;
			}
			case ModValue::VALUE_INT_HEX: {
				// ...
				break;
			}
			default:
				std::cout << "ERROR: CORRECT_SUBSTITUTE_BASE\n";
				exit(1);
			}
		}
		break;

	case Rules::INCORRECT_ABSENT:
		// ...
	case Rules::INCORRECT_SUBSTITUTE_TYPE:
		// ...
		break;


	case Rules::INCORRECT_SUBSTITUTE_NUMERAL_SYS:
		// ...
		break;
	case Rules::INCORRECT_TO_SPECIAL_SYM: {
		val = get_same_type_val(special_syms, 0);

		(*it)->SetValue(val);
		IncorrectToText();
		break;
	}

	case Rules::INCORRECT_TO_KEYWORD:
		// ...
		break;
	case Rules::INCORRECT_TO_NAME:
		
		(*it)->SetValue(random_name);
		IncorrectToText();
		break;

	default:
		std::cout << "ERROR: [ValueTestGen]\n";
		exit(1);
		break;
	}
	(*it)->RestoreOrigElem();
}

void TestGen::OperationTestGen(Rules rule) {
	(*it)->SaveOrigElem();
	std::string wrong_num_val(3, (*it)->GetValue()[0]);
	std::string val = "";
	uint8_t m = (*it)->GetMod();

	switch (rule) {
	case Rules::CORRECT_SUBSTITUTION: {
		switch (m) {
		case ModOp::OP_UN_BITCOMP:
		case ModOp::OP_UN_NEG:
		case ModOp::OP_UN_NOT: {
			for (suo_iter = supported_un_ops.begin(); suo_iter != supported_un_ops.end(); suo_iter++) {
				(*it)->SetValue(suo_iter->val);
				CorrectToText();
				(*it)->RestoreOrigElem();
				(*it)->SaveOrigElem();
			}
			break;
		}
		case ModOp::OP_BIN_ADD:
		case ModOp::OP_BIN_NEG:
		case ModOp::OP_BIN_MUL:
		case ModOp::OP_BIN_DIV: {
			for (sbo_iter = supported_bin_ops.begin(); sbo_iter != supported_bin_ops.end(); sbo_iter++) {
				(*it)->SetValue(sbo_iter->val);
				CorrectToText();
				(*it)->RestoreOrigElem();
				(*it)->SaveOrigElem();
			}
			break;
		}
		}
		break;
	}

	case Rules::INCORRECT_ABSENT:
		// ...
		break;

	case Rules::INCORRECT_SUBSTITUTION:		
		// ...
		break;

	case Rules::INCORRECT_WRONG_NUM:
		// ...
		break;

	case Rules::INCORRECT_SUBSTITUTE_TYPE:
		if (m == OP_UN_BITCOMP || m == OP_UN_NEG || m == OP_UN_NOT) {
			val = get_same_type_val(supported_bin_ops, 0);
			(*it)->SetValue(val);
			IncorrectToText();
		}
		else if (m == OP_BIN_ADD || m == OP_BIN_NEG || m == OP_BIN_MUL || m == OP_BIN_DIV) {
			val = get_same_type_val(supported_un_ops, 0);
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

// Функція для вибору правил, за якими генерувати коректні тести 
// та виклики відповідних функцій
void TestGen::Correct() {
	(*it)->SaveOrigElem();
	ElementType type = (*it)->GetType();
	switch (type)
	{
	case ElementType::TYPE_KEYWORD: {
		// DO NOTHING
		break;
	}
	case ElementType::TYPE_SPACE: {
		int min_sp_num = 0;
		int rand_sp_num;
		const int max_sp_num = 4;

		ElementType t = (*(it - 1))->GetType();
		if (t == ElementType::TYPE_KEYWORD || t == ElementType::TYPE_NEW_LINE) {
			min_sp_num = 1;
		}
		
		boost::mt19937 generator;
		boost::uniform_int<> distribution(
			((min_sp_num + 1 <= max_sp_num - 1) ? min_sp_num + 1 : min_sp_num),
			((max_sp_num - 1 > min_sp_num + 1) ? max_sp_num - 1 : max_sp_num));
		rand_sp_num = distribution(generator);

		SpaceTestGen(Rules::CORRECT_SPACES, min_sp_num);
		SpaceTestGen(Rules::CORRECT_SPACES, rand_sp_num);
		SpaceTestGen(Rules::CORRECT_SPACES, max_sp_num);
		break;
	}
	case ElementType::TYPE_BRACKET: {
		// DO NOTHING
		break;
	}
	case ElementType::TYPE_COLON: {
		// DO NOTHING
		break;
	}
	case ElementType::TYPE_NEW_LINE: {
		SpaceTestGen(Rules::CORRECT_MULT_NEWLINES, 3);		
		break;
	}
	case ElementType::TYPE_VALUE: {
		ElemValue* base = static_cast<ElemValue*>(*it);
		for (base->pv_iter = base->possible_values.begin(); base->pv_iter != base->possible_values.end(); base->pv_iter++) {
			ValueTestGen(base->pv_iter, Rules::CORRECT_SUBSTITUTE_TYPE);
			ValueTestGen(base->pv_iter, Rules::CORRECT_SUBSTITUTE_NUMERAL_SYS);
		}
		break;
	}
	case ElementType::TYPE_OP: {
		OperationTestGen(Rules::CORRECT_SUBSTITUTION);		
		break;
	}
	case ElementType::TYPE_EOF:
		break;

	default:
		std::cout << "ERROR: correct test error\n";
		exit(1);
	}
}

// Функція для вибору правил, за якими генерувати некоректні тести 
// та виклики відповідних функцій
void TestGen::Incorrect() {
	// ...
}

// Функція генерації тестів залежно від номеру лабораторної роботи
void TestGen::Generate() {
	switch (lab_num) {
	case LAB1:
		supported_types = { ModValue::VALUE_INT_DEC, ModValue::VALUE_FLOAT };
		unsupported_types = { ModValue::VALUE_STR };
		supported_bases = { ModValue::VALUE_INT_DEC, ModValue::VALUE_INT_BIN };
		unsupported_bases = { ModValue::VALUE_INT_HEX, ModValue::VALUE_INT_OCT };

		supported_bin_ops = {
			{OP_BIN_NEG, "-"},
			{OP_BIN_ADD, "+"}

		};
		unsupported_bin_ops = {
			{OP_BIN_MUL, "*"},
			{OP_BIN_DIV, "/"}
		};
		supported_un_ops = {
			{OP_UN_NEG, "-"},
			{OP_UN_BITCOMP, "~"},
		};
		unsupported_un_ops = {
			{OP_UN_NOT, "not"}
		};

		break;

	case LAB2:
		// ...
	// ...
	default:
		break;
	}

	GenPattern(); // Генерація шаблону

	for (it = pattern.begin(); it != pattern.end(); it++) {
		Correct();
		Incorrect();
	}

	// Запуск згенерованих тестів на виконання
	std::vector <std::string>::iterator iter;
	for (iter = correct_tests.begin(); iter != correct_tests.end(); iter++) {
		tests_num++;
		modify_input_code(*iter, path_source);
		std::string out_res_path = run_program(path_compiler);		
		std::ifstream stream(out_res_path);
		std::string line;
		while (getline(stream, line)) {
			if (line.find("RESULT BEGIN...") != std::string::npos) {
				getline(stream, line);
				while (!isdigit(line[0]) && (!line.find("... RESULT END") != std::string::npos))
					getline(stream, line);
				if (line.find("... RESULT END") != std::string::npos) {
					// failed tests
					// DO NOTHING
				}
				else {
					// passed tests
					correct_tests_num++;
				}
			}
		}
	}

	for (iter = incorrect_tests.begin(); iter != incorrect_tests.end(); iter++) {
		// ...
	}

	// Виставлення оцінки
	percent = correct_tests_num * 100 / tests_num;
	mark = percent * max_mark / 100;
}

void TestGen::GenPattern() {
	switch (lab_num)
	{
	case 1: {
		pattern = {
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
			new ElemSpace(),
			new ElemKeyword(ModKeyword::KEYWORD_RETURN),
			new ElemSpace(),
			new ElemValue(ModValue::VALUE_BASE, {
				new ElemValue(ModValue::VALUE_INT_DEC, {}),
				new ElemValue(ModValue::VALUE_FLOAT, {}),
				}),
		};
		break;
	}
	case 2: {
		// ...
		break;
	}
	// ...
	default:
		std::cout << "ERROR: undefined lab number\n";
		exit(1);
		break;
	}

// Конструктор класу TestGen
TestGen::TestGen()
	:
	keywords({
		{ KEYWORD_DEF, "def" },
		{ KEYWORD_RETURN, "return" },
		{ KEYWORD_NOT, "not" },
		}),		
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
{}

TestGen::~TestGen() {
}

/*
	FILE: common.cpp
*/

#include "common.h"

// Функція перевірки існування файлу
void check_file(const std::string& path) {
	// ...
}

// Функція запуску програми на виконання
std::string run_program(std::string path) {
	check_file(path);
	size_t index = path.length() - 1;
	while (path[index] != '.' && index > 0) {
		index--;
	}
	size_t name_end = index - 1;

	while ((path[index] != '/') && index > 0) {		
		index--;
	}
	size_t name_start = index + 1;

	size_t length = 0;
	if (name_end != 0 && name_start != 0 && name_end != name_start)
		length = name_end - name_start + 1;
	else {
		std::cout << "ERROR: file path is wrong\n";
		exit(1);
	}
	std::string file_name = path.substr(name_start, length);

	std::stringstream ss;
	ss << path << " > " << file_name;
	std::string cmd(ss.str());
	ss << system(cmd.c_str());

	// Повертає шлях до файлу, куди заносяться результати виконання програми
	return path.substr(0, name_start) + file_name;
}

// Перезапис файлу
void modify_input_code(std::string& data, const std::string& path) {
	// ...
}

/*
	FILE: main.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <fstream>
#include <thread>

#include <GLFW/glfw3.h>	
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/ImGuiFileBrowser.h"

#include "common.h"
#include "TestGen.h"

// Функція, яку виконують дочірні потоки
void t_generate(std::vector<TestGen*>& test_gens, int& labs_num, int i) {
	// Відстеження статусу генерації тестів
	test_gens[i]->status = (char*)"IN PROGRESS ...";
	test_gens[i]->Generate();	// Метод генерації тестів
	test_gens[i]->status = (char*)"DONE";
}

// Функція відображення вікна
void ShowWindow(bool* p_open, std::vector<TestGen*>& test_gens, std::vector<std::thread>& threads) {

	// Об'єкт для вікна вибору файлів
	static imgui_addons::ImGuiFileBrowser file_dialog;
	
	// Побудова графічного інтерфейсу
	// ...
	static int labs_num;
	static bool button_enter = false;
	if (ImGui::Button("ENTER lab num")) {
		if (!test_gens.empty()) {
			test_gens.clear();
		}
		labs_num = atoi(buf);
		// Створення екземплярів класу TestGen
		for (int i = 0; i < labs_num; i++) {
			test_gens.push_back(new TestGen());
		}
		button_enter = true;
	}

	if (button_enter) {
		// Побудова графічного інтерфейсу
		// ...
		// Побудова таблиці в графічному інтерфейсі
		// ...
		for (int i = 0; i < labs_num; i++)
		{
			// ...
			// Занесення ідентифікаторів створених потоків у спеціальний вектор	
			threads.push_back(std::thread(t_generate, std::ref(test_gens), std::ref(labs_num), i));
			// ...
		}
		// ...

		if (ImGui::Button("GENERATE ALL")) {
			for (int i = 0; i < labs_num; i++) {
				threads.push_back(std::thread(t_generate, std::ref(test_gens), std::ref(labs_num), i));
			}
		}
		ImGui::SameLine();
		ImGui::Text("Press this button to generate all tests at once.");
	}
}


// Головна функція. Точка входу у програму
int main(int argc, char** argv) {

	// Вектор вказівників на створені екземпляри класу TestGen.
	std::vector<TestGen*> test_gens;	
	// Вектор ідентифікаторів дочірніх потоків
	std::vector<std::thread> threads;

	// Створення вікна
	// ...

	bool show_window = true;
	
	// Цикл роботи вікна
	while (!glfwWindowShouldClose(window))
	{
		// ...

		// Відображення вікна
		if (show_window) {
			ShowWindow(&show_window, test_gens, threads);
		}
		// ...
	}

	// Завершення роботи вікна
	// ...

	// Синхронізація потоків
	for (auto& th : threads) th.join();

	return 0;
}