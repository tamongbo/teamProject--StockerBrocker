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
		if (count <= 0)
			throw exception("StockerBrockerBuy0CountException");
		if (price <= 0)
			throw exception("StockerBrockerPriceException");

		adapter->buy(stockCode, count, price);
	}

	void sell(string stockCode, int count, int price) {
		if (count <= 0) {
			throw exception("1개 이상의 매도 주문만 설정 가능합니다.");
		}

		if (price <= 0) {
			throw exception("1원 이상의 매도 주문만 설정 가능합니다.");
		}
		adapter->sell(stockCode, count, price);
	}

	int currentPrice(string stockCode, int minutes) {
		if (stockCode.length() != STOCK_CODE_LENGTH)
			throw invalid_argument("Stock code must be 5 characters");

		return adapter->currentPrice(stockCode, minutes);

		return adapter->currentPrice(stockCode, minutes);
	}

	void sellNiceTiming(string stockCode, int price) {

	}

private:
	Adapter* adapter;
	const int STOCK_CODE_LENGTH = 5;
};