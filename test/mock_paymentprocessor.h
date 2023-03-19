#ifndef MOCKPAYMENTPROCESSOR_H
#define MOCKPAYMENTPROCESSOR_H

#include "gmock/gmock.h"

#include "paymentprocessor.h"

class MockPaymentProcessor : public IPaymentProcessor {
    public:
        MOCK_METHOD(void, ProcessPayment, (int paymentAmount), (override));
        MOCK_METHOD(void, ProcessPurchase, (int purchaseAmount), (override));
        MOCK_METHOD(bool, HasSufficientBalance, (int purchaseAmount), (override));
        MOCK_METHOD(int, GetBalance, (), (override));
        MOCK_METHOD(void, ClearPayment, (), (override));
};

#endif