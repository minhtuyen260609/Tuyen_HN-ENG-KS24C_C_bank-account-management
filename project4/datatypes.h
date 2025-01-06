#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} 
Date;

typedef struct {
    char id[7];
    char name[35];
    char phone[11];
    char email[30];
    Date publicationDate;
    char userName[20]; 
    char status[10]; 
} User;
