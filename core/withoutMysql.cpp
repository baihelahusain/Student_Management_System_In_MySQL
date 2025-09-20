#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
using namespace std;

class Student {
    int rollNo;
    string name;
    int marks[5];
    float percentage;
    char grade;

    void calculate() {
        int total = 0;
        for (int i = 0; i < 5; i++) total += marks[i];
        percentage = total / 5.0;

        if (percentage >= 90) grade = 'A';
        else if (percentage >= 75) grade = 'B';
        else if (percentage >= 50) grade = 'C';
        else grade = 'F';
    }

public:
    Student() : rollNo(0), percentage(0), grade('F') {}

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter marks in 5 subjects: ";
        for (int i = 0; i < 5; i++) cin >> marks[i];
        calculate();
    }

    void display() const {
        cout << setw(5) << rollNo << setw(15) << name 
             << setw(10) << percentage << setw(8) << grade << endl;
    }

    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    float getPercentage() const { return percentage; }
    char getGrade() const { return grade; }

    void writeToFile(ofstream &outFile) {
        outFile.write((char*)this, sizeof(Student));
    }

    void readFromFile(ifstream &inFile) {
        inFile.read((char*)this, sizeof(Student));
    }
};

map<int, Student> studentDB;  // STL Map for fast access

// ✅ Load students from file into map
void loadData() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) return;

    Student st;
    while (inFile.read((char*)&st, sizeof(Student))) {
        studentDB[st.getRollNo()] = st;
    }
    inFile.close();
}

// ✅ Save all students back to file
void saveData() {
    ofstream outFile("students.dat", ios::binary | ios::trunc);
    for (auto &pair : studentDB) {
        outFile.write((char*)&pair.second, sizeof(Student));
    }
    outFile.close();
}

// ✅ Add student
void addStudent() {
    Student st;
    st.input();
    studentDB[st.getRollNo()] = st;
    saveData();
    cout << "✔ Student record added successfully!\n";
}

// ✅ Display all
void displayAll() {
    cout << "\nROLL   NAME            %AGE   GRADE\n";
    cout << "-----------------------------------\n";
    for (auto &pair : studentDB) {
        pair.second.display();
    }
}

// ✅ Search student
void searchStudent() {
    int r;
    cout << "Enter Roll No to search: ";
    cin >> r;
    if (studentDB.find(r) != studentDB.end()) {
        cout << "\nROLL   NAME            %AGE   GRADE\n";
        cout << "-----------------------------------\n";
        studentDB[r].display();
    } else {
        cout << "❌ Student not found!\n";
    }
}

// ✅ Update student
void updateStudent() {
    int r;
    cout << "Enter Roll No to update: ";
    cin >> r;
    if (studentDB.find(r) != studentDB.end()) {
        cout << "Enter new details:\n";
        Student st;
        st.input();
        studentDB[r] = st;
        saveData();
        cout << "✔ Record updated successfully!\n";
    } else {
        cout << "❌ Student not found!\n";
    }
}

// ✅ Delete student
void deleteStudent() {
    int r;
    cout << "Enter Roll No to delete: ";
    cin >> r;
    if (studentDB.erase(r)) {
        saveData();
        cout << "✔ Record deleted successfully!\n";
    } else {
        cout << "❌ Student not found!\n";
    }
}

// ✅ Export results to CSV
void exportCSV() {
    ofstream file("results.csv");
    file << "Roll No,Name,Percentage,Grade\n";
    for (auto &pair : studentDB) {
        file << pair.second.getRollNo() << ","
             << pair.second.getName() << ","
             << pair.second.getPercentage() << ","
             << pair.second.getGrade() << "\n";
    }
    file.close();
    cout << "✔ Data exported to results.csv\n";
}

// ✅ Admin Menu
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Student\n2. Display All\n3. Search\n4. Update\n5. Delete\n6. Export CSV\n7. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exportCSV(); break;
        }
    } while (choice != 7);
}

// ✅ Student Menu
void studentMenu() {
    int roll;
    cout << "Enter your Roll No: ";
    cin >> roll;

    if (studentDB.find(roll) != studentDB.end()) {
        cout << "\n--- Your Result ---\n";
        cout << "ROLL   NAME            %AGE   GRADE\n";
        cout << "-----------------------------------\n";
        studentDB[roll].display();
    } else {
        cout << "❌ Record not found!\n";
    }
}

// ✅ Main
int main() {
    loadData();
    int choice;

    do {
        cout << "\n=== Student Result Management System ===\n";
        cout << "1. Admin Login\n2. Student Login\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: studentMenu(); break;
        }
    } while (choice != 3);

    saveData();
    return 0;
}
