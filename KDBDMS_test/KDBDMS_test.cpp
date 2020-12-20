#include "KDBDMS_test.hpp"

Manager *manager;
Database *db;
Table *table;
Response r;

vector<TableColumn> columns =
{
	TableColumn(String(TEXT("id")), Type::ULONG),
	TableColumn(String(TEXT("name")), Type::STRING),
	TableColumn(String(TEXT("age")), Type::USHORT)
};

vector<TableRow *> testRows =
{
	new TableRow
	(
		nullptr,
		{
			Data((unsigned long long)1),
			Data(new String(TEXT("Dmitriy"))),
			Data((unsigned short)21)
		}
	),
	new TableRow
	(
		nullptr,
		{
			Data((unsigned long long)2),
			Data(new String(TEXT("under18"))),
			Data((unsigned short)17)
		}
	),
	new TableRow
	(
		nullptr,
		{
			Data((unsigned long long)3),
			Data(new String(TEXT("foo"))),
			Data((unsigned short)42)
		}
	),
	new TableRow
	(
		nullptr,
		{
			Data((unsigned long long)4),
			Data(new String(TEXT("bar"))),
			Data((unsigned short)1337)
		}
	),
	new TableRow
	(
		nullptr,
		{
			Data((unsigned long long)5),
			Data(new String(TEXT("test"))),
			Data((unsigned short)9999)
		}
	)
};

int __cdecl main()
{
	Test1();

	system("pause");

	Test2();

	system("pause");

	Test3();

	system("pause");

	Test4();

	system("pause");

	return 0;
}

void Test1()
{
	cout << endl << TEXT("Test #1") << endl;

	manager = new Manager(TEXT("Test manager #1"));

	Output(manager);

	r = manager->CreateDatabase(TEXT("My test database #1"));
	r = manager->CreateDatabase(TEXT("My test database #2"));
	r = manager->CreateDatabase(TEXT("My test database #3"));
	r = manager->CreateDatabase(TEXT("My test database #4"));
	r = manager->CreateDatabase(TEXT("My test database #5"));

	Output(manager);

	r = manager->DropDatabase(TEXT("My test database #1"));
	r = manager->DropDatabase(TEXT("My test database #2"));
	r = manager->DropDatabase(TEXT("My test database #3"));
	r = manager->DropDatabase(TEXT("My test database #4"));
	r = manager->DropDatabase(TEXT("My test database #5"));

	Output(manager);

	delete manager;
}

void Test2()
{
	cout << endl << TEXT("Test #2") << endl;

	manager = new Manager(TEXT("Test manager #2"));
	r = manager->CreateDatabase(TEXT("My test database #2"));
	db = (Database *)r.data;
	r = db->CreateTable(TEXT("Persons"), &columns);
	table = (Table *)r.data;

	for (int i = 0; i < (int)testRows.size(); i++)
	{
		testRows.data()[i]->columns = table->columns;
		r = table->Insert(testRows.data()[i]);
	}

	Output(table);

	Condition *deleteCondition = new Condition
	(
		table,
		String(TEXT("id")),
		Data((unsigned long long)3),
		Comparison::LESS_THAN,
		nullptr,
		new Condition
		(
			table,
			String(TEXT("id")),
			Data((unsigned long long)3),
			Comparison::GREATER_THAN
		)
	);

	r = table->Delete(deleteCondition);
	delete deleteCondition;

	Output(table);

	manager->DropDatabase(TEXT("My test database #2"));

	delete manager;
}

void Test3()
{
	cout << endl << TEXT("Test #3") << endl;

	manager = new Manager(TEXT("Test manager #3"));
	r = manager->CreateDatabase(TEXT("My test database #3"));
	db = (Database *)r.data;
	r = db->CreateTable(TEXT("Persons"), &columns);
	table = (Table *)r.data;

	for (int i = 0; i < (int)testRows.size(); i++)
	{
		testRows.data()[i]->columns = table->columns;
		r = table->Insert(testRows.data()[i]);
	}

	Output(table);

	Condition *updateCondition = new Condition
	(
		table,
		String(TEXT("age")),
		Data((unsigned short)18),
		Comparison::GREATER_OR_EQUALS_THAN
	);
	table->Update(updateCondition, String(TEXT("name")), Data(new String(TEXT("Oldman"))));

	Output(table);

	manager->DropDatabase(TEXT("My test database #3"));

	delete manager;
}

void Test4()
{
	cout << endl << TEXT("Test #4") << endl;

	manager = new Manager(TEXT("Test manager #4"));
	r = manager->CreateDatabase(TEXT("My test database #4"));
	db = (Database *)r.data;
	r = db->CreateTable(TEXT("Persons"), &columns);
	table = (Table *)r.data;

	for (int i = 0; i < (int)testRows.size(); i++)
	{
		testRows.data()[i]->columns = table->columns;
		r = table->Insert(testRows.data()[i]);
	}

	Output(table);

	r = db->SaveToFile(String(TEXT("db.BIN")));

	table->Delete(nullptr);

	Output(table);

	r = db->LoadFromFile(String(TEXT("db.BIN")));
	r = db->FindTable(TEXT("Persons"));
	table = (Table *)r.data;

	Output(table);

	manager->DropDatabase(TEXT("My test database #4"));

	delete manager;
}

void Output(Manager *manager)
{
	cout << manager->ToString() << endl << endl;
}

void Output(Database *database)
{
	cout << database->ToString() << endl << endl;
}

void Output(Table *table)
{
	cout << table->ToString() << endl << endl;
	Response r = table->Select(nullptr);
	vector<TableRow *> *entries = (vector<TableRow *> *)r.data;

	if (entries->size() != 0)
	{
		for (int i = 0; i < (int)entries->size(); i++)
		{
			Output(entries->data()[i]);
		}
	}
	else
	{
		cout << TEXT("No entries!") << endl;
	}

	cout << endl;
}

void Output(TableRow *row)
{
	cout << row->ToString() << endl;
}
