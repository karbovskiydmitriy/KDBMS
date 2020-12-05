#pragma once

#ifndef __KDBMS_HPP__
#define __KDBMS_HPP__

#include "Config.h"

#include <string>
#include <vector>

#include "SQL.hpp"

using namespace std;

struct Manager
{
	Database *CreateDatabase(String name);
	Database *Use(String name);
	Database *Use(Database database);
	SQLResponse *DropDatabase(String name);
	SQLResponse *DropDatabase(Database database);
};

void main();
void SetupTests();

#endif // __KDBMS_HPP__
