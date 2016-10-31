#include "goods.h" 
void Goods::printGoods(bool noPrintStockVolume)
{
	cout << goodsId << "\t"
		<< goodsName << "\t" 
		<< (salesPrice)/100.0 << "\t"
		<< salesVolume;
	if( !noPrintStockVolume )
	cout << "\t" << stockVolume;
}
bool Goods::operator<(Goods & right)
{
	return goodsId < right.goodsId;
}

// 用于商品名字排序的函数
bool Goods::compName(const Goods & left, const Goods & right)
{
	return (0 < left.goodsName.compare(right.goodsName));
}
bool Goods::compSalesPrice(const Goods & left, const Goods & right)
{
	return (left.salesPrice < right.salesPrice);
}
bool Goods::compSalesVolume(const Goods & left, const Goods & right)
{
	return (left.salesVolume < right.salesVolume);
}

