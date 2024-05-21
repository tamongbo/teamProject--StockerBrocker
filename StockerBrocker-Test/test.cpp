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

class CurrentPriceTestFixture : public testing::Test {
public:
	void SetUp() {
		app.selectStockBrocker(&mock);
	}
	const int CUR_PRICE = 1000;
	const int CUR_MINETUE = 0;
	const string STOCK_CODE = "ABC12";
	const string WRONG_STOCK_CODE = "A1";

	StockerBrocker app;
	AdapterMock mock;
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

TEST_F(CurrentPriceTestFixture, CurrentPriceSuccess) {
	EXPECT_CALL(mock, currentPrice(STOCK_CODE, CUR_MINETUE))
		.Times(1)
		.WillOnce(testing::Return(CUR_PRICE));

	EXPECT_EQ(CUR_PRICE, app.currentPrice(STOCK_CODE, CUR_MINETUE));
}

TEST_F(CurrentPriceTestFixture, CurrentPriceFail) {
	EXPECT_CALL(mock, currentPrice(WRONG_STOCK_CODE, CUR_MINETUE))
		.Times(0);

	try {
		app.currentPrice(WRONG_STOCK_CODE, CUR_MINETUE);
		FAIL();
	}
	catch (invalid_argument& err) {
		EXPECT_EQ(string("Stock code must be 5 characters"), string(err.what()));
	}
}