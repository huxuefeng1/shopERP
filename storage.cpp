#include "storage.h"
ListGoods::ListGoods()
{
	if(DEBUG)
		cout << "ListGoods" << endl;
	char temp[1024];
	unsigned temp_enable; 

	unsigned m_goodsId;
	string m_goodsName;
	int m_stockPrice;
	int m_salesPrice;
	int m_stockVolume;
	int m_salesVolume;
	bool m_enable; 

	FILE * pf = NULL;
	if( NULL == (pf = fopen("data/goods", "r")))
		return;

	while(7 == fscanf(pf, "%d %s %d %d %d %d %d", &m_goodsId, temp
				, &m_stockPrice, &m_salesPrice, &m_stockVolume
				, &m_salesVolume, &temp_enable))
	{
		m_goodsName = string(temp);
		m_enable = (bool)temp_enable;

		listGoods.push_back(Goods(m_goodsId, m_goodsName, m_stockPrice
					, m_salesPrice, m_stockVolume, m_salesVolume
					, m_enable ));
	}
	fclose(pf);

}

ListGoods::~ListGoods()
{
	if(DEBUG)
		cout << "~ListGoods" << endl;

	char temp[1024];
	unsigned temp_enable; 

	unsigned m_goodsId;
	string m_goodsName;
	int m_stockPrice;
	int m_salesPrice;
	int m_stockVolume;
	int m_salesVolume;
	bool m_enable; 

	FILE * pf = NULL;
	if( NULL == (pf = fopen("data/goods", "w")))
		return;
	list_it it;
	for( it = listGoods.begin(); it != listGoods.end(); ++it )
	{
		strcpy(temp, it->goodsName.c_str());
		temp_enable = (int)it->enable;

		fprintf(pf, "%d %s %d %d %d %d %d\n", it->goodsId, temp
				, it->stockPrice, it->salesPrice, it->stockVolume
				, it->salesVolume, temp_enable);
	}
	fclose(pf);

}

bool ListGoods::newGoodsName()
{
	unsigned id = listGoods.size();
	string name;
	double stockP;
	double salesP;

	cout << "\t\t新增商品信息(q退出)" << endl;
	cout << "\t商品ID\t商品名称\t进货价\t销售价\t" << endl;
	cout << "\t" << id << "\t";

	cin >> name;
	if( name[0] == 'q')
		return false;
	if(cin >> stockP)
	{
		if(cin >> salesP)
		{
			Goods addnew(id, name, (int)(stockP*100), (int)(salesP*100));
			listGoods.push_back(addnew);
			return true;
		}
	}
	cin.clear(); cin.sync();
	return false;
}
list_it ListGoods::findGoodsID(unsigned id)
{
	list_it it;
	for(it = listGoods.begin(); it != listGoods.end(); ++it)
	{
		if(it->goodsId == id)
			return it;
	}
	return it;
}

list_it ListGoods::findGoodsName(string name)
{

	list_it it;
	for(it = listGoods.begin(); it != listGoods.end(); ++it)
	{
		if(it->goodsName == name)
			return it;
	}
	return it;
}
void ListGoods::sortGoodsName(bool asc)
{
	listGoods.sort(Goods::compName);
	if(!asc) // 要求倒序，反向
		listGoods.reverse();
}

void ListGoods::sortSalesPrice(bool asc)
{
	listGoods.sort(Goods::compSalesPrice);
	if(!asc) // 要求倒序，反向
		listGoods.reverse();
}
void ListGoods::sortSalesValume(bool asc)
{
	listGoods.sort(Goods::compSalesVolume);
	if(!asc) // 要求倒序，反向
		listGoods.reverse();
}
int ListGoods::getValue(int index, bool enablelist)
{
	list_it it;
	int value = 0;

	for(it = listGoods.begin(); it != listGoods.end(); ++it)
	{
		switch (index)// 1.销售额，2.库存金额，3.净利润
		{
			case 1:
				value +=
					it->salesPrice * it->salesVolume;
				if(enablelist)
					cout << "\t品名：" << it->goodsName 
						<< "\t销售额：" << (it->salesPrice * it->salesVolume/100.0) << endl;
				break;
			case 2:
				value +=
					it->stockPrice * it->stockVolume;
				if(enablelist)
					cout << "\t品名：" << it->goodsName 
						<< "\t库存额：" << (it->stockPrice* it->stockVolume/100.0) << endl;
				break;
			case 3:
				value +=
					(it->salesPrice - it->stockPrice) * it->salesVolume;
				if(enablelist)
					cout << "\t品名：" << it->goodsName 
						<< "\t净利润：" << ((it->salesPrice-it->stockPrice)* it->salesVolume/100.0) << endl;
				break;
			case 4:
				value +=
					it->stockVolume + it->salesVolume;
				if(enablelist)
					cout << "\t品名：" << it->goodsName 
						<< "\t存货：" << it->stockVolume << endl;
				break;
			case 5:
				value +=
					(it->stockVolume < it->salesVolume/10);
				if(enablelist && (it->stockVolume < it->salesVolume/10))
					printGoodsInfo(it, value <= 1);
				break;
			case 6:
				value +=
					(it->salesVolume < it->stockVolume/10);
				if(enablelist && (it->salesVolume < it->stockVolume/10))
					printGoodsInfo(it, value <= 1);
		}
	}

	return value;
}

