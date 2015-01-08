#include <iostream>
#include <fstream>
#include <cstdarg>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include "LogManager.h"
#include "Manager.h"


LogManager::LogManager() {}

LogManager::~LogManager() {}

int LogManager::startUp(bool flush) {

	do_flush = flush;
	p_f = fopen(LOGFILE_NAME, "w");
	writeLog("LogManger started successfully.");

}

void LogManager::shutDown() {
	writeLog("LogManger ended.");
	fclose(p_f);
}

LogManager& LogManager::getInstance() {
	static LogManager instance;
	return instance;
}

int LogManager::writeLog(const char *fmt, ...) {
	fprintf(p_f, "Message: ");
	va_list args;
	
	va_start(args, fmt);
	char* timeStamp = getTimeString();
	vfprintf(p_f, fmt, args);
	vfprintf(p_f, timeStamp, args);
	fprintf(p_f, "\r\n");
	va_end(args);
	
	if(do_flush){fflush(p_f);}

	return 0;
}



char* LogManager::getTimeString() {
	static char time_str[30];

	time_t ntime = time(NULL);
	struct tm *p_time = localtime(&ntime);

	sprintf(time_str, "LOG_TIME:%02d:%02d:%02d", p_time -> tm_hour, p_time -> tm_min, p_time -> tm_sec);
	return time_str;
}
