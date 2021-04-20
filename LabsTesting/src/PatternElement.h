#pragma once

#include <cstdint>
#include <vector>
#include <string>

enum class KeywordType : int8_t {
	KEYWORD_FUNC,
	KEYWORD_RETURN
};

enum class SpaceType : int8_t {
	SPACE_SPACE,
	SPACE_TAB
};

enum class ParanType: int8_t {
	PARAN_PARENTHESES,
};

enum class ValueType : int8_t {
	VALUE_INT,
};

enum class ElementType : int8_t {
	KEYWORD,
	SPACE,
	FUNC_NAME,
	PARENTHESES,
	NEW_LINE,
	VALUE
};

class PatternElement
{
protected:
	ElementType type;
	//std::vector <std::string> values;
	std::string value;

protected:
	virtual void GenValue() = 0;

	PatternElement(ElementType type, std::string value);
	~PatternElement();

public:
	//inline std::string GetValue() const { return values[0]; }		// [0] ???
	inline std::string GetValue() const { return value; }
};

class ElemKeyword : public PatternElement
{
private:
	KeywordType mod;
public:
	ElemKeyword(KeywordType mod);
	~ElemKeyword();
	
private:
	void GenValue();
};

class ElemSpace : public PatternElement
{
private:
	SpaceType mod;
public:
	ElemSpace(SpaceType mod);
	~ElemSpace();
	
private:
	void GenValue();
};

class ElemFuncName : public PatternElement
{
public:
	ElemFuncName();
	~ElemFuncName();

private:
	void GenValue();
};

class ElemParentheses : public PatternElement
{
private:
	ParanType mod;
public:
	ElemParentheses(ParanType mod);
	~ElemParentheses();

private:
	void GenValue();
};

class ElemNewLine : public PatternElement
{
public:
	ElemNewLine();
	~ElemNewLine();

private:
	void GenValue();
};

class ElemValue : public PatternElement
{
private:
	ValueType mod;
public:
	ElemValue(ValueType mod);
	~ElemValue();

private:
	void GenValue();
};
