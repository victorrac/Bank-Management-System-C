#include "header.h"
void datab(const char *name, const char *surname, int account_number,const char *IBAN) {
    FILE *file = fopen("database.txt", "a"); // Open file in append mode

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write name, surname, and IBAN to file
    fprintf(file, "%s_%s_%d_account.txt ""%s""\n", name, surname,account_number ,IBAN);

    fclose(file); // Close the file
}


void edit_database(const char *filename, const char *old_iban, const char *new_iban) {
    FILE *file = fopen("database.txt", "r+");
    if (file == NULL) {
        printf("\033[1;31mFailed to open database file.\n");
        return;
    }

    FILE *temp_file = fopen("temp_database.txt", "w");
    if (temp_file == NULL) {
        printf("\033[1;31mFailed to create temporary database file.\n");
        fclose(file);
        return;
    }

    char line[200];
    int found = 0;

    // Read each line from the database file
    while (fgets(line, sizeof(line), file)) {
        // Check if the line contains the old IBAN
        if (strstr(line, old_iban) != NULL) {
            // Replace the old IBAN with the new IBAN
            fprintf(temp_file, "%s %s\n", filename, new_iban);
            found = 1;
        } else {
            // Write the line as it is to the temporary file
            fprintf(temp_file, "%s", line);
        }
    }

    fclose(file);
    fclose(temp_file);

    // Remove the old database file
    if (remove("database.txt") != 0) {
        printf("\033[1;31mFailed to remove old database file.\n");
        return;
    }

    // Rename the temporary database file to the original name
    if (rename("temp_database.txt", "database.txt") != 0) {
        printf("\033[1;31mFailed to rename temporary database file.\n");
        return;
    }

    if (!found) {
        printf("\033[1;31mOld IBAN not found in database.\n");
    } else {
        printf("\033[1;32mDatabase updated successfully.\n");
    }
}

