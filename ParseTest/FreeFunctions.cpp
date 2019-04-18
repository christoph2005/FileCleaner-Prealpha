#include <windows.h>
#include "FreeFunctions.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

std::string to_string(FILETIME ftime) // ISO format, time zone designator Z == zero (UTC)
{
	SYSTEMTIME utc;
	::FileTimeToSystemTime(std::addressof(ftime), std::addressof(utc));

	std::ostringstream stm;
	const auto w2 = std::setw(2);
	stm << std::setfill('0') << std::setw(4) << utc.wYear << '-' << w2 << utc.wMonth
		<< '-' << w2 << utc.wDay << ' ' << w2 << utc.wYear << ' ' << w2 << utc.wHour
		<< ':' << w2 << utc.wMinute << ':' << w2 << utc.wSecond << 'Z';

	return stm.str();
}