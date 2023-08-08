#ifndef MOCKPAYMENTDB_H
#define MOCKPAYMENTDB_H

#include "gmock/gmock.h"

#include "paymentdb.h"

class MockPaymentDb : public IPaymentDb {
    public:
        MOCK_METHOD(int, GetCurrentBalance, (), (override));
        MOCK_METHOD(void, SetBalance, (int newBalance), (override));
};

#endif