#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <mysql/mysql.h>
using namespace std;

// ✅ MySQL connection parameters
const char* HOST = "localhost";
const char* USER = "student_user";
const char* PASS = "Student@1234";
const char* DB   = "student_db";

// ✅ MySQL connection object
MYSQL* conn;

// ✅ Function to connect to DB
bool connectDB() {
    conn = mysql_init(NULL);
    if (!conn) {
        cerr << "MySQL initialization failed!" << endl;
        return false;
    }

    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 3306, NULL, 0)) {
        cerr << "MySQL connection error: " << mysql_error(conn) << endl;
        return false;
    }
    return true;
}

// ✅ Secure Admin Login
bool adminLogin() {
    string email, password;
    cout << "Enter admin email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    string query = 
        "SELECT email FROM admins "
        "WHERE email='" + email + 
        "' AND password_hash=SHA2('" + password + "',256)";

    if (mysql_query(conn, query.c_str())) {
        cerr << "Query Error: " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    bool success = (mysql_num_rows(res) > 0);
    mysql_free_result(res);

    if (success) cout << "✔ Admin Login Successful!\n";
    else cout << "❌ Invalid credentials!\n";

    return success;
}

// ✅ Add Student
void addStudent() {
    int roll, sub1, sub2, sub3, sub4, sub5;
    string name;

    cout << "Enter Roll No: "; cin >> roll;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter marks (5 subjects): ";
    cin >> sub1 >> sub2 >> sub3 >> sub4 >> sub5;

    float percentage = (sub1+sub2+sub3+sub4+sub5)/5.0;
    char grade = (percentage>=90)?'A':(percentage>=75)?'B':(percentage>=50)?'C':'F';

    string query = "INSERT INTO students VALUES (" 
        + to_string(roll) + ", '" + name + "', "
        + to_string(sub1) + "," + to_string(sub2) + "," 
        + to_string(sub3) + "," + to_string(sub4) + "," 
        + to_string(sub5) + "," + to_string(percentage) 
        + ",'" + grade + "') "
        "ON DUPLICATE KEY UPDATE "
        "name=VALUES(name), sub1=VALUES(sub1), sub2=VALUES(sub2), "
        "sub3=VALUES(sub3), sub4=VALUES(sub4), sub5=VALUES(sub5), "
        "percentage=VALUES(percentage), grade=VALUES(grade)";

    if (mysql_query(conn, query.c_str())) {
        cerr << "Insert Error: " << mysql_error(conn) << endl;
    } else {
        cout << "✔ Student record added/updated!\n";
    }
}

// ✅ Display All Students
void displayAll() {
    if (mysql_query(conn, "SELECT * FROM students")) {
        cerr << "Select Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "\nROLL   NAME          S1  S2  S3  S4  S5   %AGE   GRADE\n";
    cout << "-------------------------------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << setw(4) << row[0] << "  " << setw(12) << row[1]
             << "  " << setw(3) << row[2] << "  " << setw(3) << row[3]
             << "  " << setw(3) << row[4] << "  " << setw(3) << row[5]
             << "  " << setw(3) << row[6] << "  " << setw(6) << row[7]
             << "  " << setw(2) << row[8] << endl;
    }
    mysql_free_result(res);
}

// ✅ Search Student
void searchStudent() {
    int roll;
    cout << "Enter Roll No: "; cin >> roll;
    string query = "SELECT * FROM students WHERE roll=" + to_string(roll);

    if (mysql_query(conn, query.c_str())) {
        cerr << "Search Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(res))) {
        cout << "\nROLL   NAME          S1  S2  S3  S4  S5   %AGE   GRADE\n";
        cout << "-------------------------------------------------------\n";
        cout << setw(4) << row[0] << "  " << setw(12) << row[1]
             << "  " << setw(3) << row[2] << "  " << setw(3) << row[3]
             << "  " << setw(3) << row[4] << "  " << setw(3) << row[5]
             << "  " << setw(3) << row[6] << "  " << setw(6) << row[7]
             << "  " << setw(2) << row[8] << endl;
    } else {
        cout << "❌ Student not found!\n";
    }
    mysql_free_result(res);
}

// ✅ Delete Student
void deleteStudent() {
    int roll;
    cout << "Enter Roll No to delete: "; cin >> roll;
    string query = "DELETE FROM students WHERE roll=" + to_string(roll);

    if (mysql_query(conn, query.c_str())) {
        cerr << "Delete Error: " << mysql_error(conn) << endl;
    } else {
        cout << "✔ Record deleted!\n";
    }
}

// ✅ Admin Menu
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Student\n2. Display All\n3. Search\n4. Delete\n5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
        }
    } while (choice != 5);
}

// ✅ Student Menu
void studentMenu() {
    int roll;
    cout << "Enter your Roll No: ";
    cin >> roll;

    string query = "SELECT * FROM students WHERE roll=" + to_string(roll);
    if (mysql_query(conn, query.c_str())) {
        cerr << "Query Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    if ((row = mysql_fetch_row(res))) {
        cout << "\n--- Your Result ---\n";
        cout << "ROLL   NAME          %AGE   GRADE\n";
        cout << "--------------------------------\n";
        cout << setw(4) << row[0] << "  " << setw(12) << row[1]
             << "  " << setw(6) << row[7] << "  " << setw(2) << row[8] << endl;
    } else {
        cout << "❌ Record not found!\n";
    }
    mysql_free_result(res);
}

// ✅ Main
int main() {
    if (!connectDB()) return 1;

    int choice;
    do {
        cout << "\n=== Student Result Management System ===\n";
        cout << "1. Admin Login\n2. Student Login\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: if (adminLogin()) adminMenu(); break;
            case 2: studentMenu(); break;
        }
    } while (choice != 3);

    mysql_close(conn);
    return 0;
}
