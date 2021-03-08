#pragma once 

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

std::string read_file(const std::filesystem::path& path) {
    auto input_file = std::ifstream(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file: " << path << '\n';
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}