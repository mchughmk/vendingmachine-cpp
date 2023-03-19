#ifndef PAYMENTPROCESSOR_H
#define PAYMENTPROCESSOR_H

struct IPaymentProcessor {
    virtual ~IPaymentProcessor() = default;

    virtual void ProcessPayment(int paymentAmount) = 0;
    virtual void ProcessPurchase(int purchasePrice) = 0;
    virtual bool HasSufficientBalance(int purchaseAmount) = 0;
    virtual int GetBalance() = 0;
    virtual void ClearPayment() = 0;
};

#endif