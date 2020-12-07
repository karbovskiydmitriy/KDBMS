#include "KDBMS.hpp"

/*int main()
{
	SetupTests();

	return 1;
}*/

Manager::Manager(String name)
{
	this->name = name;

	cout << "Starting KDBMS..." << endl;
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
	else
	{
		if (this->currentDatabase != nullptr)
		{
			delete currentDatabase;

			currentDatabase = nullptr;

			return Response(ErrorCode::OK);
		}
		else
		{
			return Response(ErrorCode::NULL_ARGUMENT);
		}
	}
}

void Manager::EnableLoggning(bool logging)
{
	this->logging = logging;

	cout << (logging ? TEXT("Logging enabled") : TEXT("Logging disabled")) << endl;
}

SerializedObject Manager::Serialize()
{
	return SerializedObject();
}

bool Manager::Deserialize(char *rows)
{
	return false;
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
