#include "paymentprocessor.h"
#include "paymentdb.h"

class CoinPaymentProcessor : public IPaymentProcessor {
    public:
        CoinPaymentProcessor(IPaymentDb* payment_db) {
            database = payment_db;
        }

        ~CoinPaymentProcessor() {
            delete database;
        }

        int GetBalance() override {
            return database->GetCurrentBalance();
        }

        void ProcessPayment(int paymentAmount) override {
            int balance = GetBalance();
            database->SetBalance(balance + paymentAmount);
        }

        bool HasSufficientBalance(int purchasePrice) override {
            return (GetBalance() >= purchasePrice);
        }

        void ClearPayment() override {
            database->SetBalance(0);
        }

        void ProcessPurchase(int purchasePrice) override {
            int balance = GetBalance();
            database->SetBalance(balance - purchasePrice);
        }
    private:
        IPaymentDb* database;
};