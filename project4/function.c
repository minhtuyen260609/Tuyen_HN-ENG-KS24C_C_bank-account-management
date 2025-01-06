#include <stdio.h>
#include "function.h"
#include <string.h>
void printStartscreen(){
	system("cls");
	printf("***Bank Management System Using C***");
	printf("\n \t CHOOSE YOUR ROLE\n");
	printf("========================\n");
	printf("[1] Admin.\n");
	printf("[2] User.\n");
	printf("[0] Exit the Program\n");
	printf("========================\n");
}
void printMenu(){
	system("cls");
	printf("\n***Student Management System Using C***\n");
	printf("    \t MENU\n");
	printf("========================\n");
	printf("[1] Add A New user.\n");
	printf("[2] Show All users.\n");
	printf("[3] Show detail an user.\n");
	printf("[4] Lock (UnLock) an user.\n");
	printf("[5] Find User By ID.\n");
	printf("[6] User Sorting.\n");
	printf("[0] Exit the Program.\n");
	printf("========================\n");
}
void addUser(User user[], int *n) { 
    int i, j, isDuplicate;
    do{
    	isDuplicate=0;
    	printf("Enter the ID (6 characters): ");
    	scanf("%s", user[*n].id);
    	getchar();
    	if(strlen(user[*n].id)!=6){
    		printf("Invalid input.\n");
    		continue;
		}
		for(j=0;j<*n;j++){
			if(strcmp(user[j].id, user[*n].id)==0){
				printf("Duplicate ID.\n");
				isDuplicate=1;
				break;
			}
		}
	}while(isDuplicate||strlen(user[*n].id)!=6);
    do{
        printf("Enter Name: ");
        fgets(user[*n].name, sizeof(user[*n].name), stdin);
        user[*n].name[strcspn(user[*n].name, "\n")]='\0';
        if(strlen(user[*n].name)==0){
            continue;
        }
        int isInvalid=0;
        for(j=0;user[*n].name[j]!='\0';j++){
            if (!isalpha(user[*n].name[j]) && user[*n].name[j]!=' '){
                printf("Name cannot contain numbers or special characters.\n");
                isInvalid = 1;
                break;
            }
        }
        if(isInvalid==0) break;
    } while(1);
    do{
        isDuplicate=0;
        printf("Enter Phone Number (10 digits): ");
        scanf("%10s", user[*n].phone);
        getchar();
        if(strlen(user[*n].phone) != 10 || strspn(user[*n].phone, "0123456789")!=10){
            printf("Invalid Phone Number! It must be exactly 10 digits.\n");
        }
        for(j=0;j<*n;j++){
            if (strcmp(user[*n].phone, user[j].phone) == 0){
                printf("Duplicate Phone Number detected! Please enter a unique phone number.\n");
                isDuplicate = 1;
                break;
            }
        }
    } while (isDuplicate || strlen(user[*n].phone)!=10 || strspn(user[*n].phone, "0123456789")!=10);
    do{
    	isDuplicate=0;
    	printf("Enter Email: ");
    	scanf("%s", user[*n].email);
    	getchar();
    	for(j=0;j<*n;j++){
    		if(strcmp(user[*n].email, user[j].email)==0){
    			printf("Duplicate email detected!");
    			isDuplicate=1;
    			break;
			}
		}
	}while(isDuplicate);
    do {
        printf("Enter Publication Date (day month year): ");
        scanf("%d %d %d", &user[*n].publicationDate.day, &user[*n].publicationDate.month, &user[*n].publicationDate.year);
        getchar();
        int day=user[*n].publicationDate.day;
        int month=user[*n].publicationDate.month;
        int year=user[*n].publicationDate.year;
        int isInvalidDate = 0;
        if (year< 1900 || year>2100 || month<1 || month>12 || day<1 || day>31){
            isInvalidDate = 1;
        }else if((month==4 || month==6 || month==9 || month==11) && day>30){
            isInvalidDate=1;
        }else if(month==2){
            int isLeapYear=(year%4==0 && year%100!=0) || (year%400==0);
            if((isLeapYear && day>29) || (!isLeapYear && day>28)){
                isInvalidDate = 1;
            }
        }
        if (isInvalidDate){
            printf("Invalid Date! Please enter a valid date.\n");
        } else{
            break;
        }
    } while(1);
    do{
    	isDuplicate=0;
        printf("Enter User Name: ");
        fgets(user[*n].userName, sizeof(user[*n].userName), stdin);
        user[*n].userName[strcspn(user[*n].userName, "\n")] = '\0';
        if(strlen(user[*n].userName)==0){
            printf("Name cannot be empty.\n");
            continue;
        }
        for(j=0;j<*n;j++){
            if(strcmp(user[*n].userName, user[j].userName)==0);
                printf("Duplicate User Name detected.");
                isDuplicate=0;
                break;
            }
        }while(isDuplicate);
        strcpy(user[*n].status, "Open");
    
    printf("User added successfully!\n\n");
    (*n)++;
    printf("Go Back (any key) or Exit (0) "); 
}   
void printUser(User user[], int n) {
	int i;
    printf("\n|============|=====================================|================================|===============|========|\n");
    printf("| %-10s | %-35s | %-30s | %-13s | %-6s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("|============|=====================================|================================|===============|========|\n");
    for (i = 0; i < n; i++) {
        printf("| %-10s | %-35s | %-30s | %-13s | %-6s |\n",
               user[i].id,
               user[i].name,
               user[i].email,
               user[i].phone,
			   user[i].status);
               
        printf("|------------|-------------------------------------|--------------------------------|---------------|--------|\n");
    }
    printf("Go Back (any key) or Exit (0) "); 
}
void saveUsersToFile(User user[], int n) {
    FILE *ptr=fopen("bankdata.bin", "wb+");
    if(ptr==NULL) {
        printf("Cannot open file.\n");
        return;
    }
    fwrite(user, sizeof(User), n, ptr);
    fclose(ptr);
}
void loadUsersFromFile(User users[], int *n) {
    FILE *ptr=fopen("bankdata.bin", "rb");
    if(ptr==NULL){
        printf("Cannot open file.\n");
        return;
    }
    *n=fread(users, sizeof(User), 50, ptr);
    fclose(ptr);
}
void searchUserByName(User user[], int n) {
    char searchQuery[50];
    int i, found=0;
    printf("Enter the name to search: ");
    scanf("%s", &searchQuery);
    getchar();
    printf("\nMatching Users:\n");
    for(i=0;i<n;i++){
        if(strstr(user[i].name, searchQuery)!=NULL){
            if(!found){
                printf("\n|============|================================|======================|===============|\n");
                printf("| %-10s | %-30s | %-20s | %-13s |\n", "ID", "Name", "Email", "Phone");
                printf("|============|================================|======================|===============|\n");
            }
            printf("| %-10s | %-30s | %-20s | %-13s |\n",
                   user[i].id, user[i].name, user[i].email, user[i].phone);
            found=1;
        }
    }
    if(found){
        printf("|------------|--------------------------------|----------------------|---------------|\n");
    }else{
        printf("No users found containing the name '%s'.\n", searchQuery);
    }
    printf("Go Back (any key) or Exit (0) "); 
}
void searchUserById(User user[], int n) {
    char searchQuery[50];
    int i, found=0;
    printf("Enter the id to search: ");
    scanf("%s", &searchQuery);
    getchar();
    printf("\nMatching Users:\n");
    for(i=0;i<n;i++){
        if(strstr(user[i].id, searchQuery)!=NULL){
            if(!found){
                printf("\n|==========|================================|======================|===============|======================|===========|\n");
                printf("| %-8s | %-30s | %-20s | %-13s | %-20s | %-9s |\n", "ID", "Name", "Email", "Phone", "User Name", "status");
                printf("|==========|================================|======================|===============|======================|===========|\n");
            }
            printf("| %-8s | %-30s | %-20s | %-13s | %-20s | %-9s |\n",
                   user[i].id, user[i].name, user[i].email, user[i].phone, user[i].userName, user[i].status);
            found=1;
        }
    }
    if(found){
        printf("|----------|--------------------------------|----------------------|---------------|----------------------|-----------|\n");
    }else{
        printf("No users found containing the name '%s'.\n", searchQuery);
    }
    printf("Go Back (any key) or Exit (0) "); 
}
void openAndLock(User user[], int n){
	char searchQuery[50];
	int i, found=0;
	printf("Enter the user you want to lock or unlock: ");
    scanf("%s", &searchQuery);
    for(i=0;i<n;i++){
    	if(strcmp(user[i].id, searchQuery)==0){
    		if(strcmp(user[i].status, "Open")==0){
    			strcpy(user[i].status, "Lock");
			}else if(strcmp(user[i].status, "Lock")==0){
				strcpy(user[i].status, "Open");
			}
			found=1;
		}
	}
	if(!found){
		printf("No user found containing the id.");
	}
}
void sortUserByName(User user[], int n){
//	getchar();
	int i, j, key; 
	printf("1. Sort User a->z \n2. Sort User z->a\n");
	printf("Enter choice: ");
	scanf("%d", &key);
	getchar();
	if(key==1){
		for(i=0;i<n-1;i++){
			for(j=i+1;j<n;j++){
				if(strcmp(user[i].name,user[j].name)>0){
					User temp = user[i];
					user[i] =user[j];
					user[j]=temp;
				}
			}
		}
		printf("\n|============|=====================================|================================|===============|========|\n");
	    printf("| %-10s | %-35s | %-30s | %-13s | %-6s |\n", "ID", "Name", "Email", "Phone", "Status");
	    printf("|============|=====================================|================================|===============|========|\n");
    	for (i=0;i<n; i++){
        	printf("| %-10s | %-35s | %-30s | %-13s | %-6s |\n",
               user[i].id,
               user[i].name,
               user[i].email,
               user[i].phone,
			   user[i].status);  
        printf("|------------|-------------------------------------|--------------------------------|---------------|--------|\n");
    }
    printf("Go Back (any key) or Exit (0) "); 
	}else if(key==2){
		for(i=0;i<n-1;i++){
			for(j=i+1;j<n;j++){
				if(strcmp(user[i].name,user[j].name)<0){
					User temp = user[i];
					user[i] =user[j];
					user[j]=temp;
				}
			}
		}
		
		printf("\n|============|=====================================|================================|===============|========|\n");
	    printf("| %-10s | %-35s | %-30s | %-13s | %-6s |\n", "ID", "Name", "Email", "Phone", "Status");
	    printf("|============|=====================================|================================|===============|========|\n");
	    for (i=0;i<n; i++){
	        printf("| %-10s | %-35s | %-30s | %-13s | %-6s |\n",
               user[i].id,
               user[i].name,
               user[i].email,
               user[i].phone,
			   user[i].status);
        printf("|------------|-------------------------------------|--------------------------------|---------------|--------|\n");
}
    printf("Go Back (any key) or Exit (0) "); 
	}else{	
	
	}
}
