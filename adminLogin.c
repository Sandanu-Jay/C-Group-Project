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