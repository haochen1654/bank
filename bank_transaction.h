#ifndef BANK_ENTITY_BANKTRANSACTION_H_
#define BANK_ENTITY_BANKTRANSACTION_H_

#include <memory>
#include <string>
#include "db_connection.h"
#include "bank_account.h"

namespace bank {
        class BankTransaction {
        public:
            BankTransaction(const std::string& url,
                            const std::string& username,
                            const std::string& password,
                            const std::string& schema);
            ~BankTransaction() {};
            bool createAccount(const entity::BankAccount&);
            bool closeAccount(int);
            bool deposit(int, double);
            bool withdraw(int, double);
            entity::BankAccount getAccount(int);
            void printAllAccounts();
            void message(const std::string&);
        private:
            std::string schema_;
            std::unique_ptr<bank::db::DBConnection> db_conn_;
        }; 
} // namespace bank

#endif   // BANK_ENTITY_BANKTRANSACTION_H_