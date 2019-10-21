/**
 * @file 21tenmo.c
 * @author YOUR NAME HERE
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "21tenmo.h"
#include "errcodes.h"

/**
 * @brief method for executing the command selected from the menu.
 * 
 * @param choice a single number character indicating the command to be executed
 * @param accountNumber for retrieving info from the DB
 * @return State the state of the program (USER_EXIT is the 'finishing' state)
 */
State executeCommand(char choice, unsigned int accountNumber) {
    switch (choice) {
        case '1':
            showBalance(accountNumber);
            return SHOW_BALANCE;
        case '2':
            modifyBalance(accountNumber);
            return MODIFY_BALANCE;
        case '3':
            sendMoney(accountNumber);
            return SEND_MONEY;
        case '4':
            requestMoney(accountNumber);
            return RECEIVE_MONEY;
        case '5':
            checkRequests(accountNumber);
            return REQUESTS;
        case '6':
            // TODO: implement
            return USER_EXIT;
        default:
            printf("ERROR: Invalid choice entered (%c)\n", choice);
            return MENU;
    }
}

int getDBSize(void) {
    int idx = 0;
    while (arr[idx].accountNumber >= FIRST_ACCOUNT_NUMBER) {
        idx++;
    }
    return idx;
}

int getAccountIndex(unsigned int accountNumber) {
    for (int i = 0; i < getDBSize(); i++) {
        if (arr[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

int accountInactive(unsigned int accountNumber) {
    int size = getDBSize();
    return arr[size - 1].accountNumber < accountNumber;
}

/**
 * @brief helper method for showing balance in the active account.
 * 
 * @param accountNumber for retrieving info from the DB
 */
void showBalance(unsigned int accountNumber) {
    int accountIndex = getAccountIndex(accountNumber);
    printf("Here's your balance: $%.2lf\n", arr[accountIndex].balance);
}

/**
 * @brief helper method for depositing/withdrawing fund to the active account.
 * 
 * @param accountNumber for retrieving info from the DB
 */
void modifyBalance(unsigned int accountNumber) {

    // TODO: implement -- Uncomment the printf below when not testing
    int accountIndex = getAccountIndex(accountNumber);
    printf("Enter an amount to deposit/withdraw (for withdraw add a '-' before the number): $");

    char userInput[256];
    getLine(userInput, 256);

    if (formatAndCheckCurrency(userInput) != 0) {
        printf("Invalid amount, try again\n");
        return;
    }

    float userAmount = strtof(userInput, NULL);
    if (arr[accountIndex].balance + userAmount < 0) {
        myErrNo = ERR_NOT_ENOUGH_FUNDS;
        printf("Not enough funds, sorry.\n");
        return;
    }

    arr[accountIndex].balance += userAmount;
    printf("Modified by: %.2f\n", userAmount);

}

/**
 * @brief helper method for sending money to another account from current active account.
 * 
 * @param senderNumber for retrieving info from the DB
 */
void sendMoney(unsigned int senderNumber) {
    char userInput[256];

    printf("Enter the accountNumber of the receiver: ");
    getLine(userInput, 256);
    unsigned int receiverAccountNumber = strtoul(userInput, NULL, 10);

    int receiverAccountIndex = getAccountIndex(receiverAccountNumber);
    int senderAccountIndex = getAccountIndex(senderNumber);

    if (senderNumber == receiverAccountNumber) {
        myErrNo = ERR_SELF_REQUEST;
        return;
    }

    if (receiverAccountNumber >= FIRST_ACCOUNT_NUMBER + MAX_CSV_SIZE) {
        myErrNo = ERR_INVALID_ACC_NUM;
        return;
    }

    if (accountInactive(receiverAccountNumber)) {
        myErrNo = ERR_INACTIVE_ACCOUNT;
        return;
    }

    if (receiverAccountIndex == -1) {
        myErrNo = ERR_INVALID_ACC_NUM;
        return;
    }

    printf("Enter the amount you want to send: $");
    getLine(userInput, 256);

    if (formatAndCheckCurrency(userInput) != 0) {
        printf("Invalid amount, try again\n");
        return;
    }

    float userAmount = strtof(userInput, NULL);

    if (userAmount <= 0) {
        myErrNo = ERR_INVALID_AMOUNT;
        return;
    }


    if (arr[senderAccountIndex].balance - userAmount < 0) {
        myErrNo = ERR_NOT_ENOUGH_FUNDS;
        printf("Not enough funds, sorry.\n");
        return;
    }

    arr[receiverAccountIndex].balance += userAmount;
    arr[senderAccountIndex].balance -= userAmount;

}

/**
 * @brief helper method for formatting and checking a currencyString
 * 
 * In this program, a currencyString can have at most 1 dot and/or
 * at most one '-' sign, and many commas. Comma separtion
 * validation is not a requirement.
 * 
 * Note: In case of error, the passed in string should NOT be modified
 * 
 * @param currencyString the string to validate/format
 * @return int 0 on successful formatting, nonzero upon error
 */
int formatAndCheckCurrency(char *currencyString) {

    int num_commas = 0;
    int num_decimals = 0;
    int num_dashes = 0;

    int reformattedStringIdx = 0;
    char reformattedString[256];

    for (unsigned int i = 0; i < strlen(currencyString); i++) {
        char currentChar = currencyString[i];
        int validChar = ((currentChar <= '9' && currentChar >= '0') || 
        currentChar == ',' || 
        currentChar == '-' || 
        currentChar == '.');

        if (validChar) {
            if (currentChar == ',') {
                num_commas++;
            }

            if (currentChar == '.') {
                num_decimals++;
            }

            if (currentChar == '-') {
                num_dashes++;
            }
        } else {
            myErrNo = ERR_INVALID_AMOUNT;
            return -1;
        }

        if (num_decimals > 1 || num_dashes > 1) {
            myErrNo = ERR_INVALID_AMOUNT;
            return -1;
        }

        if (currentChar != ',') {
            reformattedString[reformattedStringIdx] = currentChar;
            reformattedStringIdx++;
        }

    }

    reformattedString[reformattedStringIdx] = '\0';
    strcpy(currencyString, reformattedString);

    return 0;
}

/**
 * @brief helper method for requesting money from a different account
 * 
 * @param accountNumber for retrieving info from the DB
 */
void requestMoney(unsigned int accountNumber) {
    UNUSED_PARAM(accountNumber);
    // TODO: implement -- Uncomment the printf below when not testing
    // printf("Enter the accountNumber you want to request from: ");

    // printf("Enter the amount you want to ask this sender: $");  
}

/**
 * @brief helper method for checking/approving/denying pending requests.
 * 
 * @param accountNumber for retrieving info from the DB
 */
void checkRequests(unsigned int accountNumber) {
    UNUSED_PARAM(accountNumber);
    // TODO: implement
}

// ----------------------- DO NOT MODIFY CODE BELOW -----------------------
/**
 * @brief entry point of program for current users; called from main to display menu and process commands. 
 * 
 * @param accountNumber for retrieving info from the DB
 */
void userMenu(unsigned int accountNumber) {
    Account acc = getAccountForTAUseOnly(accountNumber); // HEADER FILE NEEDS TO BE IMPLEMENTED FIRST

    // User operations --> IMPORTANT NOTE: User has to exit to write the DB @see executeCommand
    State currState = MENU;

    // TA USE ONLY: For reading input --> this has to be at least bigger than 1 char + NULL terminator + 1 (extra character)
    // to determine invalid inputs such as "12" --> this is due to the way getLine() is setup
    char choiceBuffer[3]; 
    while (currState != USER_EXIT) {
        // Resetting err number
        myErrNo = NO_ERROR;

        showMenu(acc.accountNumber);
    
        // Reading input
        getLine(choiceBuffer, sizeof(choiceBuffer));

        if (strlen(choiceBuffer) == 1) {
            // Processing input
            currState = executeCommand(choiceBuffer[0], accountNumber);
        } else {
            myErrNo = ERR_INVALID_ARGS;
            printf("ERROR: Invalid input\n");
        }
    }
}

/**
 * @brief Helper function for displaying the user options menu. 
 * 
 * @param accountNumber for retrieving info from the DB
 */
void showMenu(unsigned int accountNumber) {
    (void) (accountNumber);
    // Feel free to add more details to the menu title such as the personName!

    printf("\n$$$$$$$$$$$$$$$$$$$$$ Welcome to 21tenmo ! $$$$$$$$$$$$$$$$$$$$$\n");
    printf("\nSelect one of the options below (just the number):\n");
    printf("1. Show Balance\n");
    printf("2. Modify Balance\n");
    printf("3. Send Money\n");
    printf("4. Request Money\n");
    printf("5. Check Requests\n");
    printf("6. Save & Exit\n");
    printf("\n> ");
}
