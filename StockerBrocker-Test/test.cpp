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

TEST_F(StockerbrokerFixture, Buy0CountFailException)
{
	EXPECT_THROW(app.buy(STOCK_CODE, 0, 100), exception);
}

TEST_F(StockerbrokerFixture, MinusPriceFailException)
{
	EXPECT_THROW(app.buy(STOCK_CODE, 100, -100), exception);
}

TEST_F(StockerbrokerFixture, DISABLED_SellNiceTimingSuccess)
{
	int count = 100;

	EXPECT_CALL(mock, currentPrice(STOCK_CODE, 0))
		.WillOnce(Return(100))
		.WillOnce(Return(90))
		.WillOnce(Return(70));

	EXPECT_CALL(mock, buy(STOCK_CODE, count, app.currentPrice(STOCK_CODE, 0)))
		.Times(1);
	app.login(NAME, PASSWORD);
}
TEST_F(CurrentPriceTestFixture, BuyNiceTimingWhenBuyCase)
{
	const int MAX_BUY_COUNT = 100;

	EXPECT_CALL(mock, currentPrice(STOCK_CODE, 0)).
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
TEST_F(StockerbrokerFixture, DISABLED_SellNiceTimingFail)
{
	int count = 100;

	EXPECT_CALL(mock, currentPrice(STOCK_CODE, 0))
		.WillOnce(Return(100))
		.WillOnce(Return(90))
		.WillOnce(Return(95));

	EXPECT_THROW(app.sellNiceTiming(STOCK_CODE, count), exception);
}

TEST_F(StockerbrokerFixture, SellSuccess)
{
	int count = 5;
	int price = 1000;

	EXPECT_CALL(mock, sell(STOCK_CODE, count, price))
		.Times(1);

	app.sell(STOCK_CODE, count, price);
}

TEST_F(StockerbrokerFixture, SellZeroCountException)
{
	int count = 0;
	int price = 1000;

	EXPECT_CALL(mock, sell(STOCK_CODE, count, price))
		.Times(0);

	EXPECT_THROW(app.sell(STOCK_CODE, count, price), exception);
}

TEST_F(StockerbrokerFixture, SellZeroPriceException)
{
	int count = 5;
	int price = 0;

	EXPECT_CALL(mock, sell(STOCK_CODE, count, price))
		.Times(0);
	EXPECT_THROW(app.sell(STOCK_CODE, count, price), exception);
}

TEST_F(CurrentPriceTestFixture, CurrentPriceSuccess)
{
	EXPECT_CALL(mock, currentPrice(STOCK_CODE, CUR_MINETUE))
		.Times(1)
		.WillOnce(testing::Return(CUR_PRICE));

	EXPECT_EQ(CUR_PRICE, app.currentPrice(STOCK_CODE, CUR_MINETUE));
}

TEST_F(CurrentPriceTestFixture, CurrentPriceFail)
{
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