#include "db_connection.h"

#include <iostream>
#include <memory>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

namespace bank {
    namespace db {
        std::vector<std::vector<std::string>> DBConnection::query(const std::string& schema, const std::string& query, int size_of_column)
        {
            try {
                
                /* Connect to the MySQL test database */
                con_->setSchema(schema);

                // Send query to database
                std::unique_ptr<sql::ResultSet> res(con_->createStatement()->executeQuery(query));
                
                std::vector<std::vector<std::string>> output;

                while (res->next()) {
                    std::vector<std::string> tmp;
                    for (int i = 1; i <= size_of_column; ++i) {
                        tmp.push_back(res->getString(i));
                    }
                    output.push_back(tmp);
                }

                return output;
            } catch (sql::SQLException& e) {
                
                std::cout << "# ERR: SQLException in " << __FILE__;
                std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
                std::cout << "# ERR: " << e.what();
                std::cout << " (MySQL error code: " << e.getErrorCode();
                std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            
            }
        }
        bool DBConnection::write(const std::string& schema, const std::string& query)
        {
           
            return false;
            
        }
    }
}