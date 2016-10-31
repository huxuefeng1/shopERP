#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <algorithm>
#include "login.h"
#include "goods.h"
#include "storage.h"
typedef struct ShoppingCart{
	list_it it;
	int count;
	string ordernumber;
}SC;

class Customer :public User, private ListGoods {
	public:
		Customer(User & user): User(user) { };
		Customer(User && user):User(move(user)) {};
		bool buyGoods();
		int addSC(SC goods);
		int printSC();
		void printGoods(int orderby, bool asc = true);
		bool payAll();
		
	private:
		vector<SC> shoppingcart;
		string ordernumber;

};

#endif /*__CUSTOMER_H__*/

