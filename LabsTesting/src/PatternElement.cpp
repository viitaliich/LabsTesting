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
	
{}

ElemKeyword::~ElemKeyword()
{

}

void ElemKeyword::GenValue() {

}

// ElemSpace

ElemSpace::ElemSpace(/*int mod*/)
	:
	//mod(mod),
	PatternElement(ElementType::SPACE, "")
{}

ElemSpace::~ElemSpace()
{

}

void ElemSpace::GenValue() {

}

// ElemFuncName

ElemFuncName::ElemFuncName()
	:
	PatternElement(ElementType::FUNC_NAME, "")
{}

ElemFuncName::~ElemFuncName()
{

}

void ElemFuncName::GenValue() {

}

// ElemParentheses

ElemParentheses::ElemParentheses(int mod)
	:
	mod(mod),
	PatternElement(ElementType::PARENTHESES, "")
{}

ElemParentheses::~ElemParentheses()
{

}

void ElemParentheses::GenValue() {

}

// ElemNewLine

ElemNewLine::ElemNewLine()
	:
	PatternElement(ElementType::NEW_LINE, "")
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
	
{}

ElemValue::~ElemValue()
{

}

void ElemValue::GenValue() {

}

