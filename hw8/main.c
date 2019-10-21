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

    UNUSED_PARAM(argc);
    UNUSED_PARAM(argv);

    readCSV();

    // char a[] = "--";

    // printf("\n%i\n", formatAndCheckCurrency(a));
    // printf("\n%s\n", a);
    char const *argumentFlag = argv[1];
    if (strcmp("-a", argumentFlag) == 0) {
        unsigned int inputAccountNumber = strtoul(argv[2], NULL, 10);
        userMenu(inputAccountNumber);
    } else if (strcmp("-l", argumentFlag) == 0) {

    }

    // writeCSV();
    //*** Do NOT remove this ***
    return EXIT_SUCCESS;
}
