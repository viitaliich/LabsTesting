#pragma once

#include <cstdint>
#include <vector>
#include <string>

enum KeywordType : int8_t {
	KEYWORD_DEF = 1,
	KEYWORD_RETURN
};

enum SpaceType : int8_t {
	SPACE_SPACE = 1,
	SPACE_TAB
};

enum BracketType : int8_t {
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

enum ValueType : int8_t {
	VALUE_INT_DEC = 1,
	VALUE_INT_BIN,
	VALUE_INT_OCT,
	VALUE_INT_HEX,
	VALUE_FLOAT,
	VALUE_STR
};

enum class ElementType : int8_t {
	TYPE_KEYWORD,
	TYPE_SPACE,
	TYPE_NAME,
	TYPE_BRACKET,
	TYPE_COLON,
	TYPE_NEW_LINE,
	TYPE_VALUE
};


class PatternElement
{
protected:
	ElementType type;
	std::string value;
	PatternElement* orig_val;

protected:
	PatternElement(ElementType type, std::string value);
	~PatternElement();

public:
	void SetValue(std::string value);

	virtual void SaveOrigElem() = 0;		
	void RestoreOrigElem();
	
	inline std::string GetValue() const { return value; }
	inline ElementType GetType() const { return type; }
	
	virtual inline int GetMod() const { return 0; }

};

class ElemKeyword : public PatternElement
{
private:
	int mod;
public:
	ElemKeyword(int mod);
	~ElemKeyword();

	void SaveOrigElem();
	void RestoreOrigElem();
	

	inline int GetMod() const { return mod; }
};

class ElemSpace : public PatternElement
{
public:
	ElemSpace();
	~ElemSpace();

	void SaveOrigElem();
	void RestoreOrigElem();
};

class ElemFuncName : public PatternElement
{
public:
	ElemFuncName(std::string name);
	~ElemFuncName();

	void SaveOrigElem();
	void RestoreOrigElem();
};

class ElemLeftBracket : public PatternElement
{
private:
	int mod;
public:
	ElemLeftBracket(int mod);
	~ElemLeftBracket();

	void SaveOrigElem();
	void RestoreOrigElem();
	
	inline int GetMod() const { return mod; }
};

class ElemRightBracket : public PatternElement
{
private:
	int mod;
public:
	ElemRightBracket(int mod);
	~ElemRightBracket();

	void SaveOrigElem();
	void RestoreOrigElem();
	
	inline int GetMod() const { return mod; }
};

class ElemColon : public PatternElement
{
public:
	ElemColon();
	~ElemColon();

	void SaveOrigElem();
	void RestoreOrigElem();
};

class ElemNewLine : public PatternElement
{
public:
	ElemNewLine();
	~ElemNewLine();
	
	void SaveOrigElem();
	void RestoreOrigElem();
};

class ElemValue : public PatternElement
{
private:
	int mod;
public:
	ElemValue(int mod);
	~ElemValue();

	void SaveOrigElem();
	void RestoreOrigElem();
	
	inline int GetMod() const { return mod; }
};
