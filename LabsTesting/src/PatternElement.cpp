#include <iostream>

#include "PatternElement.h"


PatternElement::PatternElement(ElementType type, std::string value)
	:
	type(type),
	value(value)
{}

PatternElement::~PatternElement() {
}

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

ElemKeyword::~ElemKeyword()
{
}

void ElemKeyword::SaveOrigElem() {
	orig_val = new ElemKeyword(mod);
}

// ElemSpace
ElemSpace::ElemSpace()
	:
	PatternElement(ElementType::TYPE_SPACE, " ")
{}

ElemSpace::~ElemSpace()
{
}

void ElemSpace::SaveOrigElem() {
	orig_val = new ElemSpace();
}

// ElemName
ElemName::ElemName(std::string name)
	:
	PatternElement(ElementType::TYPE_NAME, name)
{}

ElemName::~ElemName()
{
}

void ElemName::SaveOrigElem() {
	orig_val = new ElemName(this->value);		// take name iterator points at
}

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

ElemLeftBracket::~ElemLeftBracket()
{
}

void ElemLeftBracket::SaveOrigElem() {
	orig_val = new ElemLeftBracket(mod);
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

ElemRightBracket::~ElemRightBracket()
{
}

void ElemRightBracket::SaveOrigElem() {
	orig_val = new ElemRightBracket(mod);
}

// ElemColon
ElemColon::ElemColon()
	:
	PatternElement(ElementType::TYPE_COLON, ":")
{}

ElemColon::~ElemColon()
{
}

void ElemColon::SaveOrigElem() {
	orig_val = new ElemColon();
}

// ElemNewLine
ElemNewLine::ElemNewLine()
	:
	PatternElement(ElementType::TYPE_NEW_LINE, "\n")
{}

ElemNewLine::~ElemNewLine()
{
}

void ElemNewLine::SaveOrigElem() {
	orig_val = new ElemNewLine();
}

// ElemValue
ElemValue::ElemValue(uint8_t mod)
	:
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
	case VALUE_INT_OCT: {
		value = "0o7";
		break;
	}
	case VALUE_INT_HEX: {
		value = "0xAA";
		break;
	}
	case VALUE_FLOAT: {
		value = "3.14";
		break;
	}
	case VALUE_STR: {
		value = "hello";
		break;
	}
	default:
		std::cout << "ERROR: ElemValue constructor\n";
		exit(1);
	}
}

ElemValue::~ElemValue()
{
}

void ElemValue::SaveOrigElem() {
	orig_val = new ElemValue(mod);
}
