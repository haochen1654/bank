#ifndef BANK_DB_DBCONNECTION_H_
#define BANK_DB_DBCONNECTION_H_

#include <string>
#include <vector>

namespace bank {
    namespace db {
        class DBConnection {
        public:
            DBConnection(const std::string& url,
                const std::string& username,
                const std::string& password) :
                url_{url},
                username_{username},
                password_{password} {};
            ~DBConnection() {};

            std::vector<std::vector<std::string>> query(const std::string& schema, const std::string& query, int size_of_column);

            bool write(const std::string& schema, const std::string& query);

        private:
            std::string url_;
            std::string username_;
            std::string password_;
        };
    } // namespace db
} // namespace bank

#endif   // BANK_DB_DBCONNECTION_H_