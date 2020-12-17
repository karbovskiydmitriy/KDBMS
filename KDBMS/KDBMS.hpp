#pragma once

#ifndef __KDBMS_HPP__
#define __KDBMS_HPP__

#include "Config.hpp"

#include <string>
#include <vector>
#include <iostream>

#include "Database.hpp"
#include "Serializeable.hpp"
#include "SerializedObject.hpp"
#include "Response.hpp"

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
	bool Deserialize(SerializedObject object) override;

private:
	bool logging = false;
	list<Database *> databases;
	Database *currentDatabase = nullptr;

	Database *FindDatabaseByName(String name);
	bool DeleteDatabase(Database *database);
};

#endif // __KDBMS_HPP__
