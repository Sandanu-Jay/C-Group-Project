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
        if (fields < 4) c.votes = 0;
        candidates[cCount++] = c;
        printf("%d. %s (Number: %d, Party: %s, Votes: %d)\n", cCount, c.name, c.number, c.partyname, c.votes);
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
        if (fields < 4) c.votes = 0;
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
