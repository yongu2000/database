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
/  FILE:        user_interface.cpp
/
/  DESCRIPTION:
/   This file contains the user-interface functions
/   for Project 2
*********************************************/

#include <string.h>
#include <iostream>
#include <iomanip>
#include "llist.h"

using namespace std;


void menu_option();
void menu_input();
void getaddress (char [], int);

/********************************************
/
/  Function name: menu_option
/
/  DESCRIPTION: Prints the available menu for the user
/
/  Parameters:  none
/
/  Return values: none
/
*********************************************/
void menu_option()
{
    #if debugmode == 1
        cout << "This is debug mode menu_option\n" << endl;
    #endif    
    cout << "<Choose a menu option>\n";
    cout << "-------------------------------------\n";
    cout << "<add> : <Add a new record in the database>\n";
    cout << "<printall> : <Print all records in the database>\n";
    cout << "<find> : <Find record(s) with a specified account #>\n";
    cout << "<delete> : <Delete existing record(s) from the database using the account # as a key>\n";
    cout << "<quit> : <Quit the program>\n";
    cout << "-------------------------------------\n";
}

/********************************************
/
/  Function name: getaddress
/
/  DESCRIPTION:   User Input for residential address
/
/  Parameters:    address[] (char) : residential address of the user input
/                 size (int) : maximum size of the input
/
/  Return values: none
/
*********************************************/
void getaddress (char address[], int size)
{

    #if debugmode == 1
        cout << "This is debug mode getaddress\n";
    #endif 

    cout << "Please Enter Address and Enter '#' When End\n";
    cin.getline(address, 64, '#');
    cin.ignore();  
}


/******************************************************************
/  Function name: main
/ 
/  DESCRIPTION:   A main function
/                 generates a user interface of account
/
/  Parameters:    argc (int) : the number of command line arguments
/                 *argv[] (char) : the individual arguments on the command line
/  
/  Return values:  0: success
/
****************************************************************/

int main (int argc, char* argv[])
{
    int runs = 1;
    int state;


    #if debugmode == 1
        cout << "This is debug mode\n";
    #endif                                                                      
    if (runs == 1)
    {
        cout << "<User-Interface>\n";
        llist *data = new llist();        
        state = 0;
        while(state == 0)
        {
            char input[64];
            menu_option();
            cout << "type the corresponding option and hit the enter\n";
            cin >> input;
            cin.ignore();
            if (strcmp(input, "add") == 0 || strcmp(input, "ad") == 0 || strcmp(input, "a") == 0)
            {
                int i;
                int accountNo;
                
                char name[64];
                char address[80];
                i = 0;
                while (i < 80)
                {
                    address[i] = '\0';
                    i++;
                }
                #if debugmode == 1
                    cout << "Add Selected\n";
                
                #endif

                cout << "Type your account number\n";
                cin >> accountNo;
                cin.ignore();

                while (accountNo < 0)
                {
                    cout << "Please enter a positive integer";
                    cin >> accountNo;  
                    cin.ignore();   
                }
                

                cout << "Type your name\n";
                cin.get(name, 64);
                cin.ignore();  
                cout << "Type your address\n";
                getaddress(address, 80);

                #if debugmode == 1
                {
                    cout << "Account number is " << accountNo << endl;
                    cout << "Name is" << name << endl;
                    cout << "Address is " << address << endl;
                }
                #endif

                if (data->llist::addRecord(accountNo, name, address) == 0)
                {
                    cout << "The new record is added" << endl;
                }
  
            }
            else if (strcmp(input, "printall") == 0 || strcmp(input, "printal") == 0 || 
            strcmp(input, "printa") == 0 || strcmp(input, "print") == 0 || strcmp(input, "prin") == 0 || 
            strcmp(input, "pri") == 0 || strcmp(input, "pr") == 0 || strcmp(input, "p") == 0)
            {
                #if debugmode == 1
                    cout << "Printall Selected\n";
                #endif                
		data->printAllRecords();

                
            }
            else if (strcmp(input, "find") == 0 || strcmp(input, "fin") == 0 || strcmp(input, "fi") == 0 || strcmp(input, "f") == 0)
            {
                int accountNo;
                
                
                #if debugmode == 1
                    cout << "Find Selected\n";
                #endif   
                
                cout << "Type your account number\n";
                cin >> accountNo;
                cin.ignore();  
                while (accountNo < 0 )
                {
                    cout << "Please enter a positive integer\n";
                    cin >> accountNo;
                    cin.ignore();  
                }
                

                if (data->llist::findRecord(accountNo) == -1)
                {
                    cout << "there is no record of the corresponding address to be found\n";
                }
               
            }
            else if (strcmp(input, "delete") == 0 || strcmp(input, "delet") == 0 || strcmp(input, "dele") == 0 || strcmp(input, "del") == 0 
            || strcmp(input, "de") == 0 || strcmp(input, "d") == 0)
            {
                int accountNo;
                
                
                #if debugmode == 1
                    cout << "Delete Selected\n";
                #endif   

                cout << "Type your account number\n";
                cin >> accountNo;
                cin.ignore();  
                
                while (accountNo < 0)
                {
                    cout << "Please enter a positive integer\n";
                    cin >> accountNo;
                    cin.ignore();  
                }
                if (data->llist::deleteRecord(accountNo) == -1)
                {
                    cout << "there is no record of the corresponding address to be deleted\n";
                }
                else
                {
                    cout << "record for following address has been deleted\n";
                }
            }

            else if (strcmp(input, "quit") == 0 || strcmp(input, "qui") == 0 || strcmp(input, "qu") == 0 || strcmp(input, "q") == 0)
            {
                
                #if debugmode == 1
                    cout << "Quit Selected\n";
                #endif   
                state = 1;
                data->printAllRecords();
                delete data;
                cout << "have been saved into save.txt\n";
          
            }
            else
            {
                cout << "Invaild Input\n";
            }
        }
    }  
    return 0;
}

