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
void mergeSort(int array[], int l, int r);
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
    pair tempPairs[pair_count];

    for (int i = 0; i < pair_count; i++){
        strength[i] = preferences[pairs[i].winner][pairs[i].loser]
        - preferences[pairs[i].loser][pairs[i].winner];
        printf("Strength: %d\n", strength[i]);
        printf("%d", pairs[i].winner);
        printf("%d\n\n", pairs[i].loser);
    }

    int lower = 0;

    int upper = sizeof(strength) / sizeof(strength[0]);

    printf("\n\n\n");

    mergeSort(strength, lower, upper);

    for (int j = 0; j < pair_count; j++){
        printf("PRINT: %i\n", j);
        printf("Strength: %d\n", strength[j]);
        tempPairs[j].winner = pairs[strength[j] - 1].winner;
        tempPairs[j].loser = pairs[strength[j] - 1].loser;

        printf("Pairs: %d", pairs[strength[j] - 1].winner);
        printf("%d", pairs[strength[j] - 1].loser);

        printf("Temp: %d", tempPairs[j].winner);
        printf("%d\n", tempPairs[j].loser);
    }

    for (int k = 0; k < pair_count; k++){
        pairs[k].winner = tempPairs[k].winner;
        pairs[k].loser = tempPairs[k].loser;

        printf("%d", pairs[k].winner);
        printf("%d\n", pairs[k].loser);
    }

    // mergeSort(merge[], lower, upper);

    // merge finds strongest order based on pairs[i]

    // NewArray[i].winner = Pairs[merge[i]].winner

    // Make a new pair array

    // NEED TO SORT PAIRS ARRAY

    return;
}

void merge(int strength[], int lower, int mid, int upper){
    int leftArray = mid - lower + 1;
    int rightArray = upper - mid;

    int left[leftArray], right[rightArray];

    for(int i = 0; i < leftArray; i++){
        left[i] = strength[lower + i];
    }
    for(int j = 0; j < rightArray; j++){
        right[j] = strength[mid + 1 + j];
    }

    int lInd = 0, rInd = 0, sort = 1;

    while(lInd < leftArray && rInd < rightArray){
        if(left[lInd] <= right[rInd]){
            strength[sort] = left[lInd];
            lInd++;
        }else{
            strength[sort] = right[rInd];
            rInd++;
        }
        sort++;
    }

    while(lInd < leftArray){
        strength[sort] = left[lInd];
        lInd++;
        sort++;
    }

    while(rInd < rightArray){
        strength[sort] = left[rInd];
        rInd++;
        sort++;
    }
}

void mergeSort(int array[], int l, int r){
    if(l < r){
    int m = l + (r - l) / 2;

    mergeSort(array, l, m);
    mergeSort(array, m + 1, r);

    merge(array, l, m, r);
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