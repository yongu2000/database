/********************************************
/
/  NAME:        Yong U Cho
/
/  HOMEWORK:    project2
/
/  CLASS:       ICS 212
/
/  INSTRUCTOR:  Ravi Narayan
/
/  DATE:        Nov 27, 2020
/
/  FILE:        llist.h
/
/  DESCRIPTION:
/   This file is the header file for the database
/   functions
*********************************************/
#include <iostream>
using namespace std;

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();    
    llist(char[]);
    ~llist();
    llist(const llist &obj);
    ostream& operator=(const llist& l);
    int addRecord(int, char [ ],char [ ]);
    int findRecord(int);
    void printAllRecords();
    // replace printAllRecords() with the << operator
    int deleteRecord(int);
    friend ostream& operator<<(ostream&, const llist&);
};