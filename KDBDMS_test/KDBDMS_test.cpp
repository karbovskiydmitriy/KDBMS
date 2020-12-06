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
	Table *table;

	manager = new Manager(TEXT("Test session"));

	print(TEXT("Opening %s\n"), TEXT("My test database #1"));

	r = manager->CreateDatabase(TEXT("My test database #1"));
	r = manager->CreateDatabase(TEXT("My test database #2"));
	r = manager->CreateDatabase(TEXT("My test database #3"));

	r = manager->Use(TEXT("My test database #1"));
	db = (Database *)r.data;

	print(TEXT("Used %s\n"), db->name.c_str());

	r = db->CreateTable(TEXT("My test table #1"), nullptr);
	r = db->CreateTable(TEXT("My test table #2"), nullptr);
	r = db->CreateTable(TEXT("My test table #3"), nullptr);
	r = db->CreateTable(TEXT("My test table #4"), nullptr);

	table = (Table *)r.data;
	cout << table->name << endl;

	manager->DropDatabase(TEXT("My test database #1"));
}
