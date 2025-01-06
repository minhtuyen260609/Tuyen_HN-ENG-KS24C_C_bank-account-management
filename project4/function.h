#include "datatypes.h"

void printStartScreen(); 
void printMenu(); 
void addUser(User user[], int *n);
void printUser(User user[], int n);
void saveUsersToFile(User user[], int n);
void loadUsersFromFile(User user[], int *n);
void searchUserByName(User user[], int n);
void searchUserById(User user[], int n);
void openAndLock(User user[], int n);
void sortUserByName(User user[], int n);
