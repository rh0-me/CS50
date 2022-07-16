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
} pair;

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
void lock_pairs(void);
void print_winner(void);
bool is_Cycle(int i);
void traverse(int vertex, int startingVertex, bool *result);

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
    // TODO
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(candidates[k], name) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int j = 0; j < candidate_count - 1; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            preferences[ranks[j]][ranks[k]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO Bubble-Sort
    for (int h = 0; h < pair_count; h++)
    {
        bool swapped = true;
        for (int i = 0; i < pair_count - 1 - h; i++)
        {
            int next = i + 1;
            int strengthNext = preferences[pairs[next].winner][pairs[next].loser] - preferences[pairs[next].loser][pairs[next].winner];
            int strength = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            swapped = false;
            if (strength < strengthNext)
            {
                pair tmp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // lock pair
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (is_Cycle(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        bool isWinner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                isWinner = false;
            }
        }
        if (isWinner == true)
        {
            // check for edges
            isWinner = false;
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[i][j] == true)
                {
                    printf("%s\n", candidates[i]);
                    isWinner = true;
                    break;
                }
            }
            if (isWinner == true)
            {
                break;
            }
        }
    }
}

bool is_Cycle(int index)
{
    // traverse graph
    // go to next node
    // check if it has edges#
    bool result = false;
    traverse(pairs[index].loser, pairs[index].loser, &result);
    return result;
}

void traverse(int vertex, int startingVertex, bool *result)
{
    for (int j = 0; j < candidate_count; j++)
    {
        // traverse this edge
        if (locked[vertex][j] == true)
        {
            if (j == startingVertex)
            {
                *result = true;
                break;
            }
            else
            {
                traverse(j, startingVertex, result);
            }
        }
    }
    // it has no cycle
}