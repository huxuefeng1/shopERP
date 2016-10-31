#ifndef __GOODS_H__
#define __GOODS_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <list>
using namespace std;
bool get_YesNo();
class Goods {
	friend class ListGoods;
	public:
	Goods(unsigned id, string name, int stockP, int salesP)
		: goodsId(id), goodsName(name), stockPrice(stockP), salesPrice(salesP)
		  ,stockVolume(0), salesVolume(0), enable(1){}

	Goods(unsigned id, string name, int stockP, int salesP
			, int stockV, int salesV, bool enabled)
		: goodsId(id), goodsName(name), stockPrice(stockP), salesPrice(salesP)
		  ,stockVolume(stockV), salesVolume(salesV), enable(enabled){}

	public:
bool operator<(const Goods & right) const;
static bool compName(const Goods & left, const Goods & right);
static bool compSalesPrice(const Goods & left, const Goods & right);
static bool compSalesVolume(const Goods & left, const Goods & right);

	public:
	void printGoods( bool noPrintStockVolume = false );
	int getSalesPrice() { return salesPrice; }
	int getStockVolume() { return stockVolume; }
	bool getEnable() { return enable; }

	bool sellGoods(int cnt) { 
		if( cnt > 0 && cnt <= stockVolume) {
			stockVolume -= cnt;
			salesVolume += cnt;
			return true;	} else
			return false; }

	private:
	unsigned goodsId;
	string goodsName;
	int stockPrice;
	int salesPrice;
	int stockVolume;
	int salesVolume;
	bool enable; 

};

#endif /*__GOODS_H__*/
