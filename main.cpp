#include <iostream>
#include <sqlite3.h>
#include <unistd.h>
#include <string>
#include "./studentdb.h"

using namespace std;

int main()
{
    StudentDB sdb = StudentDB();
    int choice;
    int rno;
    char name[100], phoneNumber[20];
    while (choice != 1)
    {
        cout << "Menu:\n";
        cout << "1. Exit\n";
        cout << "2. Insert\n";
        cout << "3. Delete\n";
        cout << "4. Show Student Data\n";
        cout << "Enter choice: \n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            break;

        case 2:
            cout << "Enter roll number of the student:";
            cin >> rno;

            cin.get();
            cout << "Enter name of the student:";
            cin.getline(name, 100);

            cout << "Enter phoneNumber of the student:";
            cin.getline(phoneNumber, 20);

            sdb.insertStudentData(rno, name, phoneNumber);
            break;

        case 3:
            cout << "Enter the roll number of student to delete:";
            cin >> rno;

            sdb.deleteStudentData(rno);
            break;

        case 4:
            sdb.showStudentsData();
            break;

        default:
            cout << "Please enter a valid choice...\n";
            sleep(2);
            break;
        }
    }

    return 0;
}