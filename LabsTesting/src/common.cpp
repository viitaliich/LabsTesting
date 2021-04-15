#include "common.h"

void check_file(const std::string& path) {
	std::fstream file;
	file.open(path);
	if (!file) {
		std::cout << "ERROR: cant find file [" << path << "]\n";
		exit(1);
	}
	file.close();
}