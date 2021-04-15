#pragma once

#include <string>

class TestGen
{
private:
	const std::string& path;
	const std::string stream;	// input file
public:
	// output buffer

private:
	std::string ReadFile(const std::string& file);
	void Lex();
	void Parse();	// ???
	void Gen();
public:
	TestGen(const std::string& path);
	~TestGen();

	inline const std::string GetStream() const { return stream; };
};

