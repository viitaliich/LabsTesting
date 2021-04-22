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

enum BracketType {
	BRACKET_PAREN = 1,
};

enum ValueType {
	VALUE_INT = 1,
};

enum class ElementType : int8_t {
	KEYWORD,
	SPACE,
	FUNC_NAME,
	BRACKET,
	NEW_LINE,
	VALUE
};





class PatternElement
{
//protected:
public:
	ElementType type;
	//std::vector <std::string> values;
	std::string value;

protected:
	virtual void GenValue() = 0;		// ???


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
	ElemFuncName(std::string name);
	~ElemFuncName();

private:
	void GenValue();
};

class ElemLeftBracket : public PatternElement
{
private:
	int mod;
public:
	ElemLeftBracket(int mod);
	~ElemLeftBracket();

	int GetMod() const { return mod; }
private:
	void GenValue();
};

class ElemRightBracket : public PatternElement
{
private:
	int mod;
public:
	ElemRightBracket(int mod);
	~ElemRightBracket();

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
