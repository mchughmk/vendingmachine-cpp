#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include <string>

#include "vendingmachine.cc"
#include "mock_paymentprocessor.h"

using std::string;
using ::testing::Return;

class VendingMachineTest : public ::testing::Test {
    public:
        VendingMachineTest() {
            paymentProcessor = new MockPaymentProcessor;
            vm = new VendingMachine(paymentProcessor);
        }

        ~VendingMachineTest() {
            delete vm;
        }
    protected:
        VendingMachine* vm;
        MockPaymentProcessor* paymentProcessor;
};

TEST_F(VendingMachineTest, ReleaseChange_WhenNoCoinsInserted_Expect0) {
    int expected = 0;

    int actual = vm->ReleaseChange();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, ReleaseChange_WhenOneCoinInserted_Expect25) {
    EXPECT_CALL(*paymentProcessor, GetBalance())
        .WillOnce(Return(25));
    int expected = 25;

    int actual = vm->ReleaseChange();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, ReleaseChange_WhenTwoCoinsInserted_Expect50) {
    EXPECT_CALL(*paymentProcessor, GetBalance())
        .WillOnce(Return(50));
    int expected = 50;

    int actual = vm->ReleaseChange();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, BuyProduct_WhenNoCoinsInserted_ExpectException) {
    ASSERT_ANY_THROW(vm->BuyProduct());
}

TEST_F(VendingMachineTest, BuyProduct_WhenSufficientBalance_ExpectNoException) {
    EXPECT_CALL(*paymentProcessor, HasSufficientBalance(50))
        .WillOnce(Return(true));

    ASSERT_NO_THROW(vm->BuyProduct());
}

TEST_F(VendingMachineTest, BuyProduct_WhenInsufficientBalance_ExpectException) {
    EXPECT_CALL(*paymentProcessor, HasSufficientBalance(50))
        .WillOnce(Return(false));

    vm->InsertCoin();

    ASSERT_ANY_THROW(vm->BuyProduct());
}

TEST_F(VendingMachineTest, BuyProduct_WhenSufficientBalanceAndProductBought_ExpectProcessPurchase50) {
    EXPECT_CALL(*paymentProcessor, HasSufficientBalance(50))
        .WillOnce(Return(true));
    EXPECT_CALL(*paymentProcessor, ProcessPurchase(50))
        .Times(1);

    vm->BuyProduct();
}

TEST_F(VendingMachineTest, ReleaseChange_WhenCalledTwice_Expect0SecondTime) {
    EXPECT_CALL(*paymentProcessor, ClearPayment())
        .Times(1);

    vm->ReleaseChange();
}

TEST_F(VendingMachineTest, GetMessage_WhenNoCoins_ExpectBalance0) {
    string expected = "Balance: 0";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, GetMessage_WhenOneCoin_ExpectBalance25) {
    EXPECT_CALL(*paymentProcessor, GetBalance())
        .WillOnce(Return(25));
    vm->InsertCoin();
    string expected = "Balance: 25";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, GetMessage_WhenProductBoughtSuccessfully_ExpectEnjoy) {
    EXPECT_CALL(*paymentProcessor, HasSufficientBalance(50))
        .WillOnce(Return(true));
    vm->BuyProduct();
    string expected = "Enjoy!";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, GetMessage_WhenProductNotBoughtSuccessfully_ExpectInsufficientFunds) {
    EXPECT_CALL(*paymentProcessor, HasSufficientBalance(50))
        .WillOnce(Return(false));
    EXPECT_ANY_THROW(vm->BuyProduct());
    string expected = "Insufficient Funds";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, GetMessage_WhenChangeReleased_ExpectBalance0) {
    vm->InsertCoin();
    vm->ReleaseChange();
    string expected = "Balance: 0";

    string actual = vm->GetMessage();

    ASSERT_EQ(expected, actual);
}

TEST_F(VendingMachineTest, InsertCoin_WhenCalled_ExpectProcessPayment25) {
    EXPECT_CALL(*paymentProcessor, ProcessPayment(25))
        .Times(1);

    vm->InsertCoin();
}