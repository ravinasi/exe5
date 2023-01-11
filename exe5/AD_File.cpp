#define _CRT_SECURE_NO_WARNINGS
#include "AD_File.h"

const int MAX = 256;

bool AD_File::isIligalChar(string s)
{
	if (s.find('<') != string::npos) return true;
	if (s.find('?') != string::npos) return true;
	if (s.find('>') != string::npos) return true;
	if (s.find('*') != string::npos) return true;
	if (s.find('|') != string::npos) return true;
	if (s.find('/') != string::npos) return true;
	if (s.find('\\') != string::npos) return true;
	if (s.find('"') != string::npos)return true;
	return false;
}

void AD_File::setName(string name)throw(const char*)
{

	if (isIligalChar(name))
	{
		throw "A file name can't contain the following characters: /:*?<>|\\";
	}

	FileName = name;
}

string AD_File::getTime()
{
	char buf[80];
	strftime(buf, sizeof(buf), "%d/%m/%Y %X", lastUpdateTime);
	return buf;
}

void AD_File::setTime()
{
	time_t now = time(0);
	lastUpdateTime = localtime(&now);
}

bool AD_File::operator==(const AD_File &other) const
{
	if (FileName == other.FileName)
		return true;
	return false;
}

