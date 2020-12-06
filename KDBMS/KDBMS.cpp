#include "KDBMS.hpp"

/*int main()
{
	SetupTests();

	return 1;
}*/

Manager::Manager(String name)
{
	this->name = name;
}

Manager::~Manager()
{
	databases.clear();
}

Response Manager::CreateDatabase(String name)
{
	Database *database = new Database(name);

	databases.push_back(database);

	return Response(ErrorCode::OK, database);
}

Response Manager::Use(String name)
{
	Database *database = FindDatabaseByName(name);

	if (database != nullptr)
	{
		return Response(ErrorCode::OK, database);
	}
	else
	{
		return Response(ErrorCode::NOT_FOUND);
	}
}

Response Manager::Use(Database *database)
{
	if (database != nullptr)
	{
		currentDatabase = database;

		return Response(ErrorCode::OK, currentDatabase);
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

Response Manager::DropDatabase(String name)
{
	Database *database = FindDatabaseByName(name);

	if (database != nullptr)
	{
		return DropDatabase(database);
	}
	else
	{
		return Response(ErrorCode::NOT_FOUND);
	}
}

Response Manager::DropDatabase(Database *database)
{
	if (database != nullptr)
	{
		if (DeleteDatabase(database))
		{
			return Response(ErrorCode::OK);
		}
		else
		{
			return Response(ErrorCode::NOT_FOUND);
		}
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

Database *Manager::FindDatabaseByName(String name)
{
	for (const auto &iterator : databases)
	{
		if (iterator->name == name)
		{
			return iterator;
		}
	}

	return nullptr;
}

bool Manager::DeleteDatabase(Database *database)
{
	if (database != nullptr)
	{
		for (const auto &iterator : databases)
		{
			if (iterator == database)
			{
				databases.remove(database);
				delete database;

				return true;
			}
		}
	}

	return false;
}
