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
/  FILE:        llist.cpp
/
/  DESCRIPTION:
/   This file contains the database functions
/   for project2
*********************************************/
#include "llist.h"
#include <cstring>
#include <fstream>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;



/********************************************
/
/  Function name: llist
/
/  DESCRIPTION:   constructor for llist
/
/  Parameters:    none
/
/  Return values: none
/
*********************************************/
llist::llist()
{
    struct record *data = start;
    readfile();

}

/********************************************
/
/  Function name: llist
/
/  DESCRIPTION:   copy-constructor for llist
/
/  Parameters:    obj (const llist &) : llist object
/
/  Return values: none
/
*********************************************/
llist::llist(const llist &obj) 
{
   *start = *obj.start;
   *filename = *obj.filename;
}

/********************************************
/
/  Function name: llist
/
/  DESCRIPTION:   constructor for llist with filename
/
/  Parameters:    file (char []) : filename of saved data
/
/  Return values: none
/
*********************************************/
llist::llist(char file[])
{
    *filename = *file;
}

/********************************************
/
/  Function name: ~llist
/
/  DESCRIPTION:   destructor for llist
/
/  Parameters:    none
/
/  Return values: none
/
*********************************************/
llist::~llist()
{
    writefile();
    cleanup();
    delete start;
}

/********************************************
/
/  Function name: operator<<
/
/  DESCRIPTION:   overloading operator << for llist
/
/  Parameters:    os (ostream&) : operator overloading stream
/                 l (const llist&) : llist
/
/  Return values: os : return overloaded operator
/
*********************************************/
ostream& operator<<(ostream& os, const llist& l)
{
    
    struct record *temp = l.start;

    if (temp == NULL)
    {
        cout << "The record is empty";
    }
    while (temp != NULL)
    {
        os << "Account No: " << temp->accountno << '/n'  << "Name: "<< temp->name << '/n'  << "Address: "<< temp->address;
        
        temp = temp->next;
        
    }
    return os;
}

/********************************************
/
/  Function name: operator=
/
/  DESCRIPTION:   overloading operator = for llist
/
/  Parameters:    l (const llist&) : llist
/
/  Return values: *this : pointer of the current llist
/
*********************************************/
llist llist::operator=(const llist& l)
{
    if (this != &l)
    {
        start = l.start;
        *filename = *l.filename;
    }
    
    return *this;
}



/********************************************
/
/  Function name: addRecord
/
/  DESCRIPTION:   Add a new record in the database
/
/  Parameters:    account (int) : account of the input
/                 name[] (char) : name of the input
/                 address[] (char) : address of the input
/
/  Return values: 0 a record has been added
/                -1 record failed to be added
/
*********************************************/
int llist::addRecord(int account, char name[] ,char address[])
{
    
    int state = 0;
    int last = 0;
    struct record *newNode = new record();
    struct record *temp = start;
    

    int returnVal = -1;
    #if debugmode == 1
        printf("This is debugmode add function\n");
    #endif
             
    newNode->accountno = account;          
    strcpy(newNode->name, name);
    strcpy(newNode->address, address);
 
    if(temp == NULL)
    {
        temp = newNode;
        start = temp;
        returnVal = 0;        
    }
    else
    {
        if(temp->accountno < newNode->accountno)
        {
            newNode->next = temp;
            start = newNode;
            returnVal = 0;        
        }
        else
        {
            while(temp->next != NULL && state == 0)
            {
                if(temp->next->accountno < newNode->accountno)
                {
                    newNode->next = temp->next;
                    temp->next = newNode;
                    returnVal = 0;
                    last++;
                    state++;
                }
                temp = temp->next;
            }
            if (last == 0)
            {
                temp->next = newNode;
            }

        }  
    }
    return returnVal;

}


void llist::printAllRecords()
{
    struct record *temp = start;
    
    if (start == NULL)
    {
        cout << "The record is empty\n";
    }
    while (temp != NULL)
    {
        cout << "\nAccount #: " << temp->accountno << "\nName: " << temp->name << "\nAddress: " << temp->address << endl;
        temp = temp->next;
    }
    
}


