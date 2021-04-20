#pragma once

#include <string>
#include <vector>

#include "PatternElement.h"

enum class LabNumber : uint8_t {
	LAB1 = 1
};

class TestGen
{
private:
	uint8_t lab_num;
	std::vector <PatternElement*> pattern;

public:
	// output buffer

private:
	std::string ReadFile(const std::string& file);
	void Correct();
	void Incorrect();
	void GenPattern();
public:
	TestGen(uint8_t lab_num);
	~TestGen();
	
	void Generate();

	//inline const std::string GetStream() const { return stream; };
};

