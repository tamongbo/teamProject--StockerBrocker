#pragma once
#include "KiwerAPI.cpp"
#include "NemoAPI.cpp"
#include <string>

using namespace std;

class Adapter {
public:
	virtual void login(string ID, string password) = 0;
	virtual void buy(string stockCode, int count, int price) = 0;
	virtual void sell(string stockCode, int count, int price) = 0;
	virtual int currentPrice(string stockCode) = 0;
};

class AdapterKiwerAPI : public Adapter {
public:
	// Adapter을(를) 통해 상속됨
	void login(string ID, string password) override
	{
		api.login(ID, password);
	}
	void buy(string stockCode, int count, int price) override
	{
		api.buy(stockCode, count, price);
	}
	void sell(string stockCode, int count, int price) override
	{
		api.sell(stockCode, count, price);
	}
	int currentPrice(string stockCode) override
	{
		return api.currentPrice(stockCode);
	}
private:
	KiwerAPI api;
};

class AdapterNemoAPI : public Adapter {
public:
	// Adapter을(를) 통해 상속됨
	void login(string ID, string password) override
	{
		api.certification(ID, password);
	}
	void buy(string stockCode, int count, int price) override
	{
		api.purchasingStock(stockCode, price, count);
	}
	void sell(string stockCode, int count, int price) override
	{
		api.sellingStock(stockCode, price, count);
	}
	int currentPrice(string stockCode) override
	{
		return api.getMarketPrice(stockCode, 0);
	}
private:
	NemoAPI api;
};