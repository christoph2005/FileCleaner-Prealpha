#pragma once

#include <tchar.h> // - This appears to be NEEDED for the msxml6 library
#include <filesystem>
#import <msxml6.dll> rename_namespace(_T("MSXML"))

class Task
{
private:
	_bstr_t taskName;
	_bstr_t taskScope;
	_bstr_t expirationDirectory;
	_bstr_t expirationType;
	_bstr_t expirationAge;
	_bstr_t expirationFinal;


	FILETIME getFileTime(std::filesystem::path filePath);

	bool isExpired(const char * filePath);
	void scanDirectory(const char* path);
	void evaluateFileAndDecide(const char * filePath);
public:
	Task();
	Task(_bstr_t taskName, _bstr_t taskScope, _bstr_t expirationDirectory, _bstr_t expirationType, _bstr_t expirationAge, _bstr_t expirationFinal);
	void Execute();

	~Task();
};

