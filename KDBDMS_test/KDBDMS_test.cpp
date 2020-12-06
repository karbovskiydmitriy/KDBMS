#include "KDBDMS_test.hpp"

int __cdecl main()
{
	SetupTests();

	system("pause");

	return 0;
}

void SetupTests()
{
	Response r;
	Manager *manager;
	Database *db;

	manager = new Manager(TEXT("Test session"));
	String myDatabaseName = String(TEXT("My test database"));

	print(TEXT("Opening %s\n"), myDatabaseName.c_str());

	manager->CreateDatabase(myDatabaseName);
	manager->CreateDatabase(TEXT("123"));
	manager->CreateDatabase(TEXT("ABC"));

	r = manager->Use(myDatabaseName);

	db = (Database *)r.data;

	print(TEXT("Used %s\n"), db->name.c_str());

	db->CreateTable(TEXT("My test table"), nullptr);

	manager->DropDatabase(myDatabaseName);
}
