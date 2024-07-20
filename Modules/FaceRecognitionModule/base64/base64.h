#ifndef BASE64
#define BASE64

#include <iostream>
#include <filesystem>
#include <fstream>

std::string toBase64(const std::string &input);
std::string FileToBinary(const std::string &file_path);

#endif