#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
    int rollNo;
    char name[50];
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
    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter marks in 5 subjects: ";
        for (int i = 0; i < 5; i++) cin >> marks[i];
        calculate();
    }

    void display() const {
        cout << setw(5) << rollNo << setw(15) << name 
             << setw(10) << percentage << setw(5) << grade << endl;
    }

    int getRollNo() const { return rollNo; }
};

void addStudent() {
    Student st;
    ofstream outFile("students.dat", ios::binary | ios::app);
    st.input();
    outFile.write(reinterpret_cast<char*>(&st), sizeof(Student));
    outFile.close();
    cout << "Record added successfully!\n";
}

void displayAll() {
    Student st;
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!\n";
        return;
    }
    cout << "ROLL  NAME            %AGE  GRADE\n";
    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        st.display();
    }
    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Result Management ---\n";
        cout << "1. Add Student\n2. Display All\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
        }
    } while (choice != 3);
    return 0;
}
