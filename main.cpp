#include <iostream>
#include <sqlite3.h>
#include <unistd.h>
#include <string.h>

using namespace std;

/* class Student
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
}; */

void insertStudentData(sqlite3 *db)
{
    int rno;
    string name, phoneNumber;

    cout << "Enter roll number of the student:";
    cin >> rno;

    cin.get();

    cout << "Enter name of the student:";
    getline(cin, name);

    cout << "Enter phoneNumber of the student:";
    getline(cin, phoneNumber);

    const char *sql = "INSERT INTO STUDENT(rno,name,phone) VALUES(?,?,?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cout << "Error while preparing insert statement" << rc << endl;
        return;
    }
    else
    {
        sqlite3_bind_int(stmt, 1, rno);
        sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, phoneNumber.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            cout << "Error occurred while executing insert statement: " << rc << endl;
            return;
        }
        else
        {
            cout << "Record inserted successfully\n";
        }
    }

    // sqlite3_finalize(stmt);
}

void deleteStudentData(sqlite3 *db)
{
    int rno;
    cout << "Enter the roll number of student to delete:";
    cin >> rno;

    const char *sql = "Delete from student where rno = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cerr << "Erorr while preparing statement for deleting record\n";
    }
    else
    {
        sqlite3_bind_int(stmt, 1, rno);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            cerr << "Error occurred while deleting record:" << rc << endl;
        }
        else
        {
            cout << "Record deleted successfully\n";
        }
    }
}

static int printStudentsData(void *data, int argc, char **argv, char **azColName)
{
    cout << (const char *)data << endl;
    for (int i = 0; i < argc; i++)
    {
        cout << azColName[i] << " " << argv[i] << endl;
    }
    return 0;
}

void showStudentsData(sqlite3 *db)
{
    string sql("Select * from student;");
    string data = "Following is the students data:";
    int rc = sqlite3_exec(db, sql.c_str(), printStudentsData, (void *)data.c_str(), NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "Error while reading data:" << rc << endl;
    }
    else
    {
        cout << "Rno\tName\tPhone" << endl;
    }
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
                            "phone TEXT"
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