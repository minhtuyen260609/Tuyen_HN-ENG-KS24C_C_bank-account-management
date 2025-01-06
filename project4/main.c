#include <stdio.h>
#include <stdlib.h>
#include "function.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]){
    User users[50];
    int n = 0;
    int choice, select;
	do{
		printStartscreen();
	    printf("Enter The Choice: ");
	    scanf("%d", &choice);
	    if(choice==1){
	    	do{ 	
    		printMenu();
	    	printf("Enter The Choice: ");
	    	scanf("%d", &select);
			getchar();
	    	switch(select){
	    		case 1:
	    			system("cls");
	    			loadUsersFromFile(users, &n);
					addUser(users, &n); 
				    saveUsersToFile(users, n);
				    getchar();
	            	break;
				case 2:
					system("cls");
					loadUsersFromFile(users, &n);
		            printUser(users, n);
		            getchar(); 
		            break;	
				case 3:
					system("cls");
					loadUsersFromFile(users, &n);
					searchUserByName(users, n);
					getchar(); 
					break; 
				case 4:
					system("cls");
					loadUsersFromFile(users, &n);
					openAndLock(users,n);
					saveUsersToFile(users, n);
					break; 
				case 5:
					system("cls");
					loadUsersFromFile(users, &n);
					searchUserById(users, n);
					getchar(); 
					break; 
				case 6:
					system("cls");
					loadUsersFromFile(users, &n);
					sortUserByName(users, n);
					getchar();
					break;
				case 0:
					break; 
				default:
	                printf("Invalid choice. Please try again.\n");
			} 
			}while(select!=0); 
	    	
		}else if(choice==2){
			
		}else if(choice==0){
			system("cls");
			printf("==========Thank You==========\n"); 
			printf("========See You Soon=========="); 
		}else{
			printf("Invalid choice. Please try again.\n");
		}
	}while(choice!=0); 

    return 0;
}
