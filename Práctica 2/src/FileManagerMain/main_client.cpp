/**
 * N�stor P�rez
 * github.com/prryplatypus
 */
#include <iostream>
#include <string>
#include "FileManagerStub.h"


std::string getInput()
{
	std::string input;
	std::cout << "someone@mycode:$~ ";
	getline(std::cin, input);
	return input;
}


std::string extractCommand(std::string input)
{
	size_t pos = input.find(' ');
	return (pos != std::string::npos) ? input.substr(0, pos) : input;
}


std::string extractParameters(std::string input)
{
	size_t pos = input.find(' ');
	return (pos != std::string::npos) ? input.substr(pos + 1) : std::string("");
}


int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cout << "ERROR: Please make sure you provide all required parameters (";
		std::cout << argv[0] << " <ip> <port>)" << std::endl;
		return -1;
	}

	FileManagerStub* fm;
	try {
		fm = nnew FileManagerStub(argv[1], std::stoi(argv[2]), "./dirprueba");
	}
	catch (std::invalid_argument) {
		std::cout << "Invalid port provided" << std::endl;
		return -1;
	}

	bool stop = false;
	std::cout << "Available commands:" << std::endl;
	std::cout << "\t- ls" << std::endl;
	std::cout << "\t- up" << std::endl;
	std::cout << "\t- upload" << std::endl;
	std::cout << "\t- down" << std::endl;
	std::cout << "\t- download" << std::endl;
	std::cout << "\t- quit" << std::endl;

	do {
		std::string input = getInput();
		std::string command = extractCommand(input);
		
		if (command == "ls") {
			vector<string*>* vfiles = fm->listRemoteFiles();
			std::cout << "Lista de ficheros en el directorio remoto:" << std::endl;
			for (unsigned i = 0; i < vfiles->size(); ++i)
				std::cout << "\t- " << vfiles->at(i)->c_str() << std::endl;
			fm->freeListedFiles(vfiles);
		}

		else if (command == "up" || command == "upload") {
			std::string filename = extractParameters(input);
			if (filename.empty()) {
				std::cout << "Missing parameter 'filename'" << std::endl;
				continue;
			}
			std::cout << "Uploading file... ";
			char* contents = nullptr;
			unsigned long content_len = 0;
			fm->readLocalFile((char*)filename.c_str(), contents, content_len);
			fm->writeRemoteFile((char*)filename.c_str(), contents, content_len);
			delete[] contents;
			std::cout << "UPLOADED!" << std::endl;
		}

		else if (command == "down" || command == "download") {
			std::string filename = extractParameters(input);
			if (filename.empty()) {
				std::cout << "Missing parameter 'filename'" << std::endl;
				continue;
			}
			std::cout << "Downloading file... ";
			char* contents = nullptr;
			unsigned long content_len = 0;
			fm->readRemoteFile((char*)filename.c_str(), contents, content_len);
			fm->writeLocalFile((char*)filename.c_str(), contents, content_len);
			delete[] contents;
			std::cout << "DOWNLOADED!" << std::endl;
		}

		else if (command == "quit")
			stop = true;

		else
			std::cout << "Unknown command. Must be one of 'ls', 'up', 'upload', 'down', 'download' or 'quit'." << std::endl;
	} while (!stop);

	delete fm;
	return 0;
}
