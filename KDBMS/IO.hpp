#pragma once

#ifndef __IO_HPP__
#define __IO_HPP__

#include "Config.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Types.h"

using namespace std;
using namespace std::filesystem;

char *ReadFromFile(String name);
void WriteToFile(String name, char *data);
vector<directory_entry> EnumerateFiles(String directory);

#endif // __IO_HPP__
