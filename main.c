#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VOTERS 100
#define MAX_REPS 10
#define MAX_NAME 50
#define ADMIN_PASS "admin123"

// Structures
typedef struct {
    char voter_id[10];
    char name[MAX_NAME];
    int has_voted;
} Voter;

typedef struct {
    char rep_id[10];
    char name[MAX_NAME];
    int vote_count;
} Representative;

typedef struct {
    time_t start_time;
    time_t end_time;
} TimeFrame;

// File names
const char *VOTERS_FILE = "voters.txt";
const char *REPS_FILE = "reps.txt";
const char *VOTES_FILE = "votes.txt";
const char *TIMEFRAME_FILE = "timeframe.txt";

// Global variables
Voter voters[MAX_VOTERS];
Representative reps[MAX_REPS];
TimeFrame timeframe;
int voter_count = 0;
int rep_count = 0;

// Function prototypes
void save_voters();
void load_voters();
void save_reps();
void load_reps();
void save_votes();
void load_votes();
void save_timeframe();
void load_timeframe();
void admin_menu();
void voter_menu();
int authenticate_admin();
void appoint_rep();
void set_timeframe();
void view_voters();
void register_voter();
void cast_vote();
void view_results();
int is_voting_open();

// File operations
void save_voters() {
    FILE *fp = fopen(VOTERS_FILE, "w");
    if (!fp) {
        printf("Error opening voters file!\n");
        return;
    }
    for (int i = 0; i < voter_count; i++) {
        fprintf(fp, "%s %s %d\n", voters[i].voter_id, voters[i].name, voters[i].has_voted);
    }
    fclose(fp);
}

void load_voters() {
    FILE *fp = fopen(VOTERS_FILE, "r");
    if (!fp) return;
    voter_count = 0;
    while (fscanf(fp, "%s %[^\n] %d", voters[voter_count].voter_id, voters[voter_count].name, &voters[voter_count].has_voted) == 3) {
        voter_count++;
    }
    fclose(fp);
}

void save_reps() {
    FILE *fp = fopen(REPS_FILE, "w");
    if (!fp) {
        printf("Error opening reps file!\n");
        return;
    }
    for (int i = 0; i < rep_count; i++) {
        fprintf(fp, "%s %s %d\n", reps[i].rep_id, reps[i].name, reps[i].vote_count);
    }
    fclose(fp);
}

void load_reps() {
    FILE *fp = fopen(REPS_FILE, "r");
    if (!fp) return;
    rep_count = 0;
    while (fscanf(fp, "%s %[^\n] %d", reps[rep_count].rep_id, reps[rep_count].name, &reps[rep_count].vote_count) == 3) {
        rep_count++;
    }
    fclose(fp);
}

void save_votes() {
    FILE *fp = fopen(VOTES_FILE, "w");
    if (!fp) {
        printf("Error opening votes file!\n");
        return;
    }
    for (int i = 0; i < rep_count; i++) {
        fprintf(fp, "%s %d\n", reps[i].rep_id, reps[i].vote_count);
    }
    fclose(fp);
}

void load_votes() {
    FILE *fp = fopen(VOTES_FILE, "r");
    if (!fp) return;
    char rep_id[10];
    int vote_count;
    while (fscanf(fp, "%s %d", rep_id, &vote_count) == 2) {
        for (int i = 0; i < rep_count; i++) {
            if (strcmp(reps[i].rep_id, rep_id) == 0) {
                reps[i].vote_count = vote_count;
                break;
            }
        }
    }
    fclose(fp);
}

void save_timeframe() {
    FILE *fp = fopen(TIMEFRAME_FILE, "w");
    if (!fp) {
        printf("Error opening timeframe file!\n");
        return;
    }
    fprintf(fp, "%ld %ld\n", timeframe.start_time, timeframe.end_time);
    fclose(fp);
}

void load_timeframe() {
    FILE *fp = fopen(TIMEFRAME_FILE, "r");
    if (!fp) return;
    fscanf(fp, "%ld %ld", &timeframe.start_time, &timeframe.end_time);
    fclose(fp);
}

// Admin functions
int authenticate_admin() {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);
    return strcmp(password, ADMIN_PASS) == 0;
}

void appoint_rep() {
    if (rep_count >= MAX_REPS) {
        printf("Maximum representatives reached!\n");
        return;
    }
    Representative rep;
    printf("Enter representative ID: ");
    scanf("%s", rep.rep_id);
    printf("Enter representative name: ");
    scanf(" %[^\n]", rep.name);
    rep.vote_count = 0;
    reps[rep_count++] = rep;
    save_reps();
    printf("Representative added successfully!\n");
}

void set_timeframe() {
    char start_str[20], end_str[20];
    struct tm tm_start = {0}, tm_end = {0};
    printf("Enter start time (YYYY-MM-DD HH:MM:SS): ");
    scanf(" %[^\n]", start_str);
    printf("Enter end time (YYYY-MM-DD HH:MM:SS): ");
    scanf(" %[^\n]", end_str);

    // Parse input strings to time_t
    sscanf(start_str, "%d-%d-%d %d:%d:%d",
           &tm_start.tm_year, &tm_start.tm_mon, &tm_start.tm_mday,
           &tm_start.tm_hour, &tm_start.tm_min, &tm_start.tm_sec);
    sscanf(end_str, "%d-%d-%d %d:%d:%d",
           &tm_end.tm_year, &tm_end.tm_mon, &tm_end.tm_mday,
           &tm_end.tm_hour, &tm_end.tm_min, &tm_end.tm_sec);

    tm_start.tm_year -= 1900; // Adjust for tm structure
    tm_start.tm_mon -= 1;
    tm_end.tm_year -= 1900;
    tm_end.tm_mon -= 1;

    timeframe.start_time = mktime(&tm_start);
    timeframe.end_time = mktime(&tm_end);
    save_timeframe();
    printf("Timeframe set successfully!\n");
}

void view_voters() {
    if (voter_count == 0) {
        printf("No registered voters.\n");
        return;
    }
    printf("Registered Voters:\n");
    for (int i = 0; i < voter_count; i++) {
        printf("ID: %s, Name: %s, Voted: %s\n",
               voters[i].voter_id, voters[i].name,
               voters[i].has_voted ? "Yes" : "No");
    }
}

// Voter functions
void register_voter() {
    if (voter_count >= MAX_VOTERS) {
        printf("Maximum voters reached!\n");
        return;
    }
    Voter voter;
    printf("Enter voter ID: ");
    scanf("%s", voter.voter_id);
    // Check for unique ID
    for (int i = 0; i < voter_count; i++) {
        if (strcmp(voters[i].voter_id, voter.voter_id) == 0) {
            printf("Voter ID already exists!\n");
            return;
        }
    }
    printf("Enter voter name: ");
    scanf(" %[^\n]", voter.name);
    voter.has_voted = 0;
    voters[voter_count++] = voter;
    save_voters();
    printf("Voter registered successfully!\n");
}

void cast_vote() {
    if (!is_voting_open()) {
        printf("Voting is closed!\n");
        return;
    }
    char voter_id[10];
    printf("Enter your voter ID: ");
    scanf("%s", voter_id);
    int voter_index = -1;
    for (int i = 0; i < voter_count; i++) {
        if (strcmp(voters[i].voter_id, voter_id) == 0) {
            voter_index = i;
            break;
        }
    }
    if (voter_index == -1) {
        printf("Voter ID not found!\n");
        return;
    }
    if (voters[voter_index].has_voted) {
        printf("You have already voted!\n");
        return;
    }
    printf("Available Representatives:\n");
    for (int i = 0; i < rep_count; i++) {
        printf("%d. ID: %s, Name: %s\n", i + 1, reps[i].rep_id, reps[i].name);
    }
    int choice;
    printf("Enter the number of your choice: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > rep_count) {
        printf("Invalid choice!\n");
        return;
    }
    reps[choice - 1].vote_count++;
    voters[voter_index].has_voted = 1;
    save_voters();
    save_reps();
    save_votes();
    printf("Vote cast successfully! Exiting...\n");
    view_results();
    exit(0); // Exit after voting
}

void view_results() {
    printf("Current Voting Results:\n");
    for (int i = 0; i < rep_count; i++) {
        printf("ID: %s, Name: %s, Votes: %d\n",
               reps[i].rep_id, reps[i].name, reps[i].vote_count);
    }
}

int is_voting_open() {
    time_t now = time(NULL);
    return (now >= timeframe.start_time && now <= timeframe.end_time);
}

// Menus
void admin_menu() {
    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. Appoint Representative\n");
        printf("2. Set Voting Timeframe\n");
        printf("3. View Registered Voters\n");
        printf("4. View Results\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1: appoint_rep(); break;
            case 2: set_timeframe(); break;
            case 3: view_voters(); break;
            case 4: view_results(); break;
            case 5: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void voter_menu() {
    while (1) {
        printf("\nVoter Menu:\n");
        printf("1. Register\n");
        printf("2. Cast Vote\n");
        printf("3. View Results\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1: register_voter(); break;
            case 2: cast_vote(); break;
            case 3: view_results(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    }
}

int main() {
    // Load data from files
    load_voters();
    load_reps();
    load_votes();
    load_timeframe();

    while (1) {
        printf("\nMini Vote Casting System\n");
        printf("1. Admin Login\n");
        printf("2. Voter Menu\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (authenticate_admin()) {
                    admin_menu();
                } else {
                    printf("Incorrect password!\n");
                }
                break;
            case 2:
                voter_menu();
                break;
            case 3:
                printf("Exiting system.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
