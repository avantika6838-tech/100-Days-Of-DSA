/* Problem Statement
Given an array of candidate names where each name represents a vote cast for that candidate, determine the candidate who received the maximum number of votes. In case of a tie, return the lexicographically smallest candidate name.

Input Format
First line contains an integer n representing number of votes.
Second line contains n space-separated strings representing candidate names.

Output Format
Print the name of the winning candidate followed by the number of votes received.

Sample Input
13
john johnny jackie johnny john jackie jamie jamie john johnny jamie johnny john

Sample Output
john 4

Explanation
Both john and johnny receive 4 votes, but john is lexicographically smaller, so john is declared the winner.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparator for sorting strings
int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int n;
    scanf("%d", &n);

    char **votes = (char **)malloc(n * sizeof(char *));
    
    for (int i = 0; i < n; i++) {
        votes[i] = (char *)malloc(101 * sizeof(char));
        scanf("%s", votes[i]);
    }

    // Sort the votes
    qsort(votes, n, sizeof(char *), cmp);

    int maxVotes = 1, count = 1;
    char winner[101];
    strcpy(winner, votes[0]);

    for (int i = 1; i < n; i++) {
        if (strcmp(votes[i], votes[i - 1]) == 0) {
            count++;
        } else {
            if (count > maxVotes) {
                maxVotes = count;
                strcpy(winner, votes[i - 1]);
            }
            count = 1;
        }
    }

    // Check last candidate
    if (count > maxVotes) {
        maxVotes = count;
        strcpy(winner, votes[n - 1]);
    }

    printf("%s %d\n", winner, maxVotes);

    // Free memory
    for (int i = 0; i < n; i++) {
        free(votes[i]);
    }
    free(votes);

    return 0;
}
