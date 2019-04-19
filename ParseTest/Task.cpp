#include "Task.h"
#include "ScanDirectoryForFilesTest.h"
#include "ReadFileDateTimes.h"



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

/* pseudocode: What's this algorithm supposed to be?
void Task::Execute() {
		
	//1. Scan for files to delete
	//List L = scanDirectory(taskScope);

	for (int i = 0; i++; i < L.length()) {
		char * filePath = L[i];
		evaluateFileAndDecide(filePath);
	}
}

void Task::evaluateFileAndDecide(const char * filePath) {
	new ReadFileDateTimes(filePath);
}
*/


Task::~Task()
{
}
