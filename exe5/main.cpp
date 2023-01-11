#pragma once
#include <iostream>
#include "DataFile.h"
#include "Folder.h"
#include <iostream>
#include <typeinfo>
using namespace std;

void main()
{
	Folder* root = &Folder::root;
	root->mkDir("C:");
	root->mkDir("D:");

	/*Folder* current = &Folder::root;
	current = root->intoFolder("C:");
	current->mkDir("newfolder");
	current = Folder::cd("C:\\newfolder");*/


	Folder* curr = Folder::cd("C:");
	bool quit = false; string path;
	string command, p_command;
	char echoStream[256];
	do {
		std::cout << curr->getFullPath() << ">";//deletes Root Folder Name
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> command;
		try {
			if (command == "cd") {
				cin.ignore(1);
				cin >> p_command;
				curr = Folder::cd(p_command);
				continue;
			}
			if (command == "mkdir") {
				cin.ignore(1);
				cin >> p_command;
				curr->mkDir(p_command);
				continue;
			}
			if (command == "dir") {
				curr->dir();
				continue;
			}
			if (command == "echo") {
				cin.ignore(1);
				std::cin.getline(echoStream, 256);
				command = echoStream;
				curr->mkfile(command.substr(command.find('<') + 2),
					command.substr(0, command.find('<') - 1));
				continue;
			}
			/*if (command == "FC") {
				cin.ignore(1);
				cin >> p_command;
				cin.ignore(1);
				cin >> command;
				if (fc(*curr, p_command, command) == true)
					cout << " equals\n";
				else
					cout << " not equals\n";
				continue;
			}*/
		}
		catch (const char* msg) { cout << msg << endl; }
		catch (...) {
			std::cout << "unhandeled eception";
		};
		break;
	} while (!quit);
}






//void main()
//{
//	Folder folder_main("folder_main", "main");
//	DataFile file1("file1.txt", "empty");
//	DataFile file2("file2.txt", "dsbkhc");
//	Folder folder1("folder1", " ");
//	Folder folder2("folder2", " ");
//	try {
//		
//		folder_main.addFileToArray(&file1);
//		folder_main.addFileToArray(&file2);
//		folder_main.mkfile("file3.txt", "");
//		folder_main.addFileToArray(&folder1);
//		folder_main.addFileToArray(&folder2);
//		folder_main.mkDir("folder3");
//		folder_main.dir();
//		
//	}
//	catch(const char* error)
//	{
//		cout << error << endl;
//	}
//	catch (const string error)
//	{
//		cout << error << endl;
//	}
//	catch (...)
//	{
//		cout << " unexpected error" << endl;
//	}
//}