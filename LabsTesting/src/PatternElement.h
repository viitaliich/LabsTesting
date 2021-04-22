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
protected:
	ElementType type;
	std::vector <std::string> values;		// ???
	std::string value;
	PatternElement* orig_val;

protected:
	PatternElement(ElementType type, std::string value);
	~PatternElement();

public:
	//inline std::string GetValue() const { return values[0]; }		// [0] ???
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
