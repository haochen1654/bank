#ifndef BANK_ENTITY_BANKACCOUNT_H_
#define BANK_ENTITY_BANKACCOUNT_H_

#include <string>
#include <string_view>

namespace bank {
    namespace entity {
        class BankAccount {
        public:
            BankAccount(int account_number,
                std::string_view first_name,
                std::string_view last_name,
                double balance) :
                account_number_(account_number),
                first_name_(first_name_),
                last_name_(last_name_),
                balance_(balance) {}
            ~BankAccount() {}

            BankAccount(const BankAccount& other) = default;
            BankAccount& operator=(const BankAccount& other) = default;

            void set_account_number(int);
            void set_last_name(std::string_view);
            void set_first_name(std::string_view);
            void set_balance(double);

            int account_numer() const;
            std::string first_name() const;
            std::string last_name() const;
            double balance() const;

        private:
            int account_number_;
            std::string first_name_;
            std::string last_name_;
            double balance_;
        };
    } // namespace enity
} // namespace bank

#endif   // BANK_ENTITY_BANKACCOUNT_H_
