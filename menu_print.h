#ifndef __MENU_PRINT_H__
#define __MENU_PRINT_H__
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include "shop.h"
#include "customer.h"
#include "goods.h"
#include "storage.h"
#include "login.h"
#include "log.h"
using namespace std;

class Menu {

	public:
		int run();
	private:
		void print_menu();

		int runLogin();
		void print_login_menu();
		void runSignIn();
		void print_signIn_menu();
		void runModifyPwd();
		void print_modifyPwd_menu();

		//管理员控制面板        
		//-------------------------------
		//--1.账号检索--  --4.系统日志--
		//--2.批量注册--  --5.销售日志--
		//--3.启用账号--  --6.备份恢复--
		//--0)上 一 页--  --q)退    出--
		int runAdmin();
		void print_admin_menu();
		void print_admin_submenu1();	
		void print_admin_submenu2();	
		void print_admin_submenu3();	
		void print_admin_submenu4();	
		void print_admin_submenu5();	
		void print_admin_submenu6();	
			int admin_backup_recovery();
		//--1.商品盘点--  --4.新增品类
		//--2.商品入库--  --5.财务报表
		//--3.品类下架--  --6.数据统计		
		int runShop();
		void print_shop_menu();
		void print_shop_submenu1();	
		void print_shop_submenu2();	
		void print_shop_submenu3();	
		void print_shop_submenu4();	
		void print_shop_submenu5(Shop & shop);	
		void print_shop_submenu6(Shop & shop);	
	
		//--1.价格排序--  --4.buyGoods--
		//--2.销量排序--  --5.购 物 车--
		//--3.品名检索--  --6.结    算--
		//--0)上 一 页--  --q)退    出--
		int runCustomer();
		void print_customer_menu();
		void print_customer_submenu1();	
		void print_customer_submenu2();	
		void print_customer_submenu3();	
		void print_customer_submenu4();	
		void print_customer_submenu5();	
		void print_customer_submenu6();	
	private:
		void pause()
		{
			cin.clear();
			cin.sync();
			cout << "\t______________\n";
			cout << "\t按回车键继续：" ;
			getchar();	
			getchar();	
		}
	private:
		User *admin;
};

#endif /*__MENU_PRINT_H__*/
