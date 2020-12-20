#pragma once

#ifndef __IO_HPP__
#define __IO_HPP__

#include "Config.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Types.hpp"
#include "Data.hpp"

using namespace std;
using namespace std::filesystem;

vector<byte> *ReadFromFile(String name);
void WriteToFile(String name, vector<byte> *data);

#endif // __IO_HPP__
