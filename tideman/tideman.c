#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void merge(int strength[], int lower, int mid, int upper);
void mergeSort(int array[], int length);
void mergeRecursion(int a[], int l, int r);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(name, candidates[i]) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count - 1; i++){
        for(int j = i + 1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other

void add_pairs(void)
{
    for(int i = 0; i < candidate_count - 1; i++){
        for(int j = i + 1; j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if(preferences[i][j] < preferences[j][i]){
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength[pair_count];
    int tempStrength[pair_count];
    pair tempPairs[pair_count];

    for (int i = 0; i < pair_count; i++){
        strength[i] = preferences[pairs[i].winner][pairs[i].loser]
        - preferences[pairs[i].loser][pairs[i].winner];
        tempStrength[i] = strength[i];
    }

    int length = sizeof(strength) / sizeof(strength[0]);

    return;
}

void merge(int a[], int length){
    mergeRecursion(a, 0, length - 1);
}

void mergeRecursion(int a[], int l, int r){
    if(l < r){
        int m = l + (r - l) /2;

        mergeRecursion(a, l, m);
        mergeRecursion(a, m + 1, r);

        mergeSort(a, l, m, r);
    }
}

void mergeSort(int a[], int l, int m, int r){
    int lLength = m - l + 1;
    int rLength = r - m;

    int tempLeft[lLength];
    int tempRight[rLength];

    int i, j, k;

    for(int i = 0; i <lLength; i++){
        tempLeft[i] = a[l + i];
    }
    for(int i = 0; i <rLength; i++){
        tempRight[i] = a[m + 1 + i];
    }

    for(i = 0, j = 0, k = l; k <= r; k++){
        if((i < lLength) && (j >= rLength) || tempLeft[i] <= tempRight[j]){
            a[k] = tempLeft;
            i++;
        }else{
            a[k] = tempRight[j];
            j++;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}