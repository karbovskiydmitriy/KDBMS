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
	std::ifstream file(name, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	if (file.read(buffer.data(), size))
	{
		return buffer.data();
	}

	return nullptr;
}

void WriteToFile(String name, char *data)
{
	std::ofstream file(name, std::ios::binary);
	file.write(data, 100);
	file.close();
}

vector<directory_entry> EnumerateFile(String directory)
{
	vector<directory_entry> result;

	for (directory_entry p : directory_iterator(directory))
	{
		result.push_back(p);
	}

	return result;
}	
