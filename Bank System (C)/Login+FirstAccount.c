#include "header.h"
void login() {
    char name[50], surname[50];
    char dirname[MAX_FILENAME_LENGTH];
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;
    char answer;

    printf("\033[1;37mEnter your name: ");
    scanf("%s", name);
    printf("\033[1;37mEnter your surname: ");
    scanf("%s", surname);
    printf("\033[1;37m---------------------\n");

    // Constructing the directory name by concatenating name and surname
    snprintf(dirname, sizeof(dirname), "%s_%s", name, surname);
    // Opening the directory
    dir = opendir(dirname);
    // Checking if the directory was opened successfully
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) { // Checking if it's a regular file
                file_count++;
            }
        }
        closedir(dir);
        printf("\033[1;32mLogin successful.\n");
        if (file_count > 0) {
            accountnrmenu(dirname, name, surname, file_count);
        } else {
            printf("\033[1;31m%s %s has no accounts.\n", name, surname);
            printf("\033[1;36mCreate account (\033[1;33mc\033[1;36m)\n");
            printf("\033[1;37mPlease enter your choice: ");
            scanf(" %c", &answer);
            if (answer == 'c' || answer == 'C') {
                createacc(dirname, name, surname, file_count + 1);
                menu(dirname, name, surname, file_count + 1);
            } else {
                printf("\033[1;31mInvalid choice.\n");
            }
        }
    } else {
        printf("\033[1;31mNot in our database. Please register first.\n");
    }
}

int create() {
    char name[50], surname[50];
    char dirname[MAX_FILENAME_LENGTH];

    printf("\033[1;37mEnter your name: ");
    scanf("%s", name);
    printf("\033[1;37mEnter your surname: ");
    scanf("%s", surname);
    printf("\033[1;37m---------------------\n");

    // Constructing the directory name by concatenating name and surname
    snprintf(dirname, MAX_FILENAME_LENGTH, "%s_%s", name, surname);

    // Creating the directory
    int status = mkdir(dirname, 0777);

    if (!status) {
        printf("\033[1;32mWelcome %s %s at VR International Bank.\n", name, surname);
        printf("\033[1;37mLogin (press \033[1;33ml\033[1;37m): ");
        char answer;
        scanf(" %c", &answer);
        if (answer == 'l' || answer == 'L')
            login();
        else {
            printf("\033[1;31mInvalid input.\n");
        }
    } else {
        printf("\033[1;32mWelcome, %s %s! You are already in our database at VR International Bank.\n", name, surname);
        printf("\033[1;37mLogin (press \033[1;33ml\033[1;37m): ");
        char answer1;
        scanf(" %c", &answer1);
        if (answer1 == 'l' || answer1 == 'L')
            login();
        else {
            printf("\033[1;31mInvalid input.\n");
        }
    }

    return 0;
}




