#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// STRUCTURES

struct Book {
    int id;
    string name;
    int quantity; // it will check the books
};

struct grade {
    int id;
    string name;
    bool present;
    float marks;
    char gradeChar;
};

struct Student {
    int id;
    string name;
    int age;
    string cnic;
};

// Gbl Vectors
vector<Book> books;
vector<grade> grading;
vector<Student> admission;

// FILE HANDLING

void saveAllData() {
    // Save Students
    ofstream sFile("students.txt");
    for (const auto& s : admission) {
        sFile << s.id << "," << s.name << "," << s.age << "," << s.cnic << endl;
    }
    sFile.close();

    // Save Books (Using Quantity)
    ofstream bFile("books.txt");
    for (const auto& b : books) {
        bFile << b.id << "," << b.name << "," << b.quantity << endl;
    }
    bFile.close();

    // Save Grading
    ofstream gFile("grading.txt");
    for (const auto& g : grading) {
        gFile << g.id << "," << g.name << "," << g.present << "," << g.marks << "," << g.gradeChar << endl;
    }
    gFile.close();
}

void loadAllData() {
    string line, temp;
    admission.clear();
    books.clear();
    grading.clear();

    // Load Students
    ifstream sFile("students.txt");
    while (getline(sFile, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, temp, ','); s.id = stoi(temp);
        getline(ss, s.name, ',');
        getline(ss, temp, ','); s.age = stoi(temp);
        getline(ss, temp, ','); s.cnic = stod(temp);
        admission.push_back(s);
    }
    sFile.close();

    // Load Books
    ifstream bFile("books.txt");
    while (getline(bFile, line)) {
        stringstream ss(line);
        Book b;
        if(getline(ss, temp, ',')) {
            b.id = stoi(temp);
            getline(ss, b.name, ',');
            getline(ss, temp, ','); b.quantity = stoi(temp);
            books.push_back(b);
        }
    }
    bFile.close();

    // Load Grading
    ifstream gFile("grading.txt");
    while (getline(gFile, line)) {
        stringstream ss(line);
        grade g;
        getline(ss, temp, ','); g.id = stoi(temp);
        getline(ss, g.name, ',');
        getline(ss, temp, ','); g.present = (temp == "1");
        getline(ss, temp, ','); g.marks = stof(temp);
        getline(ss, temp, ','); g.gradeChar = temp[0];
        grading.push_back(g);
    }
    gFile.close();
}

//  FUNCTIONS 

void addStudent() {
    Student s;
    cout << "Enter ID: "; 
    cin >> s.id;
    cin.ignore();
    cout << "Enter Name: ";
     getline(cin, s.name);
    cout << "Enter Age: ";
     cin >> s.age;
    cout << "Enter CNIC (xxxxx-xxxxxxx-x): ";
     cin >> s.cnic;
    admission.push_back(s);
    saveAllData();
    cout << "Student saved.\n";
}

void dismissStudent() {
    int id;
    cout << "Enter ID to delete: "; cin >> id;
    for (int i = 0; i < admission.size(); i++) {
        if (admission[i].id == id) {
            admission.erase(admission.begin() + i);
            saveAllData();
            cout << "Record deleted.\n";
            return;
        }
    }
    cout << "Not found.\n";
}

void addBook() {
    int id;
    cout << "Enter Book ID: "; cin >> id;

    for (Book &b : books) {
        if (b.id == id) {
            int q;
            cout << "Book exists. Add how many more copies? "; cin >> q;
            b.quantity += q;
            saveAllData();
            cout << "Stock updated.\n";
            return;
        }
    }
     cout << "Book not found. Add as new book.\n";
    Book b;
    b.id = id;
    cin.ignore();
    cout << "Enter Book Name: "; getline(cin, b.name);
    cout << "Enter Initial Quantity: "; cin >> b.quantity;
    books.push_back(b);
    saveAllData();
    cout << "New book added.\n";
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: "; cin >> id;
    for (Book &b : books) {
        if (b.id == id) {
            if (b.quantity > 0) {
                b.quantity--;
                saveAllData();
                cout << "Book issued. Remaining stock: " << b.quantity << endl;
            } else {
                cout << "Error: Out of stock!\n";
            }
            return;
        }
    }
    cout << "Book ID not found.\n";
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: "; cin >> id;
    for (Book &b : books) {
        if (b.id == id) {
            b.quantity++;
            saveAllData();
            cout << "Book returned. New stock: " << b.quantity << endl;
            return;
        }
    }
    cout << "Book ID not found in library records.\n";
}

