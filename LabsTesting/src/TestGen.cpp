#include "TestGen.h"
#include <fstream>

// TODO: not sure about realization ???
std::string TestGen::ReadFile(const std::string& path) {
	std::ifstream file(path);
	std::string content;
	content.assign((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	return content;
}

void TestGen::Lex() {

}

void TestGen::Parse() {	// ???

}

void TestGen::Gen() {

}

TestGen::TestGen(const std::string& path)
	:
	path(path),
	stream(ReadFile(path))
{}

TestGen::~TestGen(){

}