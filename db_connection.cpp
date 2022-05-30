#include "db_connection.h"

#include <iostream>
#include <memory>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

namespace bank {
    namespace db {
        namespace {
            void print_error_message(sql::SQLException& e) {

                std::cout << "# ERR: SQLException in " << __FILE__;
                std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
                std::cout << "# ERR: " << e.what();
                std::cout << " (MySQL error code: " << e.getErrorCode();
                std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            }
        }
        std::vector<std::vector<std::string>> DBConnection::query(const std::string& schema, 
                                                                  const std::string& query, 
                                                                  int size_of_column) {
            try {
                std::unique_ptr<sql::Connection> 
                    con(get_driver_instance()->connect(url_, username_, password_));

                /* Connect to the MySQL test database */
                con->setSchema(schema);

                // Send query to database
                std::unique_ptr<sql::ResultSet> 
                    res(con->createStatement()->executeQuery(query));
                
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
                print_error_message(e);
            }
        }

        bool  DBConnection::add(const std::string& schema,
                                const std::string& statement,
                                const std::vector<Data>& input) {
            try {
                std::unique_ptr<sql::Connection> 
                    con(get_driver_instance()->connect(url_, username_, password_));
                con->setSchema(schema);
                std::unique_ptr<sql::PreparedStatement> 
                    pstmt(con->prepareStatement(statement));
                for (int i = 0; i < input.size(); ++i) {
                    switch (input[i].type) {
                    case SQLTYPE::kString: 
                        pstmt->setString(i + 1, input[i].value.string_value);
                        break;
                    case SQLTYPE::kInteger: 
                        pstmt->setInt(i + 1, input[i].value.int_value);
                        break;
                    case SQLTYPE::kDouble: 
                        pstmt->setDouble(i + 1, input[i].value.double_value);
                        break;
                    default: 
                        std::cout << "Error: input data has unknow sqltype." << std::endl;
                        return true;
                    }
                }
                pstmt->execute();
                return true;
            } catch (sql::SQLException& e) {
                print_error_message(e);
                return false;
            }
        }
    }
}