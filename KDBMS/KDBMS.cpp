#include "KDBMS.hpp"

void main()
{
	SetupTests();
}

void SetupTests()
{
	Manager manager;
	String myDatabaseName = String(TEXT("My test database"));

	manager.CreateDatabase(myDatabaseName);
	Database *dataBase = manager.Use(myDatabaseName);

	// dataBase->CreateTable("My test table");

	manager.DropDatabase(myDatabaseName);
}

Database *Manager::CreateDatabase(String name)
{
	return nullptr;
}

Database *Manager::Use(String name)
{
	return nullptr;
}

Database *Manager::Use(Database database)
{
	return nullptr;
}

SQLResponse *Manager::DropDatabase(String name)
{
	return nullptr;
}

SQLResponse *Manager::DropDatabase(Database database)
{
	return nullptr;
}