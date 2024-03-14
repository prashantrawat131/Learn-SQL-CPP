#include <iostream>
#include <sqlite3.h>
#include <unistd.h>
#include <string>

using namespace std;

class Student
{
private:
    int rno;
    string name;
    string phoneNumber;

public:
    Student(int rno, string name, string phoneNumber)
    {
        this->rno = rno;
        this->name = name;
        this->phoneNumber = phoneNumber;
    }

    // Getters
    int getRno()
    {
        return rno;
    }

    string getName()
    {
        return name;
    }

    string getPhoneNumber()
    {
        return phoneNumber;
    }

    // Setters
    void setRno(int rno)
    {
        this->rno = rno;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setPhoneNumber(string phoneNumber)
    {
        this->phoneNumber = phoneNumber;
    }
};

class MyString
{
private:
    string s;

public:
    MyString(string s)
    {
        this->s = s;
    }

    void setString(string s)
    {
        this->s = s;
    }

    string getString() const
    {
        return s;
    }

    string getSqlString()
    {
        return s.c_str();
    }

    MyString operator+(const MyString &s2)
    {
        string newStr = s + s2.getString();
        return MyString(newStr);
    }

    MyString operator+(const int i)
    {
        string newStr = s + to_string(i);
        return MyString(newStr);
    }

    MyString operator=(const MyString &s2)
    {
        setString(s2.getString());
    }
};

void insertStudentData(sqlite3 *db)
{
    int rno;
    string name, phoneNumber;

    cout << "Enter roll number of the student:";
    cin >> rno;

    cout << "Enter name of the student:";
    cin >> name;

    cout << "Enter phoneNumber of the student:";
    cin >> phoneNumber;

    MyString str("");
    str = "INSERT INTO STUDENT VALUES(" + to_string(rno) + "," + name + "," + phoneNumber + ");";
    cout << str.getString() << endl;

    char *errMsg;
    int rc = sqlite3_exec(db, str.getSqlString(), NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        cout << "Unable to insert data. Error code: " << rc << endl;
    }
    else
    {
        cout << "Data inserted successfully\n";
    }
}

void deleteStudentData(sqlite3 *db)
{
}

void showStudentsData(sqlite3 *db)
{
}

int main()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Opening the SQLite Database
    rc = sqlite3_open("./prashant.db", &db);
    if (rc != SQLITE_OK)
    {
        cout << "Error while opening database\n";
        return -1;
    }
    else
    {
        cout << "Database opened successfully\n";
    }

    // Creating a table
    string createTableStr = "Create Table if not exists Student("
                            "rno INT PRIMARY KEY NOT NULL,"
                            "name TEXT,"
                            "phone REAL"
                            ");";
    cout << createTableStr << endl;
    rc = sqlite3_exec(db, createTableStr.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        cout << "Error occurred while creating table:" << rc << "\n";
    }
    else
    {
        cout << "Table created successfully\n";
    }

    int choice;
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
            insertStudentData(db);
            break;

        case 3:
            deleteStudentData(db);
            break;

        case 4:
            showStudentsData(db);
            break;

        default:
            cout << "Please enter a valid choice...\n";
            sleep(2);
            break;
        }
    }

    sqlite3_close(db);

    return 0;
}