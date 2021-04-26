#include "PatternElement.h"

#include <iostream>


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
ElemKeyword::ElemKeyword(int mod)
	:
	mod(mod),
	PatternElement(ElementType::KEYWORD, "")
{
	switch (mod){

	case KEYWORD_DEF:
		value = "def";
		break;

	case KEYWORD_RETURN:
		value = "return";
		break;
	}
}

ElemKeyword::~ElemKeyword()
{
}

void ElemKeyword::SaveOrigElem() {
	orig_val = new ElemKeyword(mod);
}

//void ElemKeyword::RestoreOrigElem() {
//	memcpy(this, orig_val, sizeof(*orig_val));
//}

// ElemSpace
ElemSpace::ElemSpace()
	:
	PatternElement(ElementType::SPACE, " ")
{}

ElemSpace::~ElemSpace()
{
}

void ElemSpace::SaveOrigElem() {
	orig_val = new ElemSpace();
}

//void ElemSpace::`OrigElem() {
//	memcpy(this, orig_val, sizeof(*orig_val));
//}

// ElemFuncName
ElemFuncName::ElemFuncName(std::string name)
	:
	PatternElement(ElementType::FUNC_NAME, name)
{}

ElemFuncName::~ElemFuncName()
{
}

void ElemFuncName::SaveOrigElem() {
	orig_val = new ElemFuncName(this->value);		// ???
}

//void ElemFuncName::RestoreOrigElem() {
//	memcpy(this, orig_val, sizeof(*orig_val));
//}

// ElemBrackets
ElemLeftBracket::ElemLeftBracket(int mod)
	:
	mod(mod),
	PatternElement(ElementType::BRACKET, "")
{
	switch (mod) {
	case BRACKET_LPAREN:
		value = "(";
		break;
	}
}

ElemLeftBracket::~ElemLeftBracket()
{
}

void ElemLeftBracket::SaveOrigElem() {
	orig_val = new ElemLeftBracket(mod);
}

//void ElemLeftBracket::RestoreOrigElem() {
//	memcpy(this, orig_val, sizeof(*orig_val));
//}

ElemRightBracket::ElemRightBracket(int mod)
	:
	mod(mod),
	PatternElement(ElementType::BRACKET, "")
{
	switch (mod) {
	case BRACKET_RPAREN:
		value = ")";
		break;
	}
}

ElemRightBracket::~ElemRightBracket()
{
}

void ElemRightBracket::SaveOrigElem() {
	orig_val = new ElemRightBracket(mod);
}

//void ElemRightBracket::RestoreOrigElem() {
//	memcpy(this, orig_val, sizeof(*orig_val));
//}

// ElemColon
ElemColon::ElemColon()
	:
	PatternElement(ElementType::COLON, ":")
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
	PatternElement(ElementType::NEW_LINE, "\n")
{}

ElemNewLine::~ElemNewLine()
{
}

void ElemNewLine::SaveOrigElem() {
	orig_val = new ElemNewLine();
}

//void ElemNewLine::RestoreOrigElem() {
//	memcpy(this, orig_val, sizeof(*orig_val));
//}

// ElemValue

ElemValue::ElemValue(int mod)
	:
	mod(mod),
	PatternElement(ElementType::VALUE, "")
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
	}
}

ElemValue::~ElemValue()
{
}

void ElemValue::SaveOrigElem() {
	orig_val = new ElemValue(mod);
}

//void ElemValue::RestoreOrigElem() {
//	memcpy(this, orig_val, sizeof(*orig_val));
//}
