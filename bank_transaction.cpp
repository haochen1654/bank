#include "bank_transaction.h"

#include <mysql_connection.h>
#include <cppconn/driver.h>

namespace bank {
        namespace {
            using ::bank::db::DBConnection;
            using ::bank::db::Data;
            using ::bank::entity::BankAccount;
            using ::bank::db::SQLTYPE;
            

            const char* kStatement = "INSERT INTO bank_account (id, first_name, last_name, balance) VALUES (?, ?, ?, ?)";

            std::vector<Data> createData(const BankAccount& bank_account) {
                std::vector<Data> input;
                input.push_back({ SQLTYPE::kInteger, { bank_account.account_numer(),  0.0, ""}});
                input.push_back({ SQLTYPE::kString, {0, 0.0, bank_account.first_name()} });
                input.push_back({ SQLTYPE::kString, {0, 0.0, bank_account.last_name()} });
                input.push_back({ SQLTYPE::kDouble, {0, bank_account.balance(), ""}});
                return input;
            }
        }

        BankTransaction::BankTransaction(const std::string& url, 
                                         const std::string& username, 
                                         const std::string& password, 
                                         const std::string& schema) {
            this->db_conn_ = std::make_unique<DBConnection>(url, username, password);
            this->schema_ = schema;
        }

        bool BankTransaction::createAccount(const BankAccount& bank_account) {
            return db_conn_->add(schema_, kStatement, createData(bank_account));
        }
}