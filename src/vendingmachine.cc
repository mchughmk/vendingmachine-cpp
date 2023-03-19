#include <stdexcept>
#include <string>

#include "product.cc"
#include "paymentprocessor.h"

using std::string;

class VendingMachine {
    public:
        VendingMachine(IPaymentProcessor* payment_processor) {
            paymentProcessor = payment_processor;
        }

        ~VendingMachine() {
            delete paymentProcessor;
        }

        int ReleaseChange() {
            int returnBalance = paymentProcessor->GetBalance();
            paymentProcessor->ClearPayment();
            message = "Balance: 0";
            return returnBalance;
        }

        void InsertCoin() {
            paymentProcessor->ProcessPayment(25);
            message = "Balance: " + std::to_string(paymentProcessor->GetBalance());
        }

        Product BuyProduct() {
            if (paymentProcessor->HasSufficientBalance(50)) {
                paymentProcessor->ProcessPurchase(50);
                message = "Enjoy!";
                return Product();
            }
            message = "Insufficient Funds";
            throw std::exception();
        }

        string GetMessage() {
            return message;
        }
    private:
        IPaymentProcessor* paymentProcessor;
        string message = "Balance: 0";
};