#ifndef BANK_DB_DBCONNECTION_H_
#define BANK_DB_DBCONNECTION_H_

#include <string>
#include <vector>
#include <map>

namespace bank {
    namespace db {
        enum class SQLTYPE {
            kString = 0,
            kInteger,
            kDouble,
        };
        struct Value {
            int int_value;
            double double_value;
            std::string string_value;
        };
        struct Data {
            SQLTYPE type;
            Value value;
        };
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

            bool add(const std::string& schema, const std::string& statement, const std::vector<Data>& input);

        private:
            std::string url_;
            std::string username_;
            std::string password_;
        };
    } // namespace db
} // namespace bank

#endif   // BANK_DB_DBCONNECTION_H_