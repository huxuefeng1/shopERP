#ifndef __LOGIN_H__
#define __LOGIN_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
#include <unistd.h>
#include "log.h"

// 老板，员工，客户
using namespace std;
typedef struct {
			unsigned key;
			char user[20];
			char passwd[20];
			unsigned identity;
			bool enable;
		}ID;
typedef vector<ID>::iterator vec_it;

class User {
	public:
		User();
		~User();
		User( const User & user );
		User( User  && user );
		
	public:
		bool logIn();
		bool signIn();
		bool modifyPwd();
		bool logOut(); 
		bool verifySignIn();
		int getIdentity();
		void printAll();
		void volumeRegister();
		void systemLog();
		void salesLog();
		void backUp();
		void recovery();
	protected:
		bool logInTest();
		int selectIdentify();
		void printInfo(vec_it it, bool title = true);
		void inPutId();
	protected:
		unsigned next_key;
		ID idInfo;
		vector<ID> *user_pwd;
};

#endif /*__LOGIN_H__*/
