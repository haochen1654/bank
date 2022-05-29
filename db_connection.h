#ifndef BANK_DB_DBCONNECTION_H_
#define BANK_DB_DBCONNECTION_H_

#include <string>
#include <vector>
#include <memory>

#include <mysql_connection.h>

namespace bank {
    namespace db {
        class DBConnection {
        public:
            DBConnection(std::unique_ptr<sql::Connection> con) :
                con_{std::move(con)} {};
            ~DBConnection() {};

            std::vector<std::vector<std::string>> query(const std::string& schema, const std::string& query, int size_of_column);

            bool write(const std::string& schema, const std::string& query);

        private:
            std::unique_ptr<sql::Connection> con_;
        };
    } // namespace db
} // namespace bank

#endif   // BANK_DB_DBCONNECTION_H_