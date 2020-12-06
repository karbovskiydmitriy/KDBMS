#include "KDBDMS_test.hpp"

int __cdecl main()
{
	SetupTests();

	// system("pause");

	return 0;
}

void SetupTests()
{
	Response r;
	Manager *manager;
	Database *db;
	Table *table;

	manager = new Manager(TEXT("Test session"));

	cout << TEXT("Opening ") << TEXT("My test database #1") << endl;

	r = manager->CreateDatabase(TEXT("My test database #1"));
	r = manager->CreateDatabase(TEXT("My test database #2"));
	r = manager->CreateDatabase(TEXT("My test database #3"));

	r = manager->Use(TEXT("My test database #1"));
	db = (Database *)r.data;

	cout << TEXT("Used ") << db->name << endl;

	vector<TableColumn> *columns = new vector<TableColumn>();
	columns->push_back(TableColumn(String(TEXT("id")), Type::LONG));
	columns->push_back(TableColumn(String(TEXT("name")), Type::STRING));
	columns->push_back(TableColumn(String(TEXT("age")), Type::SHORT));
	columns->push_back(TableColumn(String(TEXT("gender")), Type::ENUM));
	r = db->CreateTable(TEXT("Persons"), columns);

	table = (Table *)r.data;

	manager->DropDatabase(TEXT("My test database #1"));
}
