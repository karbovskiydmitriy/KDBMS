#pragma once

#ifndef __KDBMS_HPP__
#define __KDBMS_HPP__

#include "Config.h"

#include <string>
#include <vector>
#include <iostream>

#include "Database.hpp"
#include "Interfaces.hpp"
#include "Serialization.hpp"
#include "Query.hpp"

using namespace std;

struct DllExport Manager : Serializeable
{
	String name;

	Manager(String name);
	~Manager();

	Response CreateDatabase(String name);
	Response Use(String name);
	Response Use(Database *database);
	Response DropDatabase(String name);
	Response DropDatabase(Database *database);
	void EnableLoggning(bool logging);

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;

private:
	bool logging = false;
	list<Database *> databases;
	Database *currentDatabase = nullptr;

	Database *FindDatabaseByName(String name);
	bool DeleteDatabase(Database *database);
};

// int main();

#endif // __KDBMS_HPP__
