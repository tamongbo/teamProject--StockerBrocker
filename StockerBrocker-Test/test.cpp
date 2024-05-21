#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../StockerBrocker/Adapter.cpp"
#include "../StockerBrocker/StockerBrockerApp.cpp"
#include <string>

using namespace std;
using namespace testing;

class AdapterMock : public Adapter {
public:
	MOCK_METHOD(void, login, (string, string), (override));
	MOCK_METHOD(void, buy, (string, int, int), (override));
	MOCK_METHOD(void, sell, (string, int, int), (override));
	MOCK_METHOD(int, currentPrice, (string, int), (override));
};

TEST(TestCaseName, LoginSuccess) {
	StockerBrocker app;
	AdapterMock mock;
	
	app.selectStockBrocker(&mock);

	string name = "Fake Name";
	string password = "Fake Password";
	
	EXPECT_CALL(mock, login(name, password))
		.Times(1);

	app.login(name, password);
}

TEST(TestCaseName, BuySuccess) {
	StockerBrocker app;
	AdapterMock mock;

	app.selectStockBrocker(&mock);

	string stockCode = "0xFF";
	int count = 0; 
	int price = 0;

	EXPECT_CALL(mock, buy(stockCode, count, price))
		.Times(1);

	app.buy(stockCode, count, price);
}

TEST(TestCaseName, CurrentPriceSuccess) {
	StockerBrocker app;
	AdapterMock mock;

	app.selectStockBrocker(&mock);

	string stockCode = "ABCDE";
	int minute = 0;

	int price = 1000;
	EXPECT_CALL(mock, currentPrice(stockCode, minute))
		.Times(1)
		.WillOnce(testing::Return(price));

	EXPECT_EQ(price, app.currentPrice(stockCode, minute));
}

TEST(TestCaseName, CurrentPriceFail) {
	StockerBrocker app;
	AdapterMock mock;

	app.selectStockBrocker(&mock);

	string stockCode = "AA";
	int minute = 0;

	EXPECT_CALL(mock, currentPrice(stockCode, minute))
		.Times(0);

	try {
		app.currentPrice(stockCode, minute);
		FAIL();
	}
	catch (invalid_argument& err) {
		EXPECT_EQ(string("Stock code must be 5 characters"), string(err.what()));
	}
}