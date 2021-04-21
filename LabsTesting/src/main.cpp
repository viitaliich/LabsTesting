// TODO: 
//	path mechanism
//	format

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <fstream>

#include "common.h"
#include "TestGen.h"

// declarations
std::string run_program(std::string& path);
void modify_input_code();

// definitions

std::string run_program(std::string& path) {
	
	check_file(path);

	// TODO: it can be replaced with identification by thread number (thread ID)

	size_t index = path.length()-1;
	while (path[index] != '.' && index > 0) {
		index--;
	}
	size_t name_end = index - 1;

	while (path[index] != '\\' && index > 0) {
		index--;
	}
	size_t name_start = index + 1;

	size_t length = 0;
	if (name_end != 0 && name_start != 0 && name_end != name_start)
		length = name_end - name_start + 1;
	else {
		std::cout << "ERROR: file path is wrong\n";
		exit(1);
	}
	std::string file_name = path.substr(name_start, length);	// +".txt";
	
	std::stringstream ss;
	ss << path << " > " << file_name;
	std::string cmd(ss.str());
	ss << system(cmd.c_str());

	std::ifstream res_file;
	res_file.open(file_name);
	if (res_file.is_open()) {
		std::string res;
		getline(res_file, res);
		res_file.close();
		return res;
	}
	else {
		std::cout << "ERROR: file [" << file_name << "] is not opened\n";
		exit(1);
	}
}

void modify_input_code(std::string& data, const std::string& path) {
	check_file(path);

	std::ofstream file(path);
	file << data;
	file.close();
}


int main(int argc, char** argv) {
	
	TestGen* tg = new TestGen(1);
	tg->Generate();
	std::cout << "DONE";


	//getchar();
	return 0;
}