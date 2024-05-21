#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../StockerBrocker/Adapter.cpp"
#include "../StockerBrocker/StockerBrockerApp.cpp"
#include <string>

using namespace std;
using namespace testing;

int MAX_BUY_COUNT = 100;

class AdapterMock : public Adapter
{
public:
	MOCK_METHOD(void, login, (string, string), (override));
	MOCK_METHOD(void, buy, (string, int, int), (override));
	MOCK_METHOD(void, sell, (string, int, int), (override));
	MOCK_METHOD(int, currentPrice, (string, int), (override));
};

TEST(TestCaseName, LoginSuccess)
{
	StockerBrocker app;
	AdapterMock mock;

	app.selectStockBrocker(&mock);

	string name = "Fake Name";
	string password = "Fake Password";

	EXPECT_CALL(mock, login(name, password))
		.Times(1);

	app.login(name, password);
}

TEST(TestCaseName, BuySuccess)
{
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

TEST(TestCaseName, getPriceSuccess)
{
	StockerBrocker app;
	AdapterMock mock;

	app.selectStockBrocker(&mock);

	string stockCode = "0xFF";
	int count = 0;
	int price = 0;

	EXPECT_CALL(mock, currentPrice(stockCode, 1))
		.Times(1);

	app.currentPrice(stockCode, 1);

	EXPECT_CALL(mock, currentPrice(stockCode, 1))
		.Times(1);

	app.currentPrice(stockCode, 1);
}

TEST(TestCaseName, BuyNiceTimingWhenBuyCase)
{
	StockerBrocker app;
	AdapterMock mock;

	app.selectStockBrocker(&mock);

	string stockCode = "0xFF";
	int count = 0;
	int price = 0;

	EXPECT_CALL(mock, currentPrice(stockCode,0)).
		WillOnce(Return(100)).
		WillOnce(Return(120)).
		WillOnce(Return(140));

	EXPECT_CALL(mock, buy(stockCode, MAX_BUY_COUNT, price)).Times(1);

	app.buyNiceTiming(stockCode, price);
}
TEST(TestCaseName, BuyNiceTimingWhenNotBuyCase)
{
	StockerBrocker app;
	AdapterMock mock;

	app.selectStockBrocker(&mock);

	string stockCode = "0xFF";
	int count = 0;
	int price = 0;

	EXPECT_CALL(mock, currentPrice(stockCode, 0)).
		WillOnce(Return(100)).
		WillOnce(Return(180)).
		WillOnce(Return(140));

	EXPECT_CALL(mock, buy(stockCode, MAX_BUY_COUNT, price)).Times(0);
	app.buyNiceTiming(stockCode, price);

}