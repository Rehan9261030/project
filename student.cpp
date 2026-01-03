#include <iostream>
#include <vector>

using namespace std;

struct Book
{
    int id;
    string name;
    bool issued;
};

struct grade
{
    int id;
    string name;
    bool present;
    float marks;
    char grade;
};
struct Student
{
    int id;
    string name;
    int age;
    double cnic;
};

vector<Book> books;
vector<grade> grading;
vector<Student> admission;

void addStudent()
{
    Student s;
    cout << "Enter ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    cout<<"Enter your CNIC:";
    cin>> s.cnic;
    admission.push_back(s);
    cout << "Student added successfully.\n";
}

void displayStudents()
{
    if (admission.empty())
    {
        cout << "No records found.\n";
        return;
    }
    for (int i = 0; i < admission.size(); i++)
    {
        cout << "ID: " << admission[i].id << endl;
        cout << "Name: " << admission[i].name << endl;
        cout << "Age: " << admission[i].age << endl;
        cout << "CNIC: " << admission[i].cnic << endl;
    }
}

void searchStudent()
{
    int id;
    cout << "Enter ID to search: ";
    cin >> id;
    for (int i = 0; i < admission.size(); i++)
    {
        if (admission[i].id == id)
        {
            cout << "Student Found!\n";
            cout << "Name: " << admission[i].name << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

void dismissStudent()
{
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    for (int i = 0; i < admission.size(); i++)
    {
        if (admission[i].id == id)
        {
            admission.erase(admission.begin() + i);
            cout << "Record deleted successfully.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void addBook()
{
    Book b;
    cout << "Enter Book ID: ";
    cin >> b.id;
    cout << "Enter Book Name: ";
    cin >> b.name;
    b.issued = false;
    books.push_back(b);
    cout << "Book added successfully:\n";
}

void displayBooks()
{
    if (books.empty())
    {
        cout << "No books available.\n";
         cout << "First add book.\n";
        return;
    }
    for (Book b : books)
    {
        cout << "ID: " << b.id<<endl;
        cout << "Name: " << b.name<<endl;
        cout<< "Status: ";
        if(b.issued)
        cout << "Issued";
       else
        cout << "Available";
        cout << endl;
    }
}

void issueBook()
{
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;
    for (Book &b : books)
    {
        if (b.id == id && !b.issued)
        {
            b.issued = true;
            cout << "Book issued successfully.\n";
            return;
        }
    }
    cout << "Book not found or already issued.\n";
}

void addStudents()
{
    grade s;
    cout << "Enter Student ID: ";
    cin >> s.id;
    cout << "Enter Student Name: ";
    cin >> s.name;
    s.present = false;
    s.marks = 0;
    s.grade = '-';
    grading.push_back(s);
    cout << "Student added successfully.\n";
}

void markAttendance()
{
    int id;
    cout << "Enter Student ID to mark present: ";
    cin >> id;
    for (grade &s : grading)
    {
        if (s.id == id)
        {
            s.present = true;
            cout << "Attendance marked.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void displayAttendance()
{
    if (grading.empty())
    {
        cout << "No students available.\n";
        return;
    }
    for (auto s : grading)
    {
        cout << "ID: " << s.id<<endl;
        cout << "Name: " << s.name<<endl;
        cout << "Attendance: "<<endl;
        if (s.present)
        {
            cout<<"Present";
        }
        else
        {
            cout<<"Absent";
        }
        cout<<endl;
        
    }
}

char calculateGrade(float m)
{
    if (m >= 80)
    {
        return 'A';
    }
    else if (m >= 70)
    {
        return 'B';
    }
    else if (m >= 60)
    {
        return 'C';
    }
    else if (m >= 50)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

void addMarks()
{
    int id;
    float m;
    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Marks: ";
    cin >> m;
    for (grade &s : grading)
    {
        if (s.id == id)
        {
            s.marks = m;
            s.grade = calculateGrade(m);
            cout << "Marks and grade added.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void displayGrades()
{
    if (grading.empty())
    {
        cout << "No student records available.\n";
        return;
    }
    for (grade s : grading)
    {
        cout << "ID: " << s.id <<endl;
        cout << "Name: " << s.name<<endl;
        cout << "Marks: " << s.marks<<endl;
        cout << "Grade: " << s.grade << endl;
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n********** MAIN MENU **********\n";
        cout << "1. Student Management\n";
        cout << "2. Library Management\n";
        cout << "3. Attendance Management\n";
        cout << "4. Grading System\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int c;
            do
            {
                      
                cout << "\n--- Student Management ---\n";
                cout << "1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Back\n";
                cout<<"Enter your choice:";
                cin >> c;

                if (c == 1) addStudent();
                else if (c == 2) displayStudents();
                else if (c == 3) searchStudent();
                else if (c == 4) dismissStudent();
                else if (c != 5) cout << "Invalid option.\n";

            } while (c != 5);
            break;
        }

        case 2:
        {
            int c;
            do
            {
                cout << "\n--- Library Menu ---\n";
                cout << "1. Add Book\n  2. Display Books\n 3. Issue Book\n 4. Back\n";
                cout<<"Enter your choice:";
                cin >> c;

                if (c == 1) addBook();
                else if (c == 2) displayBooks();
                else if (c == 3) issueBook();
                else if (c != 4) cout << "Invalid option.\n";

            } while (c != 4);
            break;
        }

        case 3:
        {
            int c;
            do
            {
                cout << "\n--- Attendance Menu ---\n";
                cout << "1. Add Student\n2. Mark Attendance\n3. View Attendance\n4. Back\n";
                cin >> c;

                if (c == 1) addStudents();
                else if (c == 2) markAttendance();
                else if (c == 3) displayAttendance();
                else if (c != 4) cout << "Invalid option.\n";

            } while (c != 4);
            break;
        }

        case 4:
        {
            int c;
            do
            {
                cout << "\n--- Grading Menu ---\n";
                cout << "1. Add Marks\n2. View Grades\n3. Back\n";
                cin >> c;

                if (c == 1) addMarks();
                else if (c == 2) displayGrades();
                else if (c != 3) cout << "Invalid option.\n";

            } while (c != 3);
            break;
        }

        case 5:
            cout << "Program exited successfully.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
