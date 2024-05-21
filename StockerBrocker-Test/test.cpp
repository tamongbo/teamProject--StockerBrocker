#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../StockerBrocker/Adapter.cpp"
#include "../StockerBrocker/StockerBrockerApp.cpp"
#include <string>

using namespace std;
using namespace testing;

class AdapterMock : public Adapter
{
public:
	MOCK_METHOD(void, login, (string, string), (override));
	MOCK_METHOD(void, buy, (string, int, int), (override));
	MOCK_METHOD(void, sell, (string, int, int), (override));
	MOCK_METHOD(int, currentPrice, (string, int), (override));
};

class CurrentPriceTestFixture : public testing::Test
{
public:
	void SetUp()
	{
		app.selectStockBrocker(&mock);
	}
	const int CUR_PRICE = 1000;
	const int CUR_MINETUE = 0;
	const string STOCK_CODE = "ABC12";
	const string WRONG_STOCK_CODE = "A1";

	StockerBrocker app;
	AdapterMock mock;
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

TEST_F(StockerbrokerFixture, LoginSuccess)
{
	EXPECT_CALL(mock, login(NAME, PASSWORD))
		.Times(1);
	app.login(NAME, PASSWORD);
}

TEST_F(StockerbrokerFixture, BuySuccess)
{
	int count = 10;
	int price = 10;

	EXPECT_CALL(mock, buy(STOCK_CODE, count, price))
		.Times(1);
	app.buy(STOCK_CODE, count, price);
}
TEST_F(CurrentPriceTestFixture, BuyNiceTimingWhenBuyCase)
{
	const int MAX_BUY_COUNT = 100;

	EXPECT_CALL(mock, currentPrice(STOCK_CODE,0)).
		WillOnce(Return(100)).
		WillOnce(Return(120)).
		WillOnce(Return(140));

	EXPECT_CALL(mock, buy(STOCK_CODE, MAX_BUY_COUNT, CUR_PRICE)).Times(1);

	app.buyNiceTiming(STOCK_CODE, CUR_PRICE);
}
TEST_F(CurrentPriceTestFixture, BuyNiceTimingWhenNotBuyCase)
{
	const int MAX_BUY_COUNT = 100;

	EXPECT_CALL(mock, currentPrice(STOCK_CODE, 0)).
		WillOnce(Return(100)).
		WillOnce(Return(180)).
		WillOnce(Return(140));

	EXPECT_CALL(mock, buy(STOCK_CODE, MAX_BUY_COUNT, CUR_PRICE)).Times(0);
	app.buyNiceTiming(STOCK_CODE, CUR_PRICE);

}