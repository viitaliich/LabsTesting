#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

void check_file(const std::string& path);

std::string run_program(std::string path);

void modify_input_code(std::string& data, const std::string& path);