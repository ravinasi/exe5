#pragma once
#include <typeinfo>
#include "AD_File.h"

class DataFile :public AD_File
{
	string data;

public:
	DataFile(string name, string data);
	virtual bool operator == (const AD_File &other) const;
	int getSize();

};