int llist::findRecord(int account)
{
   
    struct record *temp = start;
    struct record *findNode;
    int returnVal = -1;
    
    #if debugmode == 1
        printf("This is debugmode find function\n");
    #endif
    if (start != NULL)
    {
        while(temp != NULL)
        {
            if (temp->accountno == account)
            {             
               cout << "Account #: "<< temp->accountno << "\n" << "Name: " << temp->name << "\n" << "Address: " << temp->address << endl; 
                returnVal = 0;
            }
            else
            {
                while (temp->next != NULL)
                {
                    if ((temp->next->accountno) == account)
                    {
                        findNode = temp->next;
                        cout << "Account #: " << findNode->accountno << "\n" << "Name: " << findNode->name << "\n" << "Address: " << findNode->address << endl;
                        temp = temp->next;
                        returnVal = 0;

                    }
                    else
                    {
                        temp = temp->next;
                    }        
                }
            }
            temp = temp->next;
        }       
    }
    return returnVal;
}

int llist::deleteRecord(int account)
{
    struct record *temp = start;
    struct record *deletedNode;
    int returnVal = -1;
    #if debugmode == 1
        printf("This is debugmode delete function\n");
    #endif 
    if (temp != NULL && temp->next == NULL && temp->accountno == account)
    {
        delete temp;
        start = NULL;
    }
    if (start != NULL)
    {
        while (temp->next != NULL)
        {
            if (start->accountno == account)
            {
                start = temp->next;
                delete temp;
                temp = start;
                if(temp->next == NULL)
                {
                    if(start->accountno == account)
                    {
                        delete temp;
                        start = NULL;
                    }
                }
                returnVal = 0;               
            }
            else
            {
                while (temp->next != NULL)
                {
                    if ((temp->next->accountno) == account)
                    {
                        deletedNode = temp->next;
                        temp->next = temp->next->next;
                        delete deletedNode;
                        returnVal = 0;
                    }
                    else
                    {
                        temp = temp->next;
                    }                   
                }
            }
             
        }

    }
    return returnVal;
   
}

int llist::readfile()
{
    ifstream inFile;
    inFile.open("save.txt");
    int i = 0;
    int j = 0;
    int count = 0;
    char temptemp[100];
    int accounttemp;
    char nametemp[20];
    char addresstemp[80];
    #if debugmode == 1
        printf("This is debugmode readfile function\n");
    #endif

    if (inFile.is_open())
    {
        while (inFile.peek() != EOF)
        {
            for (j = 0; j < 3; j++)
            {
                
                count ++;
                if (count % 3 == 1)
                {
                    inFile >> accounttemp;
                }
                else if (count % 3 == 2)
                {
                    inFile.getline(temptemp, 100);
                    strcpy(nametemp, temptemp);
                }
                else
                {
                    inFile.getline(temptemp, 100);
                    strcpy(addresstemp, temptemp);
                }
            }
            addRecord(accounttemp, nametemp, addresstemp);
            temptemp[0] = '\0';
            nametemp[0] = '\0';
            addresstemp[0] = '\0';
            i++;                
        }    
        inFile.close();
        i = -1;
    }
    else
    {
        i = -1;
    }
    return i;
}
int llist::writefile()
{
    ofstream writeFile;
    writeFile.open("save.txt");

    struct record *temp = start;
    int i = 0;
    int accounttemp;
    char nametemp[64];
    char addresstemp[80];
    
    #if debugmode == 1
        printf("This is debugmode writefile function\n");
    #endif  
    if(writeFile.is_open())
    {
    while (temp != NULL)
    {  
        accounttemp = temp->accountno; 
        strcpy(nametemp, temp->name);
        strcpy(addresstemp, temp->address);
        
        writeFile.write(accounttemp
        fprintf(outfile, "%d\n", accounttemp);
        fprintf(outfile, "%s\n", nametemp);
        fprintf(outfile, "%s\n", addresstemp);
            
        i++;
        temp = temp->next; 
    } 
    fclose(outfile);
    return i;
}*/

void llist::cleanup()
{
    struct record *temp = start;
    #if debugmode == 1
        printf("This is debugmode cleanup function\n");
    #endif
    
    while (temp != NULL)
    {
        start = temp->next;
        delete temp;
        temp = start;
    }
    start = NULL;
}
