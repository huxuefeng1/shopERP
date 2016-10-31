#ifndef __SHOP_H__
#define __SHOP_H__
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

class Shop :public User, public ListGoods {
	public:
		Shop(User & user):User(user) { };
		Shop(User && user):User(move(user)) {
		}
	private:

};



#endif /*__SHOP_H__*/

