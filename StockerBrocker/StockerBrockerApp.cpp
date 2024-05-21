#pragma once
#include "Adapter.cpp"

class StockerBrocker
{
public:
	void selectStockBrocker(Adapter* adapter)
	{
		this->adapter = adapter;
	}

	void login(string ID, string password)
	{
		adapter->login(ID, password);
	}
	void buy(string stockCode, int count, int price)
	{
		if (count <= 0)
			throw exception("StockerBrockerBuy0CountException");
		if (price <= 0)
			throw exception("StockerBrockerPriceException");

		adapter->buy(stockCode, count, price);
	}

	void sell(string stockCode, int count, int price)
	{
		if (count <= 0) {
			throw exception("1개 이상의 매도 주문만 설정 가능합니다.");
		}

		if (price <= 0) {
			throw exception("1원 이상의 매도 주문만 설정 가능합니다.");
		}
		adapter->sell(stockCode, count, price);
	}

	int currentPrice(string stockCode, int minutes)
	{
		if (stockCode.length() != STOCK_CODE_LENGTH)
			throw invalid_argument("Stock code must be 5 characters");

		return adapter->currentPrice(stockCode, minutes);

		return adapter->currentPrice(stockCode, minutes);
	}

	void sellNiceTiming(string stockCode, int price)
	{

	}
	void buyNiceTiming(string stockCode, int price)
	{
		if (isPriceIncrease(stockCode, price) == true)
			adapter->buy(stockCode, MAX_BUY_COUNT, price);
	}
	bool isPriceIncrease(string stockCode, int price)
	{
		int priceCheckPriod = 10; //ms
		const int MAX_CHECK_COUNT = 3;
		int priceHistory[MAX_CHECK_COUNT + 1] = { 0 };

		for (int i = 1; i <= 3; i++)
		{
			priceHistory[i] = adapter->currentPrice(stockCode, 0);
			Sleep(priceCheckPriod);
			if (priceHistory[i - 1] >= priceHistory[i])
				return false;
		}
		return true;
	}

private:
	Adapter* adapter;
	int MAX_BUY_COUNT = 100;
	const int STOCK_CODE_LENGTH = 5;
};