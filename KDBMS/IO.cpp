#include "IO.hpp"

/*char *ReadFile(string name)
{
	fstream file;
	file.open(name, ios::in);

	if (file.is_open())
	{
		int length = 1024;
		char *buffer = new char[length];
		file.get((char *)buffer, length);
		file.close();

		return buffer;
	}

	return nullptr;
}*/

char *ReadFromFile(String name)
{
	ifstream file(name, ios::binary | ios::ate);
	streamsize size = file.tellg();
	file.seekg(0, ios::beg);

	vector<char> buffer((unsigned int)size);
	if (file.read(buffer.data(), size))
	{
		return buffer.data();
	}

	return nullptr;
}

void WriteToFile(String name, char *rows)
{
	ofstream file(name, ios::binary);
	file.write(rows, 100);
	file.close();
}

vector<directory_entry> EnumerateFiles(String directory)
{
	vector<directory_entry> result;

	for (directory_entry p : directory_iterator(directory))
	{
		result.push_back(p);
	}

	return result;
}
