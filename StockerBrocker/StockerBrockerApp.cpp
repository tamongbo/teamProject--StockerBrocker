#pragma once
#include "Adapter.cpp"
#include <unordered_map>
using namespace std;

struct LoginInfo
{
	string id;
	string password;
};

class StockerBrocker {
public:
	void selectStockBrocker(Adapter* adapter) {
		this->adapter = adapter;
	}

	void login(string ID, string password) {
		if (loginInfo.find(ID) != loginInfo.end())
		{
			throw invalid_argument("Already registered id");
		}
		loginInfo.insert(make_pair(ID, password));
		adapter->login(ID, password);
	}

	void buy(string stockCode, int count, int price) {
		adapter->buy(stockCode, count, price);
	}

	void sell(string stockCode, int count, int price) {
		adapter->sell(stockCode, count, price);
	}

	int currentPrice(string stockCode, int minutes) {
		adapter->currentPrice(stockCode, minutes);
	}

private:
	Adapter* adapter;
	unordered_map<string, string> loginInfo;
};