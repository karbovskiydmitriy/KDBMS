#pragma once

#ifndef __KDBDMS_TEST_HPP__
#define __KDBDMS_TEST_HPP__

#include "..\KDBMS\Export.hpp"

#pragma comment(lib, "KDBMS.lib")

int __cdecl main();
void Test1();
void Test2();
void Test3();
void Test4();
void Output(Manager *manager);
void Output(Database *database);
void Output(Table *table);
void Output(TableRow *row);

#endif // __KDBDMS_TEST_HPP__
