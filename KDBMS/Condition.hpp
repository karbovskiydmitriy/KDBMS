#pragma once

#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__

#include "Config.hpp"

#include <string>

#include "Data.hpp"
#include "TableRow.hpp"
#include "Types.hpp"
#include "Comparison.hpp"
#include "Table.hpp"

using namespace std;

struct Table;

struct DllExport Condition
{
	int index;
	Type type;
	Data data;
	Comparison comparison;
	Condition *andCondition;
	Condition *orCondition;

	Condition(Table *table, String column, Data data, Comparison comparison, Condition *andCondition = nullptr, Condition *orCondition = nullptr);

	bool Check(vector<Data> row);
};

#endif // __CONDITION_HPP__
