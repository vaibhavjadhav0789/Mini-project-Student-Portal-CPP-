#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    string name, course;
    float marks;

    Student(int i, string n, string c, float m) {
        id = i;
        name = n;
        course = c;
        marks = m;
    }

    string calculateGrade() {
        if (marks >= 90)
            return "A+";
        else if (marks >= 80)
            return "A";
        else if (marks >= 70)
            return "B";
        else if (marks >= 60)
            return "C";
        else if (marks >= 40)
            return "D";
        else
            return "Fail";
    }

    void display() {
        cout << "\nStudent ID: " << id;
        cout << "\nName: " << name;
        cout << "\nCourse: " << course;
        cout << "\nMarks: " << marks;
        cout << "\nGrade: " << calculateGrade() << endl;
    }
};

class StudentPortal {
    vector<Student> students;

public:
    void addStudent(int id, string name,
                    string course, float marks) {

        for (auto &s : students) {
            if (s.id == id) {
                cout << "Student ID Already Exists!\n";
                return;
            }
        }

        if (marks < 0 || marks > 100) {
            cout << "Invalid Marks!\n";
            return;
        }

        students.emplace_back(id, name, course, marks);
        cout << "Student Added Successfully!\n";
    }

    void displayStudents() {
        if (students.empty()) {
            cout << "No Student Records Found!\n";
            return;
        }

        cout << "\n----- STUDENT RECORDS -----\n";

        for (auto &s : students) {
            s.display();
        }
    }

    void searchStudent(int id) {
        for (auto &s : students) {
            if (s.id == id) {
                cout << "\nStudent Found!";
                s.display();
                return;
            }
        }

        cout << "Student Not Found!\n";
    }

    void saveData() {
        ofstream file("students.txt");

        for (auto &s : students) {
            file << s.id << ","
                 << s.name << ","
                 << s.course << ","
                 << s.marks << endl;
        }

        file.close();
        cout << "Student Records Saved Successfully!\n";
    }

    void loadData() {
        ifstream file("students.txt");

        if (!file) {
            cout << "No Saved Records Found!\n";
            return;
        }

        students.clear();

        int id;
        string name, course;
        float marks;
        char comma;

        while (file >> id >> comma) {
            getline(file, name, ',');
            getline(file, course, ',');
            file >> marks;

            students.emplace_back(id, name, course, marks);
        }

        file.close();
        cout << "Student Records Loaded Successfully!\n";
    }
};

int main() {
    StudentPortal portal;

    int choice, id;
    string name, course;
    float marks;

    cout << "================================\n";
    cout << "       STUDENT PORTAL\n";
    cout << "================================\n";
    cout << "Student Name: Vaibhav\n";

    do {
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Save Records";
        cout << "\n5. Load Records";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Student ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> ws;
            getline(cin, name);

            cout << "Enter Course: ";
            getline(cin, course);

            cout << "Enter Marks: ";
            cin >> marks;

            portal.addStudent(id, name, course, marks);
            break;

        case 2:
            portal.displayStudents();
            break;

        case 3:
            cout << "Enter Student ID to Search: ";
            cin >> id;
            portal.searchStudent(id);
            break;

        case 4:
            portal.saveData();
            break;

        case 5:
            portal.loadData();
            break;

        case 6:
            cout << "Thank You, Vaibhav!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}