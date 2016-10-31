#ifndef __STORAGE_H__
#define __STORAGE_H__
#include "goods.h"
#include "log.h"
typedef list<Goods>::iterator list_it;

class ListGoods {
	public:
		ListGoods();
		~ListGoods();
	public:
		bool newGoodsName();
		bool stockGoods();

		list_it findGoodsID(unsigned id);
		list_it findGoodsName(string name);

		void sortGoodsID(bool asc = true);
		void sortGoodsName(bool asc = true);
		void sortSalesPrice(bool asc = true);
		void sortSalesValume(bool asc = true);

		int getValue(int index, bool enablelist = false); // 1.销售额，2.库存金额，3.净利润


		bool stopGoods(bool reUp);

		void printGoodsInfo(const list_it & it ,bool printTitle = true);
		void printGoodsInfo();
		void printGoodsInfo(bool Up);

	public:
	protected:

		list<Goods> listGoods;	
};



#endif /*__STORAGE_H__*/
