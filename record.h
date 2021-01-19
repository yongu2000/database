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
/  FILE:        record.h
/
/  DESCRIPTION:
/   This file is the header file for recording
/   the information
*********************************************/

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};
