#pragma once

#ifndef __KDBDMS_TEST_HPP__
#define __KDBDMS_TEST_HPP__

#include <Windows.h>
#include <iostream>
#include "..\KDBMS\Export.hpp"

#pragma comment(lib, "KDBMS.lib")

using namespace std;

int __cdecl main();
void SetupTests();

#endif // __KDBDMS_TEST_HPP__
