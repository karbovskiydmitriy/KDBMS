#pragma once

#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include <list>
#include <vector>

using namespace std;

struct TableField
{

};

struct TableRow
{

};

struct Table
{
	list<TableField> fields;

	Table();
};

#endif // __TABLE_HPP__
