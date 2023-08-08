#include <gtest/gtest.h>

#include "coinpaymentprocessor.cc"
#include "paymentdb.cc"

class CoinPaymentProcessorIntegrationTest : public ::testing::Test {
    public:
        CoinPaymentProcessorIntegrationTest() {
            processor = new CoinPaymentProcessor(new PaymentDb());
        }

        ~CoinPaymentProcessorIntegrationTest() {
            delete processor;
        }

    protected:
        CoinPaymentProcessor* processor;
};

TEST_F(CoinPaymentProcessorIntegrationTest, GetBalance_WhenNoPaymentProcessed_Expect0) {
    int expected = 0;

    int actual = processor->GetBalance();

    ASSERT_EQ(expected, actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, GetBalance_WhenPayment25Processed_Expect25) {
    processor->ProcessPayment(25);
    int expected = 25;

    int actual = processor->GetBalance();

    ASSERT_EQ(expected, actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, GetBalance_WhenPayment25ProcessedTwice_Expect50) {
    processor->ProcessPayment(25);
    processor->ProcessPayment(25);
    int expected = 50;

    int actual = processor->GetBalance();

    ASSERT_EQ(expected, actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, HasSufficientBalance_WhenNoPayment_ExpectFalse) {
    bool actual = processor->HasSufficientBalance(50);

    ASSERT_FALSE(actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, HasSufficientBalance_WhenNotEnoughPayment_ExpectFalse) {
    processor->ProcessPayment(25);

    bool actual = processor->HasSufficientBalance(50);

    ASSERT_FALSE(actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, HasSufficientBalance_WhenMoreThanEnoughPayment_ExpectTrue) {
    processor->ProcessPayment(75);

    bool actual = processor->HasSufficientBalance(50);

    ASSERT_TRUE(actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, GetBalance_WhenPaymentProcessedAndCleared_Expect0) {
    processor->ProcessPayment(25);
    processor->ClearPayment();
    int expected = 0;

    int actual = processor->GetBalance();

    ASSERT_EQ(expected, actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, GetBalance_WhenPayment50AndPurchased50_Expect0) {
    processor->ProcessPayment(50);
    processor->ProcessPurchase(50);
    int expected = 0;

    int actual = processor->GetBalance();

    ASSERT_EQ(expected, actual);
}

TEST_F(CoinPaymentProcessorIntegrationTest, GetBalance_WhenPayment75AndPurchased50_Expect25) {
    processor->ProcessPayment(75);
    processor->ProcessPurchase(50);
    int expected = 25;

    int actual = processor->GetBalance();

    ASSERT_EQ(expected, actual);
}