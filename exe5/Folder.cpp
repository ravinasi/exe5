#include "Folder.h"
const int FOLDER = 0;

Folder Folder::root("root", "");

Folder::Folder(string folderName, string foldderPath) : AD_File::AD_File(folderName)
{
	this->folderPath = foldderPath;
	sizeAD = 0;
	arrAD = NULL;
}

string Folder::getFullPath()
{
	return folderPath;
}

Folder::~Folder()
{
	for (int i = 0; i < sizeAD; i++)
	{
		delete arrAD[i];
	}
	delete[] arrAD;
}

bool Folder::operator==(const AD_File& other) const throw(const char*)
{
	const Folder* ptr = dynamic_cast<const Folder*>(&other);
	if (!ptr)
		throw "not safe for pd to point base";
	if (sizeAD == ptr->sizeAD)
	{
		for (int i = 0; i < sizeAD; i++)
		{
			if (!strcmp(typeid(arrAD[i]).name(), "class DataFile")) // check all data files in array
				if (!strcmp(typeid(ptr->arrAD[i]).name(), "class DataFile"))
				{
					if ((*(DataFile*)arrAD[i]).getNmae() != (*(DataFile*)ptr->arrAD[i]).getNmae())
						return false;
				}
		}
		for (int i = 0; i < sizeAD; i++)
		{
			if(!strcmp(typeid(arrAD[i]).name(), "class Folder")) // check all folders
				if (!strcmp(typeid(ptr->arrAD[i]).name(), "class Folder"))
				{
					if ((*(Folder*)arrAD[i]) == (*(Folder*)ptr->arrAD[i]))
						break;
					else return false;
				}
		}

	}
	
	return true;
}

void Folder::addFileToArray(const AD_File* pad)throw(const char*)
{	
	int type = FOLDER; //if file foler = 0;
	if (!strcmp(typeid(*pad).name(), "class DataFile"))  // pointer to data file
	{
		type = 1;
		for (int i = 0; i < sizeAD; i++)
		{
			if (!strcmp(typeid(arrAD[i][0]).name(), "class DataFile"))
				if (*(DataFile*)arrAD[i] == *(DataFile*)pad)
					throw "File allready exists";
		}
	}
	else // pointer to folder
	{
		for (int i = 0; i < sizeAD; i++)
		{
			if (!strcmp(typeid(arrAD[i][0]).name(), "class Folder"))
				if (((Folder*)arrAD[i])->getNmae() == (*(Folder*)pad).getNmae())
					throw "File allready exists";
		}
	}


	AD_File** temp = new AD_File * [sizeAD];
	for (int i = 0; i < sizeAD; i++) // copy to temp array and delete the old one
	{
		if (!strcmp(typeid(arrAD[i][0]).name(), "class Folder"))
		{
			temp[i] = new Folder(((Folder*)arrAD[i])->FileName, ((Folder*)arrAD[i])->folderPath);
			delete arrAD[i];
		}
		else
		{
			temp[i] = new DataFile(*(DataFile*)arrAD[i]);
			delete arrAD[i];
		}
	}
	delete[] arrAD;

	sizeAD++;
	arrAD = new AD_File * [sizeAD]; // allocate new array
	for (int i = 0; i < sizeAD-1; i++)
	{
		if (!strcmp(typeid(temp[i][0]).name(), "class Folder"))
		{
			arrAD[i] = new Folder(((Folder*)temp[i])->FileName, ((Folder*)temp[i])->folderPath);
			delete temp[i];
		}
		else
		{
			arrAD[i] = new DataFile(*(DataFile*)temp[i]);
			delete temp[i];
		}
	}
	delete[] temp;
	if (type == 1)
		arrAD[sizeAD - 1] = new DataFile(*(DataFile*)pad);
	else arrAD[sizeAD - 1] = new Folder(((Folder*)pad)->FileName,((Folder*)pad)->folderPath);
}

Folder::Folder(const Folder& other, const string path): AD_File::AD_File(other.FileName)
{
	folderPath = path;
	for (int i = 0; i < sizeAD; i++) // delete old array 
		delete arrAD[i];
	delete[] arrAD;

	sizeAD = other.sizeAD;
	arrAD = new AD_File * [sizeAD];
	
	for (int i = 0; i < sizeAD; i++)
	{
		if (!strcmp(typeid(other.arrAD[i]).name(), "class DataFile"))
		{
			
			arrAD[i] = new DataFile(*(DataFile*)other.arrAD[i]);
		}
		else arrAD[i] = new Folder(other.arrAD[i]->getNmae(), path);
	}
}

void Folder::mkfile(string fileName, string data)
{
	DataFile d(fileName, data);
	this->addFileToArray(&d);
}

void Folder::mkDir(string _filename)
{
	string newpath = this->folderPath;
	if (newpath.size())
		newpath += "\\";
	newpath += _filename;
	Folder newfolder(_filename, newpath);
	this->addFileToArray(&newfolder);
}

void Folder::dir()
{
	cout << "________________________________" << endl;
	cout << "Files in folder " << this->FileName << ":" << endl;
	for (int i = 0; i < sizeAD; i++)
	{
		if (!strcmp(typeid(arrAD[i][0]).name(), "class Folder"))
			cout << arrAD[i]->getTime() << "   <DIR>\t     " << arrAD[i]->getNmae() << endl;
		else
		{
			int size = ((DataFile*)arrAD[i])->getSize();
			float size_f = (float)size / 1024;
			cout << arrAD[i]->getTime() << "\t\t";
			cout << fixed << setprecision(2) << size_f << " KB " << arrAD[i][0].getNmae() << endl;
		}
	}
}

Folder* Folder::cd(string path) throw(const string)
{
	int findNext = path.find_first_of(92);
	string goinFolder = path.substr(0, findNext); // what folder to get int
	///Folder Fptr = Folder::root;
	Folder* proot = &Folder::root;
	path = path.substr(findNext + 1);
	return Folder::root.findFolderPointer(path, findNext, goinFolder, proot);
}

Folder* Folder::findFolderPointer(string path, int findNext, string goinFolder, Folder* Fptr)
{
	if (findNext == -1)
	{
		Fptr= Fptr->intoFolder(goinFolder);
		return Fptr;
	}
	Fptr = Fptr->intoFolder(goinFolder);
	findNext = path.find_first_of(92);
	goinFolder = path.substr(0, findNext);
	path = path.substr(findNext + 1);
	Fptr = Fptr->findFolderPointer(path, findNext, goinFolder, Fptr);
	return Fptr;
}

Folder* Folder::intoFolder(string _foldername) throw (const string)
{
	for (int i = 0; i < sizeAD; i++)
	{
		if(!strcmp(typeid(arrAD[i][0]).name(), "class Folder"))
			if (arrAD[i][0].getNmae() == _foldername)
			{
				return (Folder*)arrAD[i];
			}
	}
	throw "folder does not exist in this folder";
}

bool FC(Folder& currentDir, string source, string dest)
{
	
	return false;
}
