#include "customer.h"

int Customer::addSC(SC goods)
{
	shoppingcart.push_back(goods);
	return shoppingcart.size();
}
int Customer::printSC()
{
	//打印购物车
	int totalpay = 0;
	bool noPrintStockVolume = true;

	cout << "\t______________________________________\n";
	cout << "\t商品ID\t名称\t单价\t销量\t购买数\t" << endl;
	cout << "\t--------------------------------------\n";

	for( SC & it : shoppingcart )
	{
		if(it.count > 0)
		{
			cout <<  "\t";
			it.it->printGoods(noPrintStockVolume);
			cout <<  "\t";
			cout << it.count << endl;
			totalpay += it.count*(it.it->getSalesPrice());
		}
	}
	cout << "\t______________________________________\n";
	cout << "\t合计：" << totalpay/100 << " 元 "
		<< totalpay%100 << " 分" << endl;
	return totalpay;
}
bool Customer::payAll()
{
	//	结算	
	if(shoppingcart.size() == 0)
	{
		cout << "\t您还没有选购商品！\n";
		return false;
	}

	cout <<  "\n\t" << "user: " << idInfo.user;
	cout <<  "\tNO." << ordernumber << endl;

	int totalpay = printSC();
	cout << "\n\t确定购买";
	if(get_YesNo())
	{
		for( SC & selectGoods : shoppingcart )
			selectGoods.it->sellGoods(selectGoods.count);
		if(LOG)
		{
			Log loginLog;
			string temp;
			char total[20];
			sprintf(total, "%.2f ", 1.0f*totalpay/100);
			temp += "buy_goods ";
			temp +=	"NO:";
			temp += ordernumber;
			temp +=	" users:";
			temp += idInfo.user;
			temp +=  " identity:";
			temp += ((idInfo.identity==2)?"customer":"shop");
			temp +=  " totalpay: ";
			temp += total; 
			temp += "money "; 
			loginLog.push_salesLog(temp);
		}
		ordernumber.clear();
		shoppingcart.clear();	
		return true;
	}
	else 
		return false;
}

bool Customer::buyGoods()
{
	SC goods;

	unsigned id;
	string name;
	int number;
	int cnt = 0;
	list_it ite;
	char orderrand[10];
	if(shoppingcart.size() == 0)
	{
		srand(time(0));
		ordernumber = idInfo.key;
		sprintf(orderrand, "%d", rand()/10000);
		ordernumber += orderrand; 
		cout <<  "\tuser " << idInfo.user 
			<< "\tNO." << ordernumber << endl;

	}
	while(1)
	{
		cout << "\t\t商品查询(-1 退出)\t" << endl;
		cout << "\t输入 商品ID or 商品名:" << flush;

		cin.clear(); cin.sync();

		if(cin >> id)
		{
			if(-1 == id)
				break;
			goods.it = findGoodsID(id);
		}
		else
		{
			cin.clear(); cin >> name; cin.sync();

			if('0' == name[0])
				break;
			goods.it = findGoodsName(name);
		}

		if(goods.it == listGoods.end() || !goods.it->getEnable())
		{
			cout << "\t没有查到该商品" << endl;
		}
		else	
		{
			cout << "\t商品ID\t名称\t单价\t销量\t库存" << endl;
			cout <<  "\t";
			goods.it->printGoods();
			cout <<  "\n";
			cout << "(0退出)输入购买数量：";
			cin >> number;
			if(0 >= number)
				break;
			//	cout << "\t加入购物车:" << endl;
			if(number > 0 && number <= goods.it->getStockVolume())
			{
				goods.count = number;
				goods.ordernumber = ordernumber;
				cout << "\t已选购 " << addSC(goods) << "类商品。\n";
			}
			else cout << "\t库存不足！" << endl;
		}	

	}
	printSC();
	return true;
}
void Customer::printGoods(int orderby, bool asc)
{
	switch (orderby)
	{
		case 1:
			sortSalesPrice(asc);
			break;
		case 2:
			sortSalesValume(asc);
			break;
		case 3:
			sortGoodsName(asc);
			break;
		default:
			sortGoodsID(asc);
	}
	list_it ite;
	cout << "\t商品ID\t名称\t单价\t销量\t库存" << endl;
	for (ite = listGoods.begin(); ite != listGoods.end(); ++ite)
	{
		cout <<  "\t";
		ite->printGoods();
		cout <<  "\n";
	}
}
