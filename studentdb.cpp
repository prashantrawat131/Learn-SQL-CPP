#include <sqlite3.h>
#include <iostream>
#include <unistd.h>
#include "./studentdb.h"

using namespace std;

StudentDB::StudentDB()
{
    char *zErrMsg = 0;
    int rc;

    // Opening the SQLite Database
    rc = sqlite3_open("./prashant.db", &db);
    if (rc != SQLITE_OK)
    {
        cout << "Error while opening database\n";
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
}

StudentDB::~StudentDB()
{
    cout << "Closing Database\n";
    sqlite3_close(db);
}

int StudentDB::getStudentCount()
{
    string sql("Select count(*) from student;");
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v3(db, sql.c_str(), -1, 0, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cerr << "Error while preparing statement: " << rc << endl;
        return 0;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        cerr << "Error while stepping statement: " << rc << endl;
        return 0;
    }
    // Simply get the value of the zeroth column.
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void StudentDB::insertStudentData(int rno, const char *name, const char *phoneNumber)
{
    int exist = studentExists(rno);
    if (exist)
    {
        cerr << "Roll number already present\n";
        sleep(2);
        return;
    }
    const char *sql = "INSERT INTO STUDENT(rno,name,phone) VALUES(?,?,?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cout << "Error while preparing insert statement" << rc << endl;
        sleep(2);
        return;
    }
    else
    {
        sqlite3_bind_int(stmt, 1, rno);
        sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, phoneNumber, -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            cout << "Error occurred while executing insert statement: " << rc << endl;
            sleep(2);
            return;
        }
        else
        {
            cout << "Record inserted successfully\n";
            sleep(2);
        }
    }

    // sqlite3_finalize(stmt);
}

bool StudentDB::studentExists(int rno)
{
    const char *sql = "select count(*) from student where rno = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cerr << "Error while preparing statement for deleting record\n";
        return false;
    }
    sqlite3_bind_int(stmt, 1, rno);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        cerr << "Error while stepping record\n";
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count >= 1;
}

void StudentDB::deleteStudentData(int rno)
{
    int count = getStudentCount();
    if (count == 0)
    {
        cerr << "No records to delete\n";
        sleep(2);
        return;
    }

    int studentExist = studentExists(rno);
    if (!studentExist)
    {
        cerr << "Record doesn't exit\n";
        sleep(2);
        return;
    }

    const char *sql = "Delete from student where rno = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        cerr << "Error while preparing statement for deleting record\n";
        sleep(2);
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
            sleep(2);
        }
    }
}

int StudentDB::printStudentsData(void *data, int cellCount, char **cellValues, char **azColName)
{
    for (int i = 0; i < cellCount; i++)
    {
        char *cellData = cellValues[i];
        cout << cellData << "\t";
        if (i % 3 == 2 && i != 2)
        {
            cout << "\n";
        }
    }
    cout << "\n";
    return 0;
}

void StudentDB::showStudentsData()
{
    int count = getStudentCount();
    if (count == 0)
    {
        cout << "No rows are currently available\n";
        sleep(2);
        return;
    }
    string sql("Select * from student;");
    cout << "Following are the student details:\n";
    cout << "------------------------------------------\n";
    int rc = sqlite3_exec(db, sql.c_str(), printStudentsData, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "Error while reading data:" << rc << endl;
    }
    cout << "------------------------------------------\n";
    sleep(2);
}
