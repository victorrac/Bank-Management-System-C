#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 256

void transaction(const char *sender_dirname, const char *sender_name, const char *sender_surname, int sender_account_number);
int countFilesInDirectory(const char *dirname);
void generate_random_IBAN(char *IBAN, size_t size);
void datab(const char *name, const char *surname, int account_number, const char *IBAN);
void view_account(const char *dirname, const char *name, const char *surname, int account_number);
void edit_database(const char *filename, const char *old_iban, const char *new_iban);
void edit_account(const char *dirname, const char *name, const char *surname, int account_number);
int menu(const char *dirname, const char *name, const char *surname, int account_number);
void createacc(const char *dirname, const char *name, const char *surname, int account_number);
void deleteacc(const char *dirname, const char *name, const char *surname, int account_number);
void accountnrmenu(const char *dirname, const char *name, const char *surname, int file_count);
void login();
int create();

#endif /* HEADER_H */

