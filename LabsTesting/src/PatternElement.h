#pragma once

#include <cstdint>
#include <vector>
#include <string>

enum KeywordType {
	KEYWORD_DEF = 1,
	KEYWORD_RETURN
};

enum SpaceType {
	SPACE_SPACE = 1,
	SPACE_TAB
};

enum ParanType {
	PARAN_PARENTHESES = 1,
};

enum ValueType {
	VALUE_INT = 1,
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
	inline ElementType GetType() const { return type; }
	
	virtual inline int GetMod() const { return 0; }		// inline
};

class ElemKeyword : public PatternElement
{
private:
	int mod;
public:
	ElemKeyword(KeywordType mod);
	~ElemKeyword();

	int GetMod() const { return mod; }

	
private:
	void GenValue();
};

class ElemSpace : public PatternElement
{
private:
	//int mod;
public:
	ElemSpace(/*int mod*/);
	~ElemSpace();

	//int GetMod() const { return mod; }

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
	int mod;
public:
	ElemParentheses(int mod);
	~ElemParentheses();

	int GetMod() const { return mod; }


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
	int mod;
public:
	ElemValue(int mod);
	~ElemValue();

	int GetMod() const { return mod; }


private:
	void GenValue();
};
