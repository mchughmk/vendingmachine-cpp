#include "paymentdb.h"

class PaymentDb : public IPaymentDb {
    public:
        int GetCurrentBalance() override {
            return balance;
        }

        void SetBalance(int newBalance) override {
            balance = newBalance;
        }

    private:
        int balance = 0;
};