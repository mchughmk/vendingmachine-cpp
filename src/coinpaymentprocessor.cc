#include "paymentprocessor.h"

class CoinPaymentProcessor : public IPaymentProcessor {
    public:
        int GetBalance() override {
            return balance;
        }

        void ProcessPayment(int paymentAmount) override {
            balance += paymentAmount;
        }

        bool HasSufficientBalance(int purchasePrice) override {
            return (balance >= purchasePrice);
        }

        void ClearPayment() override {
            balance = 0;
        }

        void ProcessPurchase(int purchasePrice) override {
            balance -= purchasePrice;
        }
    private:
        int balance = 0;
};