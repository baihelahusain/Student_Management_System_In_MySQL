#include <iostream>
#include <mariadb/conncpp.hpp>

using namespace std;

int main() {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://localhost:3306/student_db");
        sql::Properties properties({
            {"user", "student_user"},
            {"password", "Student@1234"}
        });

        unique_ptr<sql::Connection> conn(driver->connect(url, properties));
        cout << "✅ Connected to MariaDB!" << endl;

        unique_ptr<sql::Statement> stmt(conn->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM students"));

        while (res->next()) {
            cout << "Roll: " << res->getInt("roll")
                 << ", Name: " << res->getString("name") << endl;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "❌ SQL Error: " << e.what() << endl;
    }
}
