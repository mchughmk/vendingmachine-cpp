#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include <string>

#include "vendingmachine.cc"
#include "coinpaymentprocessor.cc"
#include "mock_paymentdb.h"

using std::string;
using ::testing::Return;

class VendingMachineIntegrationTest : public ::testing::Test {
    public:
        VendingMachineIntegrationTest() {
            database = new MockPaymentDb();
            vm = new VendingMachine(new CoinPaymentProcessor(database));
        }

        ~VendingMachineIntegrationTest() {
            delete vm;
        }
    protected:
        VendingMachine* vm;
        MockPaymentDb* database;
};

TEST_F(VendingMachineIntegrationTest, ReleaseChange_WhenNoCoinsInserted_Expect0) {
    int expected = 0;

    int actual = vm->ReleaseChange();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, ReleaseChange_WhenOneCoinInserted_Expect25) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillOnce(Return(25));
    int expected = 25;

    int actual = vm->ReleaseChange();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, ReleaseChange_WhenTwoCoinsInserted_Expect50) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillOnce(Return(50));
    int expected = 50;

    int actual = vm->ReleaseChange();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, BuyProduct_WhenNoCoinsInserted_ExpectException) {
    ASSERT_ANY_THROW(vm->BuyProduct());
}

TEST_F(VendingMachineIntegrationTest, BuyProduct_WhenSufficientBalance_ExpectNoException) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillRepeatedly(Return(50));

    ASSERT_NO_THROW(vm->BuyProduct());
}

TEST_F(VendingMachineIntegrationTest, BuyProduct_WhenInsufficientBalance_ExpectException) {
    EXPECT_CALL(*database, SetBalance(25));
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillOnce(Return(0))
        .WillRepeatedly(Return(25));

    vm->InsertCoin();

    ASSERT_ANY_THROW(vm->BuyProduct());
}

TEST_F(VendingMachineIntegrationTest, BuyProduct_WhenSufficientBalanceAndProductBought_ExpectBalance0) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillOnce(Return(50))
        .WillOnce(Return(50))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*database, SetBalance(0));

    vm->BuyProduct();
}

TEST_F(VendingMachineIntegrationTest, ReleaseChange_WhenCalled_ExpectBalanceCleared) {
    EXPECT_CALL(*database, SetBalance(0));

    vm->ReleaseChange();
}

TEST_F(VendingMachineIntegrationTest, GetMessage_WhenNoCoins_ExpectBalance0) {
    string expected = "Balance: 0";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, GetMessage_WhenOneCoin_ExpectBalance25) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillOnce(Return(0))
        .WillOnce(Return(25));
    EXPECT_CALL(*database, SetBalance(25));
    vm->InsertCoin();
    string expected = "Balance: 25";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, GetMessage_WhenProductBoughtSuccessfully_ExpectEnjoy) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillRepeatedly(Return(50));
    vm->BuyProduct();
    string expected = "Enjoy!";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, GetMessage_WhenProductNotBoughtSuccessfully_ExpectInsufficientFunds) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillRepeatedly(Return(25));
    EXPECT_ANY_THROW(vm->BuyProduct());
    string expected = "Insufficient Funds";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, GetMessage_WhenChangeReleased_ExpectBalance0) {
    EXPECT_CALL(*database, GetCurrentBalance())
        .WillOnce(Return(0))
        .WillRepeatedly(Return(25));
    EXPECT_CALL(*database, SetBalance(25));
    EXPECT_CALL(*database, SetBalance(0));
    vm->InsertCoin();
    vm->ReleaseChange();
    string expected = "Balance: 0";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineIntegrationTest, InsertCoin_WhenCalled_ExpectProcessPayment25) {
    EXPECT_CALL(*database, SetBalance(25));

    vm->InsertCoin();
}