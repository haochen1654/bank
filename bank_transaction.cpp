#include "bank_transaction.h"

#include <mysql_connection.h>
#include <cppconn/driver.h>

namespace bank {
        namespace {
            using ::bank::db::DBConnection;
            using ::bank::entity::BankAccount;

            auto del_con = [](sql::Connection* con)  // custom deleter
            {
                delete con;
            };
        }

        BankTransaction::BankTransaction(const std::string& url, const std::string& username, const std::string& password)
        {
            std::unique_ptr<sql::Connection, decltype(del_con)> con(get_driver_instance()->connect(url, username, password), del_con);
            this->db_conn_ = std::make_unique<DBConnection>(con);
        }
        bool BankTransaction::createAccount(const BankAccount&)
        {
            return false; 
        }
    
}