#include "log.h"

bool Log::push_sysLog(const std::string& info)
{
	std::string loginfo;
	time_t nowTime = time(NULL);
	loginfo += "\n\t";
	loginfo += ctime(&nowTime);
	loginfo += info;
	loginfo += '\n';
	sysLog.push(loginfo);
	return true;
}
bool Log::push_salesLog(const std::string& info)
{
	std::string loginfo;
	time_t nowTime = time(NULL);
	loginfo += "\n\t";
	loginfo += ctime(&nowTime);
	loginfo += info;
	loginfo += '\n';
	salesLog.push(loginfo);
	return true;
}
Log::Log()
{
	FILE * psys = NULL;
	FILE * psal = NULL;
	//打开成功，追加日志到文件尾
	if(NULL == (psys = fopen("data/syslog", "r")))
	{
		sysLog.push(std::string(
					"\t            System Log              \n"
					"\t____________________________________\n"));
	}
	else
		fclose(psys);
	if(NULL == (psal = fopen("data/saleslog", "r")))
	{
		salesLog.push(std::string(
					"\t           Shopping Log             \n"
					"\t____________________________________\n"));
	}
	else
		fclose(psal);

}
Log::~Log()
{
	FILE * psys = NULL;
	FILE * psal = NULL;
	//打开成功，追加日志到文件尾
		if(NULL == (psys = fopen("data/syslog", "a")))
			return;
	while(!sysLog.empty())
	{
		fwrite(sysLog.front().c_str(), sysLog.front().size(),1,psys);
		sysLog.pop();	
	}
	//必须关闭文件
	fclose(psys);

	if(NULL == (psal = fopen("data/saleslog", "a")))
			return;
	while(!salesLog.empty())
	{
		fwrite(salesLog.front().c_str(), salesLog.front().size(),1,psal);
		salesLog.pop();	
	}
	//必须关闭文件
	fclose(psal);

}
bool Log::cat_sysLog()
{
	system("cat data/syslog | more ");
	return true;
}
bool Log::cat_salesLog()
{
	system("cat data/saleslog | more ");
	return true;
}
