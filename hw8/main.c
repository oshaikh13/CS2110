/**
 * @file main.c
 * @author YOUR NAME HERE
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "21tenmo.h"
#include "errcodes.h"

// Initializing the global err number variable to default
unsigned int myErrNo = NO_ERROR;

/**
 * @brief helper function for printing out the usage of the program.
 */
void printUsage(void) {
    printf("Usage for adding a new account:      ./21tenmo -a \"personName\"\n");
    printf("Usage for logging in a current user: ./21tenmo -l accountNumber\n");
}

/**
 * @brief MAIN Method, responsible for parsing & validating arguments and
 * handling events (e.g. modifying the database, logging in user).
 */
int main(int argc, char const *argv[])
{
    // printUsage(); // Feel free to remove this line after implementing command line parsing!

    if (argc != 3) {
        myErrNo = ERR_INVALID_ARGS;
        printf("Invalid Arguments.\n");
        myExit(EXIT_FAILURE);
    }

    readCSV();

    char const *argumentFlag = argv[1];
    if (strcmp("-a", argumentFlag) == 0) {
        if (strlen(argv[2]) < MIN_NAME_SIZE || strlen(argv[2]) > MAX_NAME_SIZE) {
            myErrNo = ERR_INVALID_NAME;
            printf("Invalid Name Size.\n");
            myExit(EXIT_FAILURE);
        }

        int maxAccountNumber = FIRST_ACCOUNT_NUMBER + MAX_CSV_SIZE;
        int nextAccountNumber = FIRST_ACCOUNT_NUMBER + DBsize;
        if (nextAccountNumber >= maxAccountNumber) {
            myErrNo = ERR_DB_FULL;
            printf("Invalid Arguments.\n");
            myExit(EXIT_FAILURE);
        }

        arr[DBsize].accountNumber = nextAccountNumber;
        strcpy(arr[DBsize].personName, argv[2]);
        writeCSV();
        myErrNo = NO_ERROR;
        myExit(EXIT_SUCCESS);
    } else if (strcmp("-l", argumentFlag) == 0) {
        unsigned int inputAccountNumber = strtoul(argv[2], NULL, 10);
        userMenu(inputAccountNumber);
        myErrNo = NO_ERROR;
        myExit(EXIT_SUCCESS);
     } else {
        myErrNo = ERR_INVALID_ARGS;
        printf("Invalid Arguments.\n");
        myExit(EXIT_FAILURE); 
     }

    //*** Do NOT remove this ***
    return EXIT_SUCCESS;
}
