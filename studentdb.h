#ifndef STUDENTDB_H
#define STUDENTDB_H

#include <sqlite3.h>

class StudentDB
{
private:
    sqlite3 *db;
    static int printStudentsData(void *, int, char **, char **);

public:
    StudentDB();
    ~StudentDB();

    int getStudentCount();
    bool studentExists(int rno);
    void insertStudentData(int, const char *, const char *);
    void deleteStudentData(int);
    void showStudentsData();
};

#endif