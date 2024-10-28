#include "header.h"
int menu(const char *dirname, const char *name, const char *surname, int account_number) {
    char answer;

    printf("\033[1;36mView account (\033[1;33mv\033[1;36m)\n");
    printf("\033[1;36mEdit account (\033[1;33me\033[1;36m)\n");
    printf("\033[1;36mMake a transaction (\033[1;33mt\033[1;36m)\n");
    printf("\033[1;36mCreate an account (\033[1;33mc\033[1;36m)\n");
    printf("\033[1;36mSelect account (\033[1;33ma\033[1;36m)\n");
    printf("\033[1;36mDelete account (\033[1;33md\033[1;36m)\n");
    printf("\033[1;36mQuit (\033[1;33mq\033[1;36m)\n");
    printf("\033[1;37mPlease enter your choice: ");
    scanf(" %c", &answer);

    if (answer == 'v' || answer == 'V') {
        printf("\033[1;32mYou chose to view account.\n");
        view_account(dirname,name,surname,account_number);
    } else if (answer == 'e' || answer == 'E') {
        printf("\033[1;32mYou chose to edit account.\n");
        edit_account(dirname,name,surname,account_number);
    } else if (answer == 't' || answer == 'T') {
        printf("\033[1;32mYou chose to make a transaction.\n");
        transaction(dirname,name,surname,account_number);
    } else if (answer == 'c' || answer == 'C') {
        printf("\033[1;32mYou chose to create an account.\n");
        createacc(dirname,name,surname,account_number+1);
    } else if (answer == 'd' || answer == 'D') {
        printf("\033[1;32mYou chose to delete an account.\n");
        deleteacc(dirname,name,surname,account_number);
    } else if (answer == 'a' || answer == 'A') {
        printf("\033[1;32mYou chose to select an account.\n");
        accountnrmenu(dirname,name,surname,account_number);
    } else if (answer == 'q' || answer == 'Q') {
        printf("\033[1;32mQuitting...\n");
        exit(0); // Exit the program
    } else {
        printf("\033[1;31mInvalid choice.\n");
    }

    return 0;
}

void accountnrmenu(const char *dirname, const char *name, const char *surname, int file_count) {
    file_count=countFilesInDirectory(dirname);
    printf("\033[1;32m%s %s has %d account(s)\n", name, surname, file_count);
    // Display existing accounts
    printf("\033[1;36mSelect an account:\n");

    DIR *dir;
    struct dirent *entry;
    // Opening the directory
    dir = opendir(dirname);
    // Checking if the directory was opened successfully
    if (dir != NULL) {
        int account_nr = 1;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) { // Checking if it's a regular file
                printf("\033[1;36mAccount %d (\033[1;33m%d\033[1;36m)\n", account_nr, account_nr);
                account_nr++;
            }
        }
        closedir(dir);

        printf("\033[1;37mPlease enter the account number: ");
        int selected_account;
        scanf("%d", &selected_account);
        if (selected_account >= 1 && selected_account <file_count+1) {
            // Proceed to menu with selected account
            menu(dirname, name, surname, selected_account);
        } else {
            printf("\033[1;31mInvalid account number.\n");
        }
    } else {
        printf("\033[1;31mFailed to open directory.\n");
    }
}


