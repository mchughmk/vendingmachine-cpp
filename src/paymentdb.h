#ifndef PAYMENTDB_H
#define PAYMENTDB_H

struct IPaymentDb {
    virtual ~IPaymentDb() = default;

    virtual int GetCurrentBalance() = 0;
    virtual void SetBalance(int newBalance) = 0;
};

#endif
