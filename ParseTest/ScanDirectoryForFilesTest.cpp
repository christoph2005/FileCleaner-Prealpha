#include "ScanDirectoryForFilesTest.h"
#include <string>
#include <iostream>
#include <filesystem>


ScanDirectoryForFilesTest::ScanDirectoryForFilesTest(const char* path)
{
	namespace fs = std::filesystem;
	for (const auto & entry : fs::directory_iterator(path))
		std::cout << "\t" << entry.path() << std::endl;
}

ScanDirectoryForFilesTest::~ScanDirectoryForFilesTest()
{
}