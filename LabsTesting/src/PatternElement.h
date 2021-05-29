#pragma once

#include <cstdint>
#include <vector>
#include <string>

enum ModKeyword : uint8_t {
	KEYWORD_DEF = 1,
	KEYWORD_RETURN,
	KEYWORD_NOT,
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
	VALUE_STR,
	VALUE_BASE,
};

//// ???
//enum ModUnOp : uint8_t {
//	OP_UN_BITCOMP = 1,
//	OP_UN_NOT,
//	OP_UN_NEG,
//};
//
//// ???
//enum ModBinOp : uint8_t {
//	OP_BIN_NEG = 1,
//	OP_BIN_ADD,
//	OP_BIN_MUL,
//	OP_BIN_DIV,
//};

enum ModOp : uint8_t {
	OP_UN_BITCOMP = 1,
	OP_UN_NOT,
	OP_UN_NEG,
	OP_BIN_NEG,
	OP_BIN_ADD,
	OP_BIN_MUL,
	OP_BIN_DIV,
};

//enum ModOp : uint8_t {
//	OP_UNARY = 1,
//	OP_BINARY,
//};

enum ModSpSym : uint8_t {
	SP_SYM_AND = 1,
	SP_SYM_DOL,
	SP_SYM_PERC,
	SP_SYM_COLON,
	SP_SYM_SEMI,
	SP_SYM_QUEST,
	SP_SYM_DOG,
	SP_SYM_LINE,
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

	TYPE_OP,

	TYPE_EOF,
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
	//virtual void SetPVIter(std::vector<ElemValue*>::iterator pv_iter);

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
	std::vector<ElemValue*> possible_values;
	std::vector<ElemValue*>::iterator pv_iter;
	//static std::vector <ElemValue*>::iterator i;
public:
	ElemValue(uint8_t mod, std::vector<ElemValue*> values);
	~ElemValue();
	std::string GetValue();

	void SaveOrigElem();
	
	inline int GetMod() const { return mod; }
};

class BaseValue : public PatternElement {
//private:
public:
	std::vector<ElemValue*> possible_values;
	std::vector<ElemValue*>::iterator pv_iter;
	void SaveOrigElem();
public:
	BaseValue(std::vector<ElemValue*> values);
	~BaseValue();
};

class ElemUnOperation : public PatternElement
{
private:
	uint8_t mod;
public:
public:
	ElemUnOperation(uint8_t mod);
	~ElemUnOperation();
	std::string GetValue();

	void SaveOrigElem();

	inline int GetMod() const { return mod; }
};

class ElemBinOperation : public PatternElement
{
private:
	uint8_t mod;
public:
public:
	ElemBinOperation(uint8_t mod);
	~ElemBinOperation();
	std::string GetValue();

	void SaveOrigElem();

	inline int GetMod() const { return mod; }
};

class ElemEOF : public PatternElement
{
public:
	ElemEOF();
	~ElemEOF();
	
	void SaveOrigElem();
};