#pragma once
#include <iomanip>
#include <string>
#include <typeinfo>
#include "AD_File.h"
#include "DataFile.h"

class Folder :public AD_File
{
	AD_File** arrAD;
	int sizeAD;
	string folderPath;
	
	Folder* findFolderPointer(string path, int currentPlace, string currentFolder, Folder* F);

public:
	static Folder root;
	Folder(string folderName, string foldderPath);
	string getFullPath();
	virtual ~Folder();
	virtual bool operator == (const AD_File& other) const;
	void addFileToArray(const AD_File *pad);
	Folder(const Folder& other, const string path);
	void mkfile(string fileName, string data);
	void mkDir(string _filename);
	Folder* intoFolder(string _folderName);
	void dir();
	static Folder* cd(string path)throw(const string);
	friend bool FC(Folder& currentDir, string source, string dest);


	
};

