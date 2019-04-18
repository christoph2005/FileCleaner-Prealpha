#include <windows.h>
#include "ReadFileDateTimes.h"
#include <fileapi.h>
#include <stdio.h>

#include "FreeFunctions.h"

ReadFileDateTimes::ReadFileDateTimes(const char* path)
{
	//FILE* f = fopen(path, "r");
	LPCSTR lpFileName  = path;
	DWORD dwDesiredAccess = GENERIC_READ;
	DWORD dwShareMode = FILE_SHARE_READ; // Prob should be FILE_SHARE_DELETE, but I don't want that ability right now. See the doc: https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-createfilea
	// Setting the security attribute to NULL, this could be an issue later. Right now the file "HANDLE" wont be accessible by child processes, this seems fine.
	LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL;
	DWORD dwCreationDisposition = OPEN_EXISTING; // Open file only if exists
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL; // Some serious consideration should probably given to this flag, but I'm just going with the default value for now.
	CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, NULL);
	
	// We can get these values this way, but may not need to.
	//LPFILETIME lpCreationTime;
	//LPFILETIME lpLastAccessTime;
	//LPFILETIME lpLastWriteTime;
	//GetFileTime(h, lpCreationTime, lpLastAccessTime, lpLastWriteTime);

	
	LPWIN32_FIND_DATA lpFindFileData = new WIN32_FIND_DATA;
	HANDLE h = FindFirstFile(path, lpFindFileData);
	printf("Creation Time: %s\nAccess Time: %s\nModify Time: %s\n", to_string(lpFindFileData->ftCreationTime).c_str(), to_string(lpFindFileData->ftLastAccessTime).c_str(), to_string(lpFindFileData->ftLastWriteTime).c_str());
}


ReadFileDateTimes::~ReadFileDateTimes()
{
}
