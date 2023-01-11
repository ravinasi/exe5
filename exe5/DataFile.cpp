#include "DataFile.h"

DataFile::DataFile(string name, string data) :AD_File(name)
{
	this->data = data;
}

bool DataFile::operator==(const AD_File &other) const
{
	const DataFile* ptr = dynamic_cast<const DataFile*>(&other);
	if (!ptr)
	{
		cout << "not safe for pd to point base" << endl;
		exit(1);
	}
	if (AD_File::FileName == ptr->FileName )
		if (this->data == ptr->data)
			return true;
	return false;
}

int DataFile::getSize()
{
	int size = this->data.size();
	return size;
}


