#include <windows.h>
#include "ReadFileDateTimes.h"
#include <fileapi.h>
#include <stdio.h>

#include "FreeFunctions.h"

ReadFileDateTimes::ReadFileDateTimes(const char* path)
{
	//https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-createfilea

	LPWIN32_FIND_DATA lpFindFileData = new WIN32_FIND_DATA;
	HANDLE h = FindFirstFile(path, lpFindFileData);

	printf("Creation Time: %s\nAccess Time: %s\nModify Time: s%s\n", to_string(lpFindFileData->ftCreationTime).c_str(), to_string(lpFindFileData->ftLastAccessTime).c_str(), to_string(lpFindFileData->ftLastWriteTime).c_str());
}


ReadFileDateTimes::~ReadFileDateTimes()
{
}