char calculateGrade(float m) {
    if (m >= 80) return 'A';
    else if (m >= 70) return 'B';
    else if (m >= 60) return 'C';
    else if (m >= 50) return 'D';
    else return 'F';
}


void addStudentsGrading() {
    grade s;
    cout << "Enter Student ID: "; cin >> s.id;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, s.name);
    s.present = false; s.marks = 0; s.gradeChar = '-';
    grading.push_back(s);
    saveAllData();
    cout << "Student enrolled in grading.\n";
}

void removeGradeRecord() {
    int id;
    cout << "Enter Student ID to remove from Grading: "; cin >> id;
    for (int i = 0; i < grading.size(); i++) {
        if (grading[i].id == id) {
            grading.erase(grading.begin() + i);
            saveAllData(); // Update file after deletion
            cout << "Grading record removed.\n";
            return;
        }
    }
    cout << "Student ID not found in grading system.\n";
}

void markAttendance() {
    int id;
    cout << "Enter Student ID: "; cin >> id;
    for (grade &s : grading) {
        if (s.id == id) {
            s.present = true;
            saveAllData();
            cout << "Attendance marked.\n";
            return;
        }
    }
}

void addMarks() {
    int id; float m;
    cout << "Enter ID: "; cin >> id;
    cout << "Enter Marks: "; cin >> m;
    for (grade &s : grading) {
        if (s.id == id) {
            s.marks = m;
            s.gradeChar = calculateGrade(m);
            saveAllData();
            cout << "Marks and Grade updated.\n";
            return;
        }
    }
}

//  MAIN MENU

int main() {
    loadAllData();
    int choice;

    do {
        cout << "\n********** MAIN SYSTEM MENU **********\n";
        cout << "1. Student Management\n";
        cout << "2. Library Management\n";
        cout << "3. Attendance/Grading\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
         cin >> choice;

        switch (choice) {
            case 1: {
                int c;
                cout << "\n--- Student Management ---\n";
                cout << "1. Add Student\n2. Delete Student\n3. View All\n4. Back\n";
                cout << "Enter Choice: ";
                cin >> c;
                if (c == 1) addStudent();
                else if (c == 2) dismissStudent();
                else if (c == 3) {
                    for(auto s : admission) cout << s.id << " | " << s.name << " | Age: " << s.age << endl;
                }
                break;
            }
            case 2: {
                int c;
                cout << "\n--- Library Management ---\n";
                cout << "1. Add or Restock Book\n2. Issue Book\n3. Return Book\n4. View Stock\n5. Back\n";
                cout << "Enter Choice: ";
                cin >> c;
                if (c == 1) addBook();
                else if (c == 2) issueBook();
                else if (c == 3) returnBook();
                else if (c == 4) {
                    cout << "ID | Name | Quantity Available\n";
                    for(auto b : books) cout << b.id << " | " << b.name << " | " << b.quantity << endl;
                }
                break;
            }
            case 3: {
                int c;
                cout << "\n--- Grading Management ---\n";
                cout << "1. Enroll for Grades\n2. Mark Attendance\n3. Add Marks\n4. Delete Grade\n5. Back\n";
                cout << "Enter Choice: ";
                cin >> c;
                if (c == 1) addStudentsGrading();
                else if (c == 2) markAttendance();
                else if (c == 3) addMarks();
                else if (c == 4) removeGradeRecord(); 
                break;
            }
        }
    } while (choice != 4);

    return 0;
}


