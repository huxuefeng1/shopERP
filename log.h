#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
#include <string>
#include <time.h>
#define DEBUG (0)
#define LOG (1)

class Log {

	public:
		Log();
		~Log();
	public:
		bool push_salesLog(const std::string& info);
		bool push_sysLog(const std::string& info);
		bool cat_sysLog();
		bool cat_salesLog();

	private:
		std::queue<std::string> sysLog;
		std::queue<std::string> salesLog;
};


#endif /*__LOG_H__*/
