#include <stdio.h>
#include <stdlib.h>

void clearScreen();
int menu();
void voterRegistration();
void voterLogin();
void partyRegistration();
void partyLogin();   
void adminLogin();
void viewResults();

int main() { 
    clearScreen();
    menu();
    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int menu() {
    int first_time = 1; 
    int choice;

    while (1) {
        clearScreen();

        if (first_time) {
            printf(">>_________ WELCOME ! ______________\n");
            printf(">> SRI LANKAN PARLIAMENT VOTING SYSTEM\n");
            printf(">>___________________________________\n\n\n");
            first_time = 0; 
        }

        printf("___________________________________\n");
        printf("1. Voter Registration\n");
        printf("2. Voter Login\n");
        printf("3. Politics Parties Registration\n");
        printf("4. Politics Parties Login\n");
        printf("5. Admin Login\n");
        printf("6. View Results\n");
        printf("7. Exit\n");
        printf("___________________________________\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); 

        switch (choice) {
            case 1:
                voterRegistration();
                break;
            case 2:
                voterLogin();
                break;
            case 3:
                partyRegistration();
                break;
            case 4:
                partyLogin();   
                break;
            case 5:
                adminLogin();
                break;
            case 6:
                viewResults();
                break;
            case 7:
                printf("Exiting... \n");
                return 0; 
            default:
                printf("Invalid choice! Please try again.\n");
        }    

        printf("\nPress Enter to continue...");
        getchar(); 
    } 

    return 0;
}


void voterRegistration() { printf("Voter Registration sucessfully\n"); }
void voterLogin() { printf("Voter Login sucessfully\n"); }
void partyRegistration() { printf("Party Registration sucessfully\n"); }
void partyLogin() { printf("Party Login sucessfully\n"); }
void adminLogin() { printf("Admin Login sucessfully\n"); }
void viewResults() { printf("View Results sucessfully\n"); }



