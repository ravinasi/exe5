#pragma once
#include <iostream>
#include <cstring>
using namespace std;

class AD_File
{

protected:
	string FileName;
	tm* lastUpdateTime;

	bool isIligalChar(string s);

public:
	AD_File(string name) { this->setName(name); setTime(); };
	string getNmae() const { return FileName; };
	void setName(string name);
	string getTime();
	void setTime();
	virtual bool operator == (const AD_File &other) const;
	virtual ~AD_File() {};

};

