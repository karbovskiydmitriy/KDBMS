#include "IO.hpp"

vector<byte> *ReadFromFile(String name)
{
	ifstream file(name, ios::binary | ios::ate);
	streamsize size = file.tellg();
	file.seekg(0, ios::beg);

	char *buffer = new char[(unsigned)size];
	if (file.read(buffer, size))
	{
		vector<byte> *data = new vector<byte>((const unsigned int)size);
		memcpy(data->data(), buffer, (size_t)size);

		return data;
	}

	return nullptr;
}

void WriteToFile(String name, vector<byte> *data)
{
	ofstream file(name, ios::binary);
	file.write((const char *)data->data(), data->size());
	file.close();
}
