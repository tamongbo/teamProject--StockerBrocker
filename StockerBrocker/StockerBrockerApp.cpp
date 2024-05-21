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
			throw exception("1�� �̻��� �ŵ� �ֹ��� ���� �����մϴ�.");
		}

		if (price <= 0) {
			throw exception("1�� �̻��� �ŵ� �ֹ��� ���� �����մϴ�.");
		}
		adapter->sell(stockCode, count, price);
	}

	int currentPrice(string stockCode, int minutes) {
		adapter->currentPrice(stockCode, minutes);
	}

private:
	Adapter* adapter;
};