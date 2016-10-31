#include "login.h"
extern int get_YesNo();
User::User():next_key(0)  {
	if(DEBUG)
		cout << "User" << endl;	

	user_pwd = new vector<ID>;
	FILE * fp = NULL;

	if (NULL != (fp = fopen("data/ID", "rb")))
	{
		int line = 0;
		while(1 == fread(&idInfo, sizeof(ID),1, fp))
		{

			user_pwd->push_back(idInfo);
			next_key += 1;
			line++;
		}
		if(DEBUG)
			cout << "fread " << line <<" line" << endl;
	}
	fclose(fp);

	if(0 == next_key)
	{
		idInfo.key = 0;
		strcpy(idInfo.user, "admin" );
		strcpy(idInfo.passwd, "123456");
		idInfo.identity = 0;
		idInfo.enable = 1;
		user_pwd->push_back(idInfo);
		next_key = 1;
	}
}

User::User( const User & user )
{
	next_key = user.next_key;
	idInfo = user.idInfo;
	user_pwd = new vector<ID>(*user_pwd);
		if(DEBUG)
			cout << "deconstructor User" << endl;	
}
User::User( User && user )
{
	next_key = user.next_key;
	user.next_key = 0;
	idInfo = user.idInfo;
	user_pwd = user.user_pwd;	
	user.user_pwd = NULL;
		if(DEBUG)
			cout << "move constructor User" << endl;	
}
User::~User(){


	if(user_pwd)
	{
		FILE * fp = NULL;
		if (NULL != (fp = fopen("data/ID", "wb")))
		{
			for( vec_it it = user_pwd->begin(); it != user_pwd->end(); ++it )
			{
				fwrite(&(*it), sizeof(ID), 1, fp);
				next_key -= 1;

			}
		}
		fclose(fp);
		delete user_pwd;

	}
		if(DEBUG)
			cout << "~User" << endl;	
}

bool User::logInTest()
{
	vec_it ite = user_pwd->begin();
	while(ite != user_pwd->end())
	{
		if(strcmp(idInfo.user, ite->user) == 0 
				&& 0 == strcmp(idInfo.passwd, ite->passwd))
			return true;
		ite++;
	}
	return false;
}
bool User::logIn()
{
	inPutId();

	vec_it ite = user_pwd->begin();
	while(ite != user_pwd->end())
	{
		if(DEBUG)
		{
			cout << "登录compare" << endl;
			cout << idInfo.user << " " << ite->user << endl;
			cout << idInfo.passwd << " " << ite->passwd << endl;
		}
		if(strcmp(idInfo.user, ite->user) == 0 
				&& 0 == strcmp(idInfo.passwd, ite->passwd))
		{
			if(ite->enable == true)
			{
				idInfo.enable = true;
				idInfo.key = ite->key;
				idInfo.identity = ite->identity;
				if(DEBUG)
					cout << "登录成功！" << endl;
				else
					printf("\033[9;23H登录成功！\033[11;9H");
				fflush(stdout);
				sleep(1);

				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "LOGIN  ";
					temp +=	"users:";
					temp += idInfo.user;
					temp +=  " identity:";
					temp += ((idInfo.identity==2)?"customer":"shop");
					temp +=  " succeed!";
					loginLog.push_sysLog(temp);
				}
				
				return true;
			}
			else
			{
				cout << "\t\t账户暂未启用，或被停用！" << endl;
				cout << "\t\t请联系管理员！" << endl;
				sleep(2);
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "LOGIN ";
					temp +=	"users:";
					temp += idInfo.user;
					temp +=  " identity:";
					temp += ((idInfo.identity==2)?"customer":"shop");
					temp +=  " disabled!";
					loginLog.push_sysLog(temp);
				}
				return false;
			}
		}
		ite++;
	}
	if(DEBUG)
		cout << "用户名或密码不正确！" << endl;
	else
		printf("\033[9;17H用户名或密码不正确！\033[11;9H");
	fflush(stdout);
	sleep(1);
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "LOGIN  ";
					temp +=	"users:";
					temp += idInfo.user;
					temp +=  " fail!";
					loginLog.push_sysLog(temp);
				}
	return false;
}
bool User::signIn()
{
	inPutId();
	if(logInTest())
	{
		if(DEBUG)
			cout << "账号已存在" << endl;
		else
			printf("\033[9;17H      账号已存在！    \033[11;9H");
		fflush(stdout);
		sleep(1);
		return false;
	}
	idInfo.identity = selectIdentify();
	idInfo.enable = false;
	idInfo.key = next_key++;
	user_pwd->push_back(idInfo);
	if(DEBUG)
		cout << "注册成功" << endl;
	else
		printf("\033[9;17H      注册成功！      \033[11;9H");
	cout << "\t请联系管理员启用账号。\n\t按回车继续" << endl;
	getchar();
	getchar();
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "SIGNIN  ";
					temp +=	"users:";
					temp += idInfo.user;
					temp +=  " identity:";
					temp += ((idInfo.identity==2)?"customer":"shop");
					temp +=  " succeed!";
					loginLog.push_sysLog(temp);
				}
	return true;
}
int User::selectIdentify()
{
	string identity;
	unsigned int count = 3 + 1;

	while(--count)
	{
		if(DEBUG)
		{

			cout << "1.销售员，2.顾客" << endl;
			cout << "请选择您的身份信息：";
		}
		else
		{
			printf("\033[9;17H\033[32m");
			cout << "1.销售员，2.顾客(默认)" << endl;
			printf("\033[8;23H\033[39m");
		}
		cin >> identity;
		if('0' < identity[0] && '2' >= identity[0])
			return  identity[0] - '0';
	}
	if(DEBUG)
		cout << "您的身份为: 顾客";
	else
	{
		printf("\033[8;23H\033[32m顾客(默认)");
		printf("\033[9;17H\033[39m");
	}
	return 2;
}
void User::printAll()
{
	for(vec_it it = user_pwd->begin(); it != user_pwd->end()
			; ++it)
	{
		if(it == user_pwd->begin())
			printInfo(it);
		else
			printInfo(it, false);
	}
}
void User::printInfo(vec_it it, bool title)
{
	if(title)
		cout << "\tID\t名字\t密码\t身份\t启用\t" << endl;
	cout << "\t" << it->key 
		<<"\t" << it->user 
		<< "\t" << "******" 
		<< "\t" << ((it->identity == 2)? "顾客" : "商家")
		<< "\t" << ((it->enable)? "启用" : "否") << endl;

}
bool User::verifySignIn()
{
	if(idInfo.identity == 0)
	{
		vec_it ite = user_pwd->begin();
		while(ite != user_pwd->end())
		{
			if(ite->enable== false)
			{
				printInfo(ite);
				cout << "\t是否启用" << ite->user << "的账号：";
				if(get_YesNo())
				{
					ite->enable = true;
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "ACTIVATE  ";
					temp +=	"users:";
					temp += ite->user;
					temp +=  " identity:";
					temp += ((ite->identity==2)?"customer":"shop");
					temp +=  " succeed!";
					loginLog.push_sysLog(temp);
				}

				}
			}
			ite++;
		}
	}	
	return false;

}
int User::getIdentity()
{
	return idInfo.identity;
}

bool User::modifyPwd()
{
	string newPwd;

	if(logIn())
	{
		//     for(  需要引用类型，才能修改原容器内容 )
		for(ID & ite : *user_pwd)
		{
			if(DEBUG)
			{
				cout << idInfo.user << " " << ite.user << endl;
			}
			if(0 == strcmp(idInfo.user, ite.user))
			{
				cout << "请输入您的新密码：";
				cin >> newPwd;
				strcpy(ite.passwd, newPwd.c_str());
				if(DEBUG)
				{
					cout << ite.passwd << " " << newPwd << endl;
				}
				cout << "修改成功！";
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "ModifyPwd ";
					temp +=	"users:";
					temp += ite.user;
					temp +=  " identity:";
					temp += ((ite.identity==2)?"customer":"shop");
					temp +=  " succeed!";
					loginLog.push_sysLog(temp);
				}
				return true;
			}
		}
	}	
	return false;
}

bool User::logOut()
{
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "LOGOUT  ";
					temp +=	"users:";
					temp += idInfo.user;
					temp +=  " identity:";
					temp += ((idInfo.identity==2)?"customer":"shop");
					temp +=  " down!";
					loginLog.push_sysLog(temp);
				}
				return true;
}
void User::inPutId()
{
	string newName;
	string newPwd;
	if(DEBUG)
		cout << "请输入您的名字：";
	else
		printf("\033[6;23H");
	cin >> newName;
	if(DEBUG)
		cout << "请输入您的密码：";
	else
		printf("\033[7;23H");
	cin >> newPwd;
	strcpy(idInfo.user, newName.c_str());
	strcpy(idInfo.passwd, newPwd.c_str());
	if(DEBUG)
	{
		cout << idInfo.user << " " << newName << endl;
		cout << idInfo.passwd << " " << newPwd << endl;
	}
}



void User::volumeRegister()
{
	string buf;

	char user[20];
	char password[20];
	int identify;
	int count;

	cout << "\t请输入：注册ID，数量， 默认密码， 账号类型 " << endl;
	cout << "\t示例： JD001    10     123456     2(顾客)" << endl;
	cout << "\t\t";
	getchar();	
	getline(cin, buf);
	if(4 !=	sscanf(buf.c_str(), "%s %d %s %d", user, &count, password, &identify ))
	{
		cout << "\t输入有误，注册失败" << endl;
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "VolumeRegister ";
					temp +=  " fail!";
					loginLog.push_sysLog(temp);
				}
		sleep(1);
		return;
	}
				if(LOG)
				{
					Log loginLog;
					string temp;
					temp += "VolumeRegister ";
					temp +=	buf;
					temp +=  " succeed!";
					loginLog.push_sysLog(temp);
				}

	for(; count > 0; count--)
	{
		idInfo.enable = true;
		idInfo.key = next_key++;
		idInfo.identity = identify;
		strcpy(idInfo.user, user);
		strcpy(idInfo.passwd, password);

		user_pwd->push_back(idInfo);

		if(user[strlen(user) - 1] + 1 <= '9' )
			user[strlen(user) - 1] += 1;
		if(user[strlen(user) - 1] + 1 > '9' )
		{
			user[strlen(user) - 2] += 1;
			user[strlen(user) - 1] = '0';

		}
	}
	cout << "\t注册成功！" << endl;
}
void User::systemLog()
{
	Log view;
	view.cat_sysLog();
}
void User::salesLog()
{
	Log view;
	view.cat_salesLog();
}
void User::backUp()
{
	system("tar zcf backup/data.gz data");
	printf("\033[8;15H\033[32m The backup successful!\033[11;9H\033[39m");
}
void User::recovery()
{
	system("tar zxf backup/data.gz data");
	printf("\033[8;15H\033[32m The recovery successful!\033[11;9H\033[39m");
}
