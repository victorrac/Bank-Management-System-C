#include "header.h"
int main() {
    char answer;

    printf("\033[1;34mWelcome to VR International Bank!\n");
    printf("\033[1;37mAre you registered? (y/n): ");
    scanf(" %c", &answer);
    printf("\033[1;37m--------------------------------\n");

    if (answer == 'y' || answer == 'Y') {
        printf("\033[1;37mLogin (press \033[1;33ml\033[1;37m): ");
        char answer1;
        scanf(" %c", &answer1);
        if (answer1 == 'l' || answer1 == 'L')
            login();
        else {
            printf("\033[1;31mInvalid input.\n");
        }
    } else if (answer == 'n' || answer == 'N') {
        printf("\033[1;37mDo you want to register? (y/n): ");
        scanf(" %c", &answer);
        if (answer == 'y' || answer == 'Y') {
            create();
        } else if (answer == 'n' || answer == 'N') {
            printf("\033[1;32mThank you for considering our services.\n");
        } else {
            printf("\033[1;31mInvalid input\n");
        }
    } else {
        printf("\033[1;31mInvalid input\n");
    }

    return 0;
}




