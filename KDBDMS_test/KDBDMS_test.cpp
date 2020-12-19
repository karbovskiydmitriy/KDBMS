#include "KDBDMS_test.hpp"

int __cdecl main()
{
	Test();

	system("pause");

	return 0;
}

void Test()
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
				Data(new String(TEXT("Dmitriy"))),
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
				Data(new String(TEXT("under18"))),
				Data((unsigned short)17)
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
				Data(new String(TEXT("foo"))),
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
				Data(new String(TEXT("bar"))),
				Data((unsigned short)1337)
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
				Data(new String(TEXT("test"))),
				Data((unsigned short)9999)
			}
		)
	);

	Condition *condition18 = new Condition
	(
		table,
		String(TEXT("age")),
		Data((unsigned short)18),
		Comparison::GREATER_OR_EQUALS_THAN
	);

	// SerializedObject testSO = table->Serialize();

	r = table->Select
	(
		nullptr
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
		cout << TEXT("No entries!") << endl;
	}

	Condition *updateCondition = new Condition
	(
		table,
		String(TEXT("age")),
		Data((unsigned short)18),
		Comparison::GREATER_OR_EQUALS_THAN
	);

	table->Update(updateCondition, String(TEXT("name")), Data(new String(TEXT("Oldman"))));

	r = table->Select();
	entries = (vector<TableRow *> *)r.data;

	SerializedObject object = table->columns->data()[0].Serialize();
	bool result = table->columns->data()[0].Deserialize(object);

	for (const auto &row : table->rows)
	{
		SerializedObject obj = row->Serialize();
		TableRow tableRow = TableRow(table->columns, vector<Data>());
		tableRow.Deserialize(obj);
	}

	SerializedObject serializedTable = table->Serialize();
	result = table->Deserialize(serializedTable);

	SerializedObject serializedDatabse = db->Serialize();
	result = db->Deserialize(serializedDatabse);

	cout << endl << table->ToString() << endl;

	if (entries->size() != 0)
	{
		for (int i = 0; i < (int)entries->size(); i++)
		{
			cout << entries->data()[i]->ToString() << endl;
		}
	}
	else
	{
		cout << TEXT("No entries!") << endl;
	}

	manager->DropDatabase(TEXT("My test database #1"));
}
