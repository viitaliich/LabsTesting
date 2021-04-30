#pragma once

#include <cstdint>
#include <vector>
#include <string>

enum ModKeyword : uint8_t {
	KEYWORD_DEF = 1,
	KEYWORD_RETURN
};

// do we need this ???
enum ModSpace : uint8_t {
	SPACE_SPACE = 1,
	SPACE_TAB
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
	VALUE_STR
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
public:
	ElemName(std::string name);
	~ElemName();

	void SaveOrigElem();
};

class ElemLeftBracket : public PatternElement
{
private:
	uint8_t mod;
public:
	ElemLeftBracket(uint8_t mod);
	~ElemLeftBracket();

	void SaveOrigElem();
	
	inline int GetMod() const { return mod; }
};

class ElemRightBracket : public PatternElement
{
private:
	uint8_t mod;
public:
	ElemRightBracket(uint8_t mod);
	~ElemRightBracket();

	void SaveOrigElem();
	
	inline int GetMod() const { return mod; }
};

class ElemColon : public PatternElement
{
public:
	ElemColon();
	~ElemColon();

	void SaveOrigElem();
};

class ElemNewLine : public PatternElement
{
public:
	ElemNewLine();
	~ElemNewLine();
	
	void SaveOrigElem();
};

class ElemValue : public PatternElement
{
private:
	uint8_t mod;
public:
	ElemValue(uint8_t mod);
	~ElemValue();

	void SaveOrigElem();
	
	inline int GetMod() const { return mod; }
};

class BaseValue : public PatternElement {
private:
	std::vector<ElemValue*> possible_values;
	void SaveOrigElem();
public:
	BaseValue(std::vector<ElemValue*> values);
	~BaseValue();
};
