#include "PatternElement.h"

#include <iostream>


PatternElement::PatternElement(ElementType type, std::string value)
	:
	type(type),
	value(value)
{}

PatternElement::~PatternElement() {

}

// ElemFuncKeyword

ElemKeyword::ElemKeyword(KeywordType mod)
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

void ElemKeyword::GenValue() {

}

// ElemSpace

ElemSpace::ElemSpace()
	:
	PatternElement(ElementType::SPACE, " ")
{}

ElemSpace::~ElemSpace()
{

}

void ElemSpace::GenValue() {

}

// ElemFuncName

ElemFuncName::ElemFuncName(std::string name)
	:
	PatternElement(ElementType::FUNC_NAME, name)
{}

ElemFuncName::~ElemFuncName()
{

}

void ElemFuncName::GenValue() {

}

// ElemParentheses

ElemLeftBracket::ElemLeftBracket(int mod)
	:
	mod(mod),
	PatternElement(ElementType::BRACKET, "")
{
	switch (mod) {
	case BRACKET_PAREN:
		value = "(";
		break;
	}
}

ElemLeftBracket::~ElemLeftBracket()
{

}

void ElemLeftBracket::GenValue() {

}

ElemRightBracket::ElemRightBracket(int mod)
	:
	mod(mod),
	PatternElement(ElementType::BRACKET, "")
{
	switch (mod) {
	case BRACKET_PAREN:
		value = ")";
		break;
	}
}

ElemRightBracket::~ElemRightBracket()
{

}

void ElemRightBracket::GenValue() {

}

// ElemNewLine

ElemNewLine::ElemNewLine()
	:
	PatternElement(ElementType::NEW_LINE, "\n")
{}

ElemNewLine::~ElemNewLine()
{

}

void ElemNewLine::GenValue() {

}

// ElemValue

ElemValue::ElemValue(int mod)
	:
	mod(mod),
	PatternElement(ElementType::VALUE, "")
	
{
	switch (mod) {
	case VALUE_INT:
		value = "2";
		break;
	}
}

ElemValue::~ElemValue()
{

}

void ElemValue::GenValue() {

}

