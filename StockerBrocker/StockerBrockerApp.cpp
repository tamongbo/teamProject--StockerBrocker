#pragma once
#include "Adapter.cpp"

class StockerBrocker {
public:
	void selectStockBrocker(Adapter* adapter) {
		this->adapter = adapter;
	}

	void login(string ID, string password) {
		adapter->login(ID, password);
	}

	void buy(string stockCode, int count, int price) {
		adapter->buy(stockCode, count, price);
	}

	void sell(string stockCode, int count, int price) {
		adapter->sell(stockCode, count, price);
	}

	int currentPrice(string stockCode, int minutes) {
		if (stockCode.length() != STOCK_CODE_LENGTH)
			throw invalid_argument("Stock code must be 5 characters");

		return adapter->currentPrice(stockCode, minutes);
	}

private:
	Adapter* adapter;
	const int STOCK_CODE_LENGTH = 5;
};