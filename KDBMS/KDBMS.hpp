#pragma once

#ifndef __KDBMS_HPP__
#define __KDBMS_HPP__

#include "Config.hpp"

#include <string>
#include <vector>
#include <iostream>

#include "Database.hpp"
#include "Printable.hpp"
#include "Response.hpp"

using namespace std;

struct DllExport Manager : Printable
{
	String name;

	Manager(String name);

	Response CreateDatabase(String name);
	Response Use(String name);
	Response Use(Database *database);
	Response DropDatabase(String name);
	Response DropDatabase(Database *database);

	String ToString() override;

private:
	list<Database *> databases;
	Database *currentDatabase = nullptr;

	Database *FindDatabaseByName(String name);
	bool DeleteDatabase(Database *database);
};

#endif // __KDBMS_HPP__
