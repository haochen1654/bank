#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "bank_transaction.h"

using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "Adif720.?";

int main()
{
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    //please create database "quickstartdb" ahead of time
    con->setSchema("quickstartdb");

    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS inventory");
    cout << "Finished dropping table (if existed)" << endl;
    stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
    cout << "Finished creating table" << endl;
    stmt->execute("DROP TABLE IF EXISTS bank_account");
    cout << "Finished dropping table (if existed)" << endl;
    stmt->execute("CREATE TABLE bank_account (id serial PRIMARY KEY, first_name VARCHAR(50), last_name VARCHAR(50), balance DOUBLE);");
    delete stmt;

    pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
    pstmt->setString(1, "banana");
    pstmt->setInt(2, 150);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "orange");
    pstmt->setInt(2, 154);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "apple");
    pstmt->setInt(2, 100);
    pstmt->execute();
    cout << "One row inserted." << endl;

    stmt = con->createStatement();
    auto* res = stmt->executeQuery("SELECT name, quantity FROM inventory;");
    while (res->next()) {

        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("name") << res->getString("quantity") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column data by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
    }

    delete pstmt;
    delete con;
    bank::BankTransaction trans(server, username, password, "quickstartdb");
    const bank::entity::BankAccount account_test(1, "henry", "chen", 100);
    trans.createAccount(account_test);
    
    system("pause");
    return 0;
}