#include "menu_print.h"

int Menu::run()
{
	string select;
	while(1)
	{
		print_menu();
		cin >> select;
		switch (select[0])
		{
			case '1':
				if(!runLogin())
					return 0; break;
			case '2':
				runSignIn(); break;
			case '3':
				runModifyPwd(); break;
			case 'q':
				exit(0);
		}
	}
}
void Menu::print_menu()
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|          欢迎使用本程序          |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|         --1.登    录--           |\n";
	cout << "\t|         --2.注    册--           |\n";
	cout << "\t|         --3.修改密码--           |\n";
	cout << "\t|         --q)退    出--           |\n";
	cout << "\t------------------------------------\n";
	cout << "\tEnter:";
}
int Menu::runLogin()
{
	print_login_menu();
	admin = new User;
	int noquit = 1;
	//admin = new User;
	if(admin->logIn())
	{
		switch (admin->getIdentity())
		{
			case 0:
				noquit = runAdmin();
				break;
			case 1:
				noquit = runShop();
				break;
			case 2:
				noquit = runCustomer();
				break;
		}
		if(noquit)
			admin->logOut();
	}
	delete admin;
	return noquit;
}

void Menu::print_login_menu()
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|           统一登录入口           |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|       账号：                     |\n";
	cout << "\t|       密码：                     |\n";
	cout << "\t|                                  |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
	//printf("\033[7;23H");
}
void Menu::runSignIn()
{
	print_signIn_menu();
	User * admin = new User;
	admin->signIn();
	delete admin;	
}
void Menu::print_signIn_menu()
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|           统一注册入口           |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|       账号：                     |\n";
	cout << "\t|       密码：                     |\n";
	cout << "\t|       身份：                     |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
	//printf("\033[7;23H");
}

void Menu::runModifyPwd()
{
	print_modifyPwd_menu();
	User * admin = new User;
	admin->modifyPwd();
	delete admin;	
}

void Menu::print_modifyPwd_menu()
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             修改密码             |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|       账号：                     |\n";
	cout << "\t|       密码：                     |\n";
	cout << "\t|     新密码：                     |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
}
int Menu::runAdmin()
{
	//管理员控制面板        
	//-------------------------------
	//--1.账号检索--  --4.系统日志--
	//--2.批量注册--  --5.销售日志--
	//--3.启用账号--  --6.备份恢复--
	//--0)上 一 页--  --q)退    出--
	string select;
	while(1)
	{
		print_admin_menu();
		cin >> select;
		switch (select[0])
		{
			case '1':
				print_admin_submenu1();	
				admin->printAll();
				break;
			case '2':
				print_admin_submenu2();	
				admin->volumeRegister();
				break;
			case '3':
				print_admin_submenu3();	
				admin->verifySignIn();
				break;
			case '4':
				print_admin_submenu4();	
				admin->systemLog();
				break;
			case '5':
				print_admin_submenu5();	
				admin->salesLog();
				break;
			case '6':
				if( ! admin_backup_recovery() )
					return 0;
				break;
			case '0':
				return 1;
				break;
			case 'q':
				admin->logOut();
				return 0;
		}
		pause();
	}
}
void Menu::print_admin_menu()
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|          管理员控制面板          |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|  --1.账号检索--  --4.系统日志--  |\n";
	cout << "\t|  --2.批量注册--  --5.销售日志--  |\n";
	cout << "\t|  --3.启用账号--  --6.备份恢复--  |\n";
	cout << "\t|  --0)上 一 页--  --q)退    出--  |\n";
	cout << "\t------------------------------------\n";
	cout << "\tEnter:";
}
void Menu::print_admin_submenu1()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             账号检索             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_admin_submenu2()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             批量注册             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_admin_submenu3()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             启用账号             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_admin_submenu4()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	//	cout << "\t------------------------------------\n";
	//	cout << "\t|             系统日志             |\n";
	//	cout << "\t------------------------------------\n";
}
void Menu::print_admin_submenu5()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	//	cout << "\t------------------------------------\n";
	//	cout << "\t|             销售日志             |\n";
	//	cout << "\t------------------------------------\n";
}
void Menu::print_admin_submenu6()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             备份恢复             |\n";
	cout << "\t|  --1)备份账套--  --2)恢复账套--  |\n";
	cout << "\t|                                  |\n";
	cout << "\t|  --0)上 一 页--  --q)退    出--  |\n";
	cout << "\t|                                  |\n";
	cout << "\t|----------------------------------|\n";
}
int Menu::admin_backup_recovery()
{
	//--1)备份账套--  --2)恢复账套--
	//--0)上 一 页--  --q)退    出--
	string select;
	while(1)
	{
		print_admin_submenu6();	
		cin >> select;
		switch (select[0])
		{
			case '1':
				admin->backUp();
				break;
			case '2':
				admin->recovery();
				break;
			case '0':
				return 1;
				break;
			case 'q':
				admin->logOut();
				return 0;
		}
		pause();
	}
}
int Menu::runShop()
{
	Shop shop(move(*admin));
	string select;
	string secondSelect;
	while(1)
	{
		print_shop_menu();
		cin >> select;
		//--1.商品盘点--  --4.新增品类
		//--2.商品入库--  --5.财务报表
		//--3.品类下架--  --6.数据统计		
		switch (select[0])
		{
			case '1':
				print_shop_submenu1();
				shop.printGoodsInfo();	
				break;
			case '2':
				print_shop_submenu2();
				shop.stockGoods();
				break;
			case '3':
				print_shop_submenu3();
				while(1)
				{
					cout << "\t停用商品按 1， 启用商品按 2, \n"
						"\t退出按 0 : ";
					cin >> secondSelect;
					if( secondSelect[0] == '1' )
					{
						shop.printGoodsInfo(true);	
						shop.stopGoods(false);//bool reUp
					}
					if( secondSelect[0] == '2' )
					{
						shop.printGoodsInfo(false);	
						shop.stopGoods(true);//bool reUp
					}
					else
						break;
				}
				break;
			case '4':
				while(1)
				{
					print_shop_submenu4();
					if(!shop.newGoodsName())
						break;
					pause();
				}
				break;
			case '5':
				while(1)
				{
					print_shop_submenu5(shop);
					cout << "\t详情输入1，2，3 ？\n"
						"\t退出按 0 : ";
					cin >> secondSelect;
					if( secondSelect[0] == '1' )
						shop.getValue(1, true);
					else if( secondSelect[0] == '2' )
						shop.getValue(2, true);
					else if( secondSelect[0] == '3' )
						shop.getValue(3, true);
					else
						break;
					pause();

				}
				break;

			case '6':
				while(1)
				{
					print_shop_submenu6(shop);
					cout << "\t详情输入1，2，3 ？\n"
						"\t退出按 0 : ";
					cin >> secondSelect;
					if( secondSelect[0] == '1' )
						shop.getValue(4, true);
					else if( secondSelect[0] == '2' )
						shop.getValue(5, true);
					else if( secondSelect[0] == '3' )
						shop.getValue(6, true);
					else
						break;
					pause();
				}
				break;
			case '0':
				return 1;
				break;
			case 'q':
				shop.logOut();
				return 0;
		}
		pause();
	}
}
void Menu::print_shop_menu()
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|           商店存货管理           |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|  --1.商品盘点--  --4.新增品类--  |\n";
	cout << "\t|  --2.商品入库--  --5.财务报表--  |\n";
	cout << "\t|  --3.品类下架--  --6.数据统计--  |\n";
	cout << "\t|  --0)上 一 页--  --q)退    出--  |\n";
	cout << "\t------------------------------------\n";
	cout << "\tEnter:";
}
void Menu::print_shop_submenu1()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             商品盘点             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_shop_submenu2()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             商品入库             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_shop_submenu3()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             品类下架             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_shop_submenu4()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             新增品类             |\n";
	cout << "\t------------------------------------\n";

}
void Menu::print_shop_submenu5(Shop & shop)	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|           商店财务报表           |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|  --1.销售金额   "<<(shop.getValue(1)/100.0f)<<"\n";
	cout << "\t|  --2.库存金额   "<<(shop.getValue(2)/100.0f)<<"\n";
	cout << "\t|  --3.净 利 润   "<<(shop.getValue(3)/100.0f)<<"\n";
	cout << "\t|  --0)上 一 页--  --q)退    出--  |\n";
	cout << "\t------------------------------------\n";
	cout << "\tEnter:";
}
void Menu::print_shop_submenu6(Shop & shop)	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|           商店库存统计           |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|  --1.库存总数   "<<(shop.getValue(4))<<"\n";
	cout << "\t|  --2.库存报警   "<<(shop.getValue(5))<<"\n";
	cout << "\t|  --3.滞销品类   "<<(shop.getValue(6))<<"\n";
	cout << "\t|  --0)上 一 页--  --q)退    出--  |\n";
	cout << "\t------------------------------------\n";
	cout << "\tEnter:";
}
int Menu::runCustomer()
{
	Customer customer(move(*admin));
	string select;
	string secondSelect;
	while(1)
	{
		print_customer_menu();
		cin >> select;
		//---1.价格排序--  --4.buyGoods--
		//---2.销量排序--  --5.购 物 车--
		//---3.品名检索--  --6.结    算--
		// --0)上 一 页--  --q)退    出--
		switch (select[0])
		{
			case '1':
				print_customer_submenu1();	
				customer.printGoods(1);
				break;
			case '2':
				print_customer_submenu2();	
				customer.printGoods(2);
				break;
			case '3':
				print_customer_submenu3();	
				customer.printGoods(3);
				break;
			case '4':
				print_customer_submenu4();	
				customer.buyGoods();
				break;
			case '5':
				print_customer_submenu5();	
				customer.printSC();
				break;
			case '6':
				print_customer_submenu6();	
				customer.payAll();
				break;
			case '0':
				return 1;
				break;
			case 'q':
				customer.logOut();
				return 0;
		}
		pause();
	}
}
void Menu::print_customer_menu()
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|         欢迎登录京东商城         |\n";
	cout << "\t|----------------------------------|\n";
	cout << "\t|  --1.价格排序--  --4.buyGoods--  |\n";
	cout << "\t|  --2.销量排序--  --5.购 物 车--  |\n";
	cout << "\t|  --3.品名检索--  --6.结    算--  |\n";
	cout << "\t|  --0)上 一 页--  --q)退    出--  |\n";
	cout << "\t------------------------------------\n";
	cout << "\tEnter:";
}
void Menu::print_customer_submenu1()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             价格排序             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_customer_submenu2()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             销量排序             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_customer_submenu3()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             品名检索             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_customer_submenu4()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|               buyGoods           |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_customer_submenu5()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             购 物 车             |\n";
	cout << "\t------------------------------------\n";
}
void Menu::print_customer_submenu6()	
{
	if(!DEBUG) system("clear");
	cout << "\n\n";
	cout << "\t------------------------------------\n";
	cout << "\t|             结    算             |\n";
	cout << "\t------------------------------------\n";
}
