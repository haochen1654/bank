#include "bank_transaction.h"

#include <mysql_connection.h>
#include <cppconn/driver.h>

namespace bank {
        namespace {
            using ::bank::db::DBConnection;
            using ::bank::entity::BankAccount;
        }

        BankTransaction::BankTransaction(const std::string& url, const std::string& username, const std::string& password) {
            this->db_conn_ = std::make_unique<DBConnection>(url, username, password);
        }

        bool BankTransaction::createAccount(const BankAccount&) {
            return false; 
        }
}