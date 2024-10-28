#include "header.h"
int countFilesInDirectory(const char *dirname) {
    int count = 0;
    DIR *directory;
    struct dirent *entry;
    // Open the directory
    directory = opendir(dirname);
    if (directory == NULL) {
        perror("Error opening directory");
        return -1;
    }

    // Iterate through directory entries
    while ((entry = readdir(directory)) != NULL) {
        // Ignore . and ..
        if (entry->d_name[0] == '.')
            continue;
        // Increment count if entry is a regular file
        if (entry->d_type == DT_REG)
            count++;
    }

    // Close the directory
    closedir(directory);

    return count;
}

void generate_random_IBAN(char *IBAN, size_t size) {
    const char *charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_size = 36;
    srand(time(NULL)); // Seed the random number generator

    // Ensure that there is space for the null terminator
    if (size < 2) {
        printf("Error: Buffer size too small\n");
        return;
    }
    // Fill the IBAN with random characters from the charset
    for (size_t i = 0; i < size - 1; i++) {
        IBAN[i] = charset[rand() % charset_size];
    }
    // Add null terminator to end the string
    IBAN[size - 1] = '\0';
}



