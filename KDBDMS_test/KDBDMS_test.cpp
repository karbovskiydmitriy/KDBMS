#include "KDBDMS_test.hpp"

int __cdecl main()
{
	SetupTests();

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

	r = manager->Use(TEXT("My test database #1"));
	db = (Database *)r.data;

	cout << TEXT("Used ") << db->name << endl;

	vector<TableColumn> columns =
	{
		TableColumn(String(TEXT("id")), Type::LONG),
		TableColumn(String(TEXT("name")), Type::STRING),
		TableColumn(String(TEXT("age")), Type::USHORT)
	};
	r = db->CreateTable(TEXT("Persons"), &columns);

	table = (Table *)r.data;

	cout << endl << table->ToString() << endl;

	int64_t id = 1;

	r = table->Insert
	(
		new TableRow
		(
			table->columns,
			{
				Data(id++),
				Data(new String("Dmitriy")),
				Data((unsigned short)21)
			}
		)
	);
	r = table->Insert
	(
		new TableRow
		(
			table->columns,
			{
				Data(id++),
				Data(new String("foo")),
				Data((unsigned short)42)
			}
		)
	);
	r = table->Insert
	(
		new TableRow
		(
			table->columns,
			{
				Data(id++),
				Data(new String("bar")),
				Data((unsigned short)1337)
			}
		)
	);

	r = table->Update();

	r = table->Select(
		new Condition
		(
			String(TEXT("age")),
			Data((unsigned short)18),
			Type::USHORT,
			Comparison::GREATER_OR_EQUALS_THAN
		)
	);
	vector<TableRow *> *entries = (vector<TableRow *> *)r.data;

	if (entries->size() != 0)
	{
		for (int i = 0; i < (int)entries->size(); i++)
		{
			cout << entries->data()[i]->ToString() << endl;
		}
	}
	else
	{
		cout << "No entries!" << endl;
	}

	manager->DropDatabase(TEXT("My test database #1"));
}

bool Condition::Check(Data value)
{
	// TODO

	return false;
}
