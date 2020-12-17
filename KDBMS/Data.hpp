#pragma once

#ifndef __DATA_HPP__
#define __DATA_HPP__

#include "Config.hpp"

#include <vector>
#include <list>

#include "Types.hpp"

using namespace std;

typedef vector<char> Blob;

struct DllExport Enum
{
	String value;
	list<String> values;
};

struct DllExport Date
{
	int day;
	int month;
	int year;
};

struct DllExport Time
{
	int second;
	int minute;
	int hour;
};

struct DllExport DateTime
{
	Date date;
	Time time;
};

union DllExport Data
{
	Pointer pointer;
	uint64_t value;
	float singlePrecisionFloating;
	double doublePrecisionFloating;

	Data(Type type = Type::NONE, uint64_t data = 0);
	Data(bool data);
	Data(char data);
	Data(signed char data);
	Data(unsigned char data);
	Data(signed short int data);
	Data(unsigned short int data);
	Data(signed long int data);
	Data(unsigned long int data);
	Data(signed long long int data);
	Data(unsigned long long int data);
	Data(float data);
	Data(double data);
	Data(String *data);
	Data(Enum *data);
	Data(Date *data);
	Data(Time *data);
	Data(DateTime *data);
	Data(Blob *data);
	Data(Pointer *array);
};

#endif // __DATA_HPP__
