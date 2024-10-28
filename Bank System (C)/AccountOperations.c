#include "header.h"

void createacc(const char *dirname, const char *name, const char *surname, int account_number) {
    char filepath[MAX_FILENAME_LENGTH];
    FILE *file;
    char IBAN[20];
    char coin[10] = "Euro";
    double amount = 0; // Initial amount of money
    int file_exists = 1;

    while (file_exists) {
        // Constructing the file path
        snprintf(filepath, sizeof(filepath), "%s/%s_%s_%d_account.txt", dirname, name, surname, account_number);

        // Attempting to open the file for reading
        file = fopen(filepath, "r");
        if (file != NULL) {
            // File exists, close it and try the next number
            fclose(file);
            account_number++;
        } else {
            // File doesn't exist, create it
            file_exists = 0;
            generate_random_IBAN(IBAN, sizeof(IBAN)); // Example IBAN

            // Attempting to create the file
            file = fopen(filepath, "w");
            if (file != NULL) {
                // Writing data to the file
                fprintf(file, "%s %s\n", name, surname); // Writing name and surname
                fprintf(file, "%s\n", IBAN); // Writing IBAN
                fprintf(file, "%s\n", coin); // Writing coin
                fprintf(file, "%.2f\n", amount); // Writing amount of money
                fclose(file);
                datab(name,surname,account_number,IBAN);
                generate_random_IBAN(IBAN, sizeof(IBAN));
                printf("\033[1;32mAccount created successfully\n");
            } else {
                printf("\033[1;31mFailed to create account\n");
            }
        }
    }
}


void deleteacc(const char *dirname, const char *name, const char *surname, int account_number) {
    char filepath[MAX_FILENAME_LENGTH];

    // Constructing the file path
    snprintf(filepath, sizeof(filepath), "%s/%s_%s_%d_account.txt", dirname, name, surname, account_number);

    // Attempting to delete the file
    if (remove(filepath) == 0) {
        printf("\033[1;32mAccount deleted successfully.\n");

        // Rename files whose number is greater than the deleted file's number
        for (int i = account_number + 1; ; i++) {
            char current_filepath[MAX_FILENAME_LENGTH];
            char new_filepath[MAX_FILENAME_LENGTH];

            // Construct current file path
            snprintf(current_filepath, sizeof(current_filepath), "%s/%s_%s_%d_account.txt", dirname, name, surname, i);

            // Check if the current file exists
            if (access(current_filepath, F_OK) != 0) {
                break; // No more files with higher numbers exist
            }

            // Construct new file path by decrementing the number
            snprintf(new_filepath, sizeof(new_filepath), "%s/%s_%s_%d_account.txt", dirname, name, surname, i - 1);

            // Rename the file
            if (rename(current_filepath, new_filepath) != 0) {
                printf("\033[1;31mFailed to rename file.\n");
                return; // Stop renaming further files
            }
        }
    } else {
        printf("\033[1;31mFailed to delete the account file.\n");
    }


}


void edit_account(const char *dirname, const char *name, const char *surname, int account_number) {
    char filepath[MAX_FILENAME_LENGTH];
    FILE *file;

    // Constructing the file path
    snprintf(filepath, sizeof(filepath), "%s/%s_%s_%d_account.txt", dirname, name, surname, account_number);
    char new_iban[20], new_coin[10];
    double new_amount;
    char old_iban[20], old_coin[10];
    double old_amount;

    // Opening the file for reading and writing
    file = fopen(filepath, "r");
    if (file != NULL) {
        // Reading data from the file
        fscanf(file, "%*s %*s"); // Skip name and surname
        fscanf(file, "%s", old_iban); // Read old IBAN
        fscanf(file, "%s", old_coin); // Read old coin
        fscanf(file, "%lf", &old_amount); // Read old amount

        // Display current account information
        printf("\033[1;37mCurrent account information:\n");
        printf("\033[1;36mIBAN: %s\n", old_iban);
        printf("\033[1;36mCoin: %s\n", old_coin);
        printf("\033[1;36mAmount: %.2f\n", old_amount);}
    fclose(file);
    file = fopen(filepath, "w");
    if (file != NULL) {
        printf("\033[1;36mEnter new IBAN: ");
        scanf("%s", new_iban);
        printf("\033[1;36mEnter new coin: ");
        scanf("%s", new_coin);
        printf("\033[1;36mEnter new amount: ");
        scanf("%lf", &new_amount);

        // Move file pointer to the beginning
        rewind(file);

        // Write updated data to the file
        fprintf(file, "%s %s\n", name, surname); // Write name and surname
        fprintf(file, "%s\n", new_iban); // Write new IBAN
        fprintf(file, "%s\n", new_coin); // Write new coin
        fprintf(file, "%.2f\n", new_amount); // Write new amount
    }
    fclose(file);
    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, sizeof(filename), "%s_%s_%d_account.txt", name, surname, account_number);
    edit_database(filename, old_iban, new_iban);

    printf("\033[1;32mAccount information updated successfully\n");


    // Return to the menu
    printf("\033[1;36mBack to menu (\033[1;33m\033[1;33;1mb\033[1;36m)\n");
    printf("\033[1;37mPlease enter your choice: ");
    char answer;
    scanf(" %c", &answer);
    if (answer == 'b' || answer == 'B') {
        menu(dirname, name, surname, account_number);
    } else {
        printf("\033[1;31mInvalid choice.\n");
    }
}


void view_account(const char *dirname, const char *name, const char *surname, int account_number) {
    char filepath[MAX_FILENAME_LENGTH];
    FILE *file;
    // Constructing the file path
    snprintf(filepath, sizeof(filepath), "%s/%s_%s_%d_account.txt", dirname, name, surname, account_number);

    // Opening the file for reading
    file = fopen(filepath, "r");
    if (file != NULL) {
        char iban[20], coin[10],n[15],s[20];
        double amount;

        // Reading data from the file
        fscanf(file, "%s %s", n, s);
        fscanf(file, "%s", iban);
        fscanf(file, "%s", coin);
        fscanf(file, "%lf", &amount);

        printf("\033[1;36mOwner: %s %s\n", name, surname);
        printf("\033[1;36mIBAN: %s\n", iban);
        printf("\033[1;36mCoin: %s\n", coin);
        printf("\033[1;36mAmount: %.2f\n", amount);

        fclose(file);
    } else {
        printf("\033[1;31mFailed to open account file.\n");
    }

    printf("\033[1;36mBack to menu (\033[1;33;1mb\033[1;36m)\n");
    printf("\033[1;37mPlease enter your choice: ");
    char answer;
    scanf(" %c", &answer);
    if (answer == 'b' || answer == 'B') {
        menu(dirname, name, surname, account_number);
    } else {
        printf("\033[1;31mInvalid choice.\n");
    }
}


void transaction(const char *sender_dirname, const char *sender_name, const char *sender_surname, int sender_account_number) {
    char sender_filepath[MAX_FILENAME_LENGTH];
    FILE *sender_file;
    char receiver_name[50], receiver_surname[50], receiver_iban[20], receiver_f[40], receiver_dirname[50];
    int receiver_account_number;
    double amount;

    printf("\033[1;37mEnter receiver's IBAN: ");
    scanf("%s", receiver_iban);
    printf("\033[1;37mEnter amount to transfer: ");
    scanf("%lf", &amount);

    // Open sender's account file for reading and writing
    snprintf(sender_filepath, sizeof(sender_filepath), "%s/%s_%s_%d_account.txt", sender_dirname, sender_name, sender_surname, sender_account_number);
    sender_file = fopen(sender_filepath, "r+");
    if (sender_file == NULL) {
        printf("\033[1;31mFailed to open sender's account file.\n");
        return;
    }

    // Read sender's current balance
    double sender_balance;
    fscanf(sender_file, "%*s %*s"); // Skip name and surname
    fscanf(sender_file, "%*s"); // Skip IBAN
    fscanf(sender_file, "%*s"); // Skip coin
    fscanf(sender_file, "%lf", &sender_balance);

    // Check if sender has enough balance for the transaction
    if (sender_balance < amount) {
        printf("\033[1;31mInsufficient balance for the transaction.\n");
        fclose(sender_file);
        return;
    }

    // Update sender's balance
    fseek(sender_file, 0, SEEK_SET); // Move file pointer to the beginning
    char buffer[100];
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), sender_file) != NULL) {
        if (line_count == 3) { // Fourth line, where the balance is stored
            double current_balance;
            sscanf(buffer, "%lf", &current_balance); // Read current balance from the fourth line
            fseek(sender_file, -strlen(buffer), SEEK_CUR); // Move file pointer back to the beginning of the line
            fprintf(sender_file, "%.2f\n", current_balance - amount); // Write updated balance
            break; // No need to read further
        }
        line_count++;
    }

    fclose(sender_file);

    // Search for the receiver's name and surname based on IBAN in database.txt
    FILE *database_file = fopen("database.txt", "r");
    if (database_file == NULL) {
        printf("\033[1;31mFailed to open database file.\n");
        return;
    }

    int found = 0;
    while (fscanf(database_file, "%s_%s_%d_account.txt", receiver_f, receiver_name, receiver_surname) != EOF) {
        char temp_iban[20];
        fscanf(database_file, "%s", temp_iban); // Read IBAN

        // Check if the IBAN matches the receiver's IBAN
        if (strcmp(temp_iban, receiver_iban) == 0) {
            found = 1;
            break;
        }
    }
    fclose(database_file);

    if (!found) {
        printf("\033[1;31mReceiver's account not found.\n");
        return;
    }

    // Construct the receiver's directory path
    char *underscore1 = strchr(receiver_f, '_');
    if (underscore1 != NULL) {
        char *underscore2 = strchr(underscore1 + 1, '_');
        if (underscore2 != NULL) {
            size_t name_length = underscore1 - receiver_f;
            size_t surname_length = underscore2 - (underscore1 + 1);
            strncpy(receiver_name, receiver_f, name_length);
            receiver_name[name_length] = '\0'; // Null-terminate the string
            strncpy(receiver_surname, underscore1 + 1, surname_length);
            receiver_surname[surname_length] = '\0'; // Null-terminate the string
        }
    }

    snprintf(receiver_dirname, sizeof(receiver_dirname), "%s_%s", receiver_name, receiver_surname);

    // Open receiver's directory
    DIR *receiver_dir = opendir(receiver_dirname);
    if (receiver_dir == NULL) {
        printf("\033[1;31mFailed to open receiver's directory.\n");
        return;
    }

    // Change current working directory to receiver's directory
    if (chdir(receiver_dirname) != 0) {
        printf("\033[1;31mFailed to change directory to receiver's directory.\n");
        closedir(receiver_dir);
        return;
    }

    // Open receiver's account file for reading and writing
    FILE *receiver_file = fopen(receiver_f, "r+");
    if (receiver_file == NULL) {
        printf("\033[1;31mFailed to open receiver's account file.\n");
        return;
    }

    // Read receiver's current balance
    double receiver_balance;
    fscanf(receiver_file, "%*s %*s"); // Skip name and surname
    fscanf(receiver_file, "%*s"); // Skip IBAN
    fscanf(receiver_file, "%*s"); // Skip coin
    fscanf(receiver_file, "%lf", &receiver_balance);

    // Update receiver's balance
    fseek(receiver_file, 0, SEEK_SET); // Move file pointer to the beginning
    char buffer1[100];
    int line_count1 = 0;
    while (fgets(buffer1, sizeof(buffer1), receiver_file) != NULL) {
        if (line_count1 == 3) { // Fourth line, where the balance is stored
            double current_balance1;
            sscanf(buffer1, "%lf", &current_balance1); // Read current balance from the fourth line
            fseek(receiver_file, -strlen(buffer1), SEEK_CUR); // Move file pointer back to the beginning of the line
            fprintf(receiver_file, "%.2f\n", current_balance1 + amount); // Write updated balance
            break; // No need to read further
        }
        line_count1++;
    }

    fclose(receiver_file);


    printf("\033[1;32mTransaction successful.\n");
    closedir(receiver_dir);
}

