#include "Task.h"
#include "ScanDirectoryForFilesTest.h"
#include "ReadFileDateTimes.h"
#include "FreeFunctions.h"

#include <filesystem>
#include <atltime.h>


Task::Task()
{
	throw 0;
}

Task::Task(_bstr_t taskName, _bstr_t taskScope, _bstr_t expirationDirectory, _bstr_t expirationType, _bstr_t expirationAge, _bstr_t expirationFinal)
{
	this->taskName = taskName;
	this->taskScope = taskScope;
	this->expirationDirectory = expirationDirectory;
	this->expirationType = expirationType;
	this->expirationAge = expirationAge;
	this->expirationFinal = expirationFinal;

}

void Task::scanDirectory(const char * path)
{
	//new ScanDirectoryForFilesTest(path);
	new ScanDirectoryForFilesTest(taskScope);
}

FILETIME Task::getFileTime(std::filesystem::path filePath) {
	// Return the appropriate "LPFILETIME" for the file, based on the expirationType

	LPWIN32_FIND_DATA lpFindFileData = new WIN32_FIND_DATA;
	HANDLE h = FindFirstFile(filePath.string().c_str(), lpFindFileData);

	//printf("\t\tCreation Time: %s\n\t\tAccess Time: %s\n\t\tModify Time: %s\n", to_string(lpFindFileData->ftCreationTime).c_str(), to_string(lpFindFileData->ftLastAccessTime).c_str(), to_string(lpFindFileData->ftLastWriteTime).c_str());

	// Just return "CreationTime" for now... ToDo: Implement "chooser"
	return lpFindFileData->ftLastWriteTime;
}



// pseudocode: What's this algorithm supposed to be?
void Task::Execute() {

	namespace fs = std::filesystem;
	for (const auto & entry : fs::directory_iterator(taskScope.GetBSTR())){
		auto  filePath = entry.path();
		printf("\tFilePath: %S \n", filePath.c_str());
		
		// Use filesystem's filetime solution?: // auto ftime = fs::last_write_time(filePath);
		// assuming system_clock for this demo
		// note: not true on MSVC or GCC 9; C++20 will allow portable output


		//Unknown code:
		


		//CTime::Format("%Y-%m-%dT%H:%M:%S.000", getFileTime(filePath));
		
		printf("Last write time for file: %s\n", to_string(getFileTime(filePath)).c_str());


		//printf("LastWriteTime: %S", fs::last_write_time(filePath));

		// DO something with that file here
		//FILETIME TheFilesTime = getFileTime(filePath);




	}
}

void Task::evaluateFileAndDecide(const char * filePath) {
	new ReadFileDateTimes(filePath);
}


Task::~Task()
{
}