bool ListGoods::stockGoods()
{
	unsigned id;
	string name;
	int number;
	list_it it;


	while(1)
	{
		cout << "\t\t商品查询(-1 退出)\t" << endl;
		cout << "\t输入 商品ID or 商品名:" << flush;

		cin.clear(); cin.sync();

		if(cin >> id)
		{
			if(-1 == id)
				break;
			it = findGoodsID(id);
		}
		else
		{
			cin.clear(); cin >> name; cin.sync();

			if('0' == name[0])
				break;
			it = findGoodsName(name);
		}

		if(it == listGoods.end())
			cout << "\t没有查到该商品" << endl;
		else
		{
			if( !it->getEnable())
				cout << "\t该商品下架状态" << endl;

	cout << "\t____________________________________________________\n";
		printGoodsInfo(it);
	cout << "\t____________________________________________________\n";
		cout << "\t输入进货数量：";
		cin >> number;
		it->stockVolume += number;
		}	

	}
		return true;
}
bool ListGoods::stopGoods(bool reUp)
{
		unsigned id;
		int enable;
		list_it it;

		cout << "\t请输入商品ID：";
		cin >> id;

		it = findGoodsID(id);

		if(it == listGoods.end())
		{
			cout << "\t没有查到该ID" << endl;
			return false;
		}
		else	
		{
			printGoodsInfo(it);
			if(reUp)
			{
				cout << "\t是否启用：";
				if(get_YesNo())
					it->enable = true;
			}
			else
			{
				cout << "\t是否停用：";
				if(get_YesNo())
					it->enable = false;

			}
			return true;
		}	
}


void ListGoods::printGoodsInfo(bool Up)
{
	list_it it;
	int i = 0;
	for(it = listGoods.begin(); it != listGoods.end(); ++it)
	{
		if(it->getEnable() == Up)
		{
		if(i++ == 0)
			printGoodsInfo(it);
		else
			printGoodsInfo(it,false);
			
		}
	}
}
void ListGoods::printGoodsInfo()
{
	list_it it;
	for(it = listGoods.begin(); it != listGoods.end(); ++it)
	{
		if(it == listGoods.begin())
			printGoodsInfo(it);
		else
			printGoodsInfo(it,false);
	}
}
void ListGoods::printGoodsInfo(const list_it & it , bool printTitle)
{
	if(printTitle)
		cout << "\t商品ID\t名称\t进货价\t销售价\t库存数\t销量\t启用" << endl;
	cout << "\t" 
		<< it->goodsId << "\t"
		<< it->goodsName << "\t" 
		<< (it->stockPrice)/100.0 << "\t"
		<< (it->salesPrice)/100.0 <<"\t" 
		<< it->stockVolume << "\t"
		<< it->salesVolume << "\t"
		<< it->enable << endl;

}
void ListGoods::sortGoodsID(bool asc)
{
	listGoods.sort();
	if(!asc) // 要求倒序，反向
		listGoods.reverse();
}


bool get_YesNo()
{
	int i=3;
	char a[1024];
	printf(" \"\033[32mYes /\033[31m No\033[30m?\" ");

	while(i>0)
	{
		scanf("%s",a);
		char b = a[0];
		if(b == 'y' || b=='Y')
			return true;
		else if(b == 'n' || b == 'N')
			return false;
		else 
		{
			i--;
			printf("\"Yes / No\" ?  ");
			fflush(stdout);
		}	

	}
	return false;
}
