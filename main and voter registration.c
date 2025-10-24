#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANDIDATES 10

int voterRegistration();
int voterLogin();
int partyRegistration();
int adminLogin();
int viewResults();

int main() {
    int first_time = 1;
    int choice;

    while (1) {
        if (first_time) {
            printf("\n\n>>_________ WELCOME ! ______________<<\n");
            printf(">> SRI LANKAN PARLIAMENT VOTING SYSTEM<<\n");
            printf(">>___________________________________<<\n\n");
            first_time = 0;
        }

        printf("\n___________________________________\n");
        printf("1. Voter Registration\n");
        printf("2. Voter Login\n");
        printf("3. Politics Parties & candidates Registration\n");
        printf("4. Admin Login\n");
        printf("5. View Results\n");
        printf("6. Exit\n");
        printf("___________________________________\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
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
                adminLogin();
                break;
            case 5:
                viewResults();
                break;
            case 6:
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

int voterRegistration() {
    char name[50];
    int yyyy;
    char address[100];
    char gender[10];
    char nic[20];

    printf("\n___Voter Registration Form___\n\n");

    printf("Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Birth year: ");
    scanf("%d", &yyyy);
    while (getchar() != '\n');

    printf("Address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';

    printf("Gender: ");
    fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = '\0';

    printf("NIC number: ");
    fgets(nic, sizeof(nic), stdin);
    nic[strcspn(nic, "\n")] = '\0';

    srand(time(NULL));
    int current_year = 2025;

    if (current_year - yyyy < 18) {
        printf("You must be 18 years or older to register.\n");
    } else if (strlen(nic) != 9 && strlen(nic) != 12) {
        printf("Invalid NIC number length. Please enter a 9 or 12 digit number.\n");
    } else {
        int id = rand() % 10000;
        printf("\nYour ID is: %04d\n", id);

        char password[9];
        int passwordLength = 5;
        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        for (int i = 0; i < passwordLength; i++) {
            int key = rand() % (sizeof(charset) - 1);
            password[i] = charset[key];
        }
        password[passwordLength] = '\0';

        printf("Your password is: %s\n", password);
        printf("\nYou are successfully registered.\n");

        FILE *fp = fopen("voters.txt", "a+");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
        fprintf(fp, "%d %s\n", id, password);
        fclose(fp);
    }

    return 0;
}