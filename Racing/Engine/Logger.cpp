#include "Logger.h"

#ifdef _DEBUG
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#endif

using namespace std;

namespace Logger {

	std::string LOG_STRING[LOG_MAX] = { "FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE" };

}

//ÉçÉOèoóÕópÇÃä÷êî
void Logger::DebugOutputStream(const char* function, const int line, LOG_TYPE type, const ostringstream& out) {

#ifdef _DEBUG
	time_t t = time(NULL);
	tm tm;
	localtime_s(&tm, &t);

	cout << '[' << setfill('0') << setw(2) << tm.tm_hour
		<< ':' << setfill('0') << setw(2) << tm.tm_min
		<< ':' << setfill('0') << setw(2) << tm.tm_sec << "] ";
	cout << '[' << function << ':' << line << "] ";
	cout << '[' << LOG_STRING[type] << "] ";
	cout << out.str() << endl;
#endif
}
string Logger::getInformation(const char* function, const int line, LOG_TYPE type) {

#ifdef  _DEBUG
	ostringstream oss;
	time_t t = time(NULL);
	tm tm;
	localtime_s(&tm, &t);
	
	oss << '[' << setfill('0') << setw(2) << tm.tm_hour
		<< ':' << setfill('0') << setw(2) << tm.tm_min
		<< ':' << setfill('0') << setw(2) << tm.tm_sec << "] ";
	oss << '[' << function << ':' << line << "] ";
	oss << '[' << LOG_STRING[type] << "] ";

	return oss.str();
#else
	return "";
#endif
}
