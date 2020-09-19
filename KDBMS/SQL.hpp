#pragma once

#ifndef __SQL_HPP__
#define __SQL_HPP__

#include <vector>
#include <string>

using namespace std;

struct Request
{
	string select;
	string from;
	string where;
	string orderby;
};

struct Response
{
	vector<string> data;
};

#endif // __SQL_HPP__
