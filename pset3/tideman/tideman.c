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
void lock_pairs(void);
void print_winner(void);
bool check_loop(int node);
bool doorloop_loop(int node, bool checked[]);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
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
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            // coördinaten van de huidige en volgende paren, die vergeleken zullen worden.
            int x1 = pairs[j].winner;
            int x2 = pairs[j + 1].winner;
            int y1 = pairs[j].loser;
            int y2 = pairs[j + 1].loser;
            
            // het verschil van beide paren, die vergeleken zullen worden.
            int diff1 = preferences[x1][y1] - preferences[y1][x1];
            int diff2 = preferences[x2][y2] - preferences[y2][x2];

            // Vergelijk de grootte van het verschil. Indien de volgende groter is, switch beide paren.
            if (diff2 > diff1)
            {
                pair mem = pairs[j + 1];
                pairs[j + 1] = pairs[j];
                pairs[j] = mem;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Maak een connectie, ongeacht of het een cycle zou vormen of niet.
        locked[pairs[i].winner][pairs[i].loser] = true;
        
        // Wanneer we deze connectie toevoegen, controleren of er een cycle is. Zoja, connectie weer verwijderen.
        if (check_loop(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}


bool check_loop(int node)
{
    // checked houdt bij waar ik reeds geweest ben
    bool checked[candidate_count];

    // checked initialiseren op 'False'
    for (int i = 0; i < candidate_count; i++)
    {
        checked[i] = false;
    }

    //int node is de coördinaat om alle nodes te vinden gekoppeld aan de winnaar van de te checken pair.
    return doorloop_loop(pairs[node].winner, checked);
}


bool doorloop_loop(int node, bool checked[])
{
    // Als ik op deze node reeds geweest ben, is de cycle rond. Return true;
    if (checked[node] == true)
    {
        return true;
    }

    // Aangeven dat ik langs deze node passeer.
    checked[node] = true;

    for (int i = 0; i < candidate_count; i++)
    {
        // Check volgende node of het een cycle vormt. 
        bool next_node = locked[node][i] && doorloop_loop(i, checked);
        
        // Indien het een cycle vormt, return true
        if (next_node)
        {
            return true;
        }
    }
    
    // Indien geen cycle, return false
    return false;
}


// Print the winner of the election
void print_winner(void)
{
    // Winner is standaard true. Vervolgens overlopen we alle waarden van 'Locked'. De meeste nodes gaan winner in false veranderen behalve 1. De winnaar
    bool winner;
    // winner_index is de i-waarde van de enige echte winnaar
    int winner_index;

    for (int i = 0; i < candidate_count; i++)
    {
        winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // Indien er een pijl eindigt in deze node, is het niet de winnaar.
            if (locked[j][i] == true)
            {
                winner = false;
            }
        }
        if (winner)
        {
            winner_index = i;
        }
    }

    printf("%s\n", candidates[winner_index]);

    return;
}