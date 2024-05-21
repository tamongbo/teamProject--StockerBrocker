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

class StockerbrokerFixture : public Test
{
public:
	StockerBrocker app;
	AdapterMock mock;

	void SetUp() override
	{
		app.selectStockBrocker(&mock);
	}

	string NAME = "Fake Name";
	string PASSWORD = "Fake Password";
	string STOCK_CODE = "0xFF";
};

TEST_F(StockerbrokerFixture, LoginSuccess) {
	EXPECT_CALL(mock, login(NAME, PASSWORD))
		.Times(1);
	app.login(NAME, PASSWORD);
}

TEST_F(StockerbrokerFixture, BuySuccess) {
	int count = 10; 
	int price = 10;

	EXPECT_CALL(mock, buy(STOCK_CODE, count, price))
		.Times(1);
	app.buy(STOCK_CODE, count, price);
}

TEST_F(StockerbrokerFixture, Buy0CountFailException) {
	EXPECT_THROW(app.buy(STOCK_CODE, 0, 100), exception);
}

TEST_F(StockerbrokerFixture, MinusPriceFailException) {
	EXPECT_THROW(app.buy(STOCK_CODE, 100, -100), exception);

TEST(StockerbrokerFixture, SellSuccess) {
	int count = 5;
	int price = 1000;

	EXPECT_CALL(mock, sell(stockCode, count, price))
		.Times(1);

	app.sell(stockCode, count, price);
}

TEST(StockerbrokerFixture, SellZeroCountException) {
	int count = 0;
	int price = 1000;

	EXPECT_CALL(mock, sell(stockCode, count, price))
		.Times(0);

	EXPECT_THROW(app.sell(stockCode, count, price), exception);
}

TEST(StockerbrokerFixture, SellZeroPriceException) {
	int count = 5;
	int price = 0;

	EXPECT_CALL(mock, sell(stockCode, count, price))
		.Times(0);

	EXPECT_THROW(app.sell(stockCode, count, price), exception);
}