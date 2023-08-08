#include <gtest/gtest.h>

#include "paymentdb.cc"

class PaymentDbTest : public ::testing::Test {
    protected:
        PaymentDb database;
};

TEST_F(PaymentDbTest, GetCurrentBalance_WhenNewDb_Expect0) {
    int expected = 0;

    int actual = database.GetCurrentBalance();

    ASSERT_EQ(expected, actual);
}

TEST_F(PaymentDbTest, GetCurrentBalance_WhenSetBalance50_Expect50) {
    int expected = 50;
    database.SetBalance(50);

    int actual = database.GetCurrentBalance();

    ASSERT_EQ(expected, actual);
}