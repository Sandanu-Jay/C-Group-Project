#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANDIDATES 25

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

int voterLogin() {
    struct candidate {
        char name[100];
        char partyname[20];
        int votes;
        int number;
    };

    int checkVoter(char *voterId) {
        FILE *fp = fopen("voted.txt", "r");
        if (!fp) return 0;
        char line[50];
        while (fgets(line, sizeof(line), fp)) {
            line[strcspn(line, "\n")] = '\0';
            if (strcmp(line, voterId) == 0) {
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        return 0;
    }

    void markVoted(char *voterId) {
        FILE *fp = fopen("voted.txt", "a");
        fprintf(fp, "%s\n", voterId);
        fclose(fp);
    }

    char gid[20], gpassword[20], line[200];
    FILE *fp;
    int found = 0;

    printf("Voter ID: ");
    scanf("%s", gid);
    printf("Password: ");
    scanf("%s", gpassword);

    fp = fopen("voters.txt", "r");
    if (fp == NULL) {
        printf("Error opening voters.txt file!\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        char fileId[20], filePassword[20];
        if (sscanf(line, "%s %s", fileId, filePassword) == 2) {
            if (strcmp(gid, fileId) == 0 && strcmp(gpassword, filePassword) == 0) {
                found = 1;
                break;
            }
        }
    }
    fclose(fp);

    if (!found) {
        printf("Invalid Voter ID or Password!\n");
        return 1;
    }
    
    if (checkVoter(gid)) {
        printf("You have already voted! Exiting...\n");
        return 1;
    }

    printf("\nLogin successful!\n\n");

    int choice;
    printf("1. Vote\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 2) {
        printf("Exiting...\n");
        return 0;
    }

    if (choice != 1) {
        printf("Invalid choice! Exiting...\n");
        return 1;
    }

    FILE *fc = fopen("candidate.txt", "r");
    if (fc == NULL) {
        printf("No candidates file found!\n");
        return 1;
    }

    struct candidate candidates[MAX_CANDIDATES];
    int cCount = 0;
    printf("Available candidates:\n");
    while (fgets(line, sizeof(line), fc)) {
        struct candidate c;
        int fields = sscanf(line, "%s %d %s %d", c.name, &c.number, c.partyname, &c.votes);
        if (fields < 4) 
           c.votes = 0;
        candidates[cCount++] = c;
        printf("%d. %s (Number: %d, Party: %s)\n", cCount, c.name, c.number, c.partyname);
    }
    fclose(fc);

    int choice1;
    printf("\nEnter candidate number to vote: ");
    scanf("%d", &choice1);

    if (choice1 < 1 || choice1 > cCount) {
        printf("Invalid candidate number! Exiting...\n");
        return 1;
    }

   

    FILE *fc2 = fopen("candidate.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    while (fgets(line, sizeof(line), fc2)) {
        struct candidate c;
        int fields = sscanf(line, "%s %d %s %d", c.name, &c.number, c.partyname, &c.votes);
        if (fields < 4)
            c.votes = 0;
        if (strcmp(c.name, candidates[choice1 - 1].name) == 0 &&
            strcmp(c.partyname, candidates[choice1 - 1].partyname) == 0) {
            c.votes++;
        }
        fprintf(temp, "%s %d %s %d\n", c.name, c.number, c.partyname, c.votes);
    }

    fclose(fc2);
    fclose(temp);
    remove("candidate.txt");
    rename("temp.txt", "candidate.txt");

    markVoted(gid);

    printf("\nVote cast successfully!\n");
    printf("You voted for %s of party %s\n", candidates[choice1 - 1].name, candidates[choice1 - 1].partyname);

    FILE *fcheck = fopen("candidate.txt", "r");
    int finalVotes = 0;
    while (fgets(line, sizeof(line), fcheck)) {
        struct candidate c;
        int fields = sscanf(line, "%s %d %s %d", c.name, &c.number, c.partyname, &c.votes);
        if (fields == 4 && strcmp(c.name, candidates[choice1 - 1].name) == 0 &&
            strcmp(c.partyname, candidates[choice1 - 1].partyname) == 0) {
            finalVotes = c.votes;
            break;
        }
    }
    fclose(fcheck);

    FILE *result = fopen("results.txt", "a");
    fprintf(result, "%s -> %s : Votes = %d\n", candidates[choice1 - 1].name, candidates[choice1 - 1].partyname, finalVotes);
    fclose(result);

    return 0;
}

int partyRegistration() {
    struct Party {
        char name[100];
        char id[10];
    };

    struct Candidate {
        char name[100];
        int number;
        char partyname[10];
    };

    int countLines(const char *filename) {
        FILE *fp = fopen(filename, "r");
        if (!fp) return 0;
        int count = 0;
        char line[200];
        while (fgets(line, sizeof(line), fp) != NULL) count++;
        fclose(fp);
        return count;
    }

    char input[10];
    FILE *fpParty, *fpCandidate;
    struct Party p;
    struct Candidate c;
    char line[200];
    int choice;

    printf("\n1.Party registration\n");
    printf("2.Candidate registration\n\n");
    printf("Enter your choice: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &choice);

    switch (choice) {
        case 1: {
            int partyCount = countLines("party.txt");
            if (partyCount >= 5) {
                printf("Party registration limit reached (5 max)!\n");
                return 1;
            }

            fpParty = fopen("party.txt", "a+");
            if (fpParty == NULL) return 1;

            printf("Party name: ");
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = '\0';

            printf("Party ID: ");
            fgets(p.id, sizeof(p.id), stdin);
            p.id[strcspn(p.id, "\n")] = '\0';

            fprintf(fpParty, "%s %s\n", p.name, p.id);
            fclose(fpParty);

            printf("Party registered successfully!\n");
            break;
        }

        case 2: {
            int candidateCount = countLines("candidate.txt");
            if (candidateCount >= 25) {
                printf("Candidate registration limit reached (25 max)!\n");
                return 1;
            }

            fpParty = fopen("party.txt", "r");
            if (fpParty == NULL) {
                printf("No parties registered yet!\n");
                return 1;
            }

            printf("\nAvailable Parties:\n\n");
            while (fgets(line, sizeof(line), fpParty) != NULL) {
                char pname[100], pid[10];
                if (sscanf(line, "%s %s", pname, pid) == 2) {
                    printf("Party: %s (ID: %s)\n", pname, pid);
                }
            }
            fclose(fpParty);
            
            printf ("\n");
            printf("Candidate name: ");
            fgets(c.name, sizeof(c.name), stdin);
            c.name[strcspn(c.name, "\n")] = '\0';

            printf("Candidate number (1-5): ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &c.number);

            if (c.number < 1 || c.number > 5) {
                printf("Invalid candidate number! Must be between 1 and 5.\n");
                return 1;
            }

            printf("Enter Party name: ");
            fgets(c.partyname, sizeof(c.partyname), stdin);
            c.partyname[strcspn(c.partyname, "\n")] = '\0';

            int found = 0;
            fpParty = fopen("party.txt", "r");
            if (fpParty != NULL) {
                while (fgets(line, sizeof(line), fpParty) != NULL) {
                    char pname[100], pid[10];
                    if (sscanf(line, "%s %s", pname, pid) == 2) {
                        if (strcmp(pname, c.partyname) == 0) {
                            found = 1;
                            printf("\n\nCandidate assigned to party: %s\n", pname);
                            break;
                        }
                    }
                }
                fclose(fpParty);
            }

            if (!found) {
                printf("Invalid Party Name!\nCandidate not registered.\n");
                return 1;
            }

            fpCandidate = fopen("candidate.txt", "a+");
            if (fpCandidate == NULL) return 1;

            fprintf(fpCandidate, "%s %d %s 0\n", c.name, c.number, c.partyname);
            fclose(fpCandidate);

            printf("Candidate registered successfully!\n");
            break;
        }

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

int adminLogin() {
    char aid[20];
    printf("\nAdmin ID: ");
    fgets(aid, sizeof(aid), stdin);
    aid[strcspn(aid, "\n")] = '\0';

    if (strcmp(aid, "admin123") == 0) {
        printf("\nLogin successful!\n\n");
    } else {
        printf("Invalid ID!\n");
        return 1;
    }

    int choice;
    printf("1. View political party list\n");
    printf("2. View candidate list\n");
    printf("3. View voting results\n");
    printf ("4. View voters list\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            FILE *fpParty = fopen("party.txt", "r");
            char line[200];
            if (fpParty == NULL) {
                printf("No parties registered yet!\n");
                return 1;
            }
            printf("\nPolitical Parties:\n");
            while (fgets(line, sizeof(line), fpParty) != NULL) {
                printf("%s", line);
            }
            fclose(fpParty);
            break;
        }

        case 2: {
            FILE *fpCandidate = fopen("candidate.txt", "r");
            char cline[200];
            if (fpCandidate == NULL) {
                printf("No candidates registered yet!\n");
                return 1;
            }
            printf("\nCandidates:\n\n");
            while (fgets(cline, sizeof(cline), fpCandidate) != NULL) {
                printf("%s", cline);
            }
            fclose(fpCandidate);
            break;
        }

        case 3: {
            FILE *fpResults = fopen("results.txt", "r");
            char rline[200];
            if (fpResults == NULL) {
                printf("No voting results available yet!\n");
                return 1;
            }
            printf("\nVoting Results:\n\n");
            while (fgets(rline, sizeof(rline), fpResults) != NULL) {
                printf("%s", rline);
            }
            fclose(fpResults);
            break;
        }

       case 4 :  {

           FILE*fpvoters = fopen ("voters.txt" , "r");
           char vline[200];
           if (fpvoters == NULL ) {
                 printf (" No voters registerd yet !\n ");
           }
           printf (" \nvoters list :\n\n");
           while (fgets(vline , sizeof(vline) , fpvoters) != NULL) {
                 printf ("%s" , vline);
           }
           fclose (fpvoters);
           break;
      }


        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

int viewResults() {
    FILE *fpResults = fopen("results.txt", "r");
    char rline[200];
    if (fpResults == NULL) {
        printf("No voting results available yet!\n");
        return 1;
    }
    printf("\nVoting Results:\n\n");
    while (fgets(rline, sizeof(rline), fpResults) != NULL) {
        printf("%s", rline);
    }
    fclose(fpResults);
    return 0;
}






