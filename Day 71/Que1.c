/*Problem Statement
Implement a hash table using quadratic probing with formula:

h(k, i) = (h(k) + i*i) % m

Input Format
Same as previous.

Output Format
Result of SEARCH operations.

Sample Input
7
4
INSERT 49
INSERT 56
SEARCH 49
SEARCH 15

Sample Output
FOUND
NOT FOUND

Explanation
Collisions resolved using i² jumps.
*/

#include <stdio.h>
#include <string.h>

#define EMPTY -1

int hashTable[1000];

void insert(int key, int m){
    int h = key % m;

    for(int i = 0; i < m; i++){
        int idx = (h + i * i) % m;

        if(hashTable[idx] == EMPTY){
            hashTable[idx] = key;
            return;
        }
    }
}


int search(int key, int m){
    int h = key % m;

    for(int i = 0; i < m; i++){
        int idx = (h + i * i) % m;

        if(hashTable[idx] == EMPTY){
            return 0; 
        }

        if(hashTable[idx] == key){
            return 1; 
        }
    }
    return 0;
}

int main() {
    int m, q;
    scanf("%d", &m);
    scanf("%d", &q);

    for (int i = 0; i < m; i++){
        hashTable[i] = EMPTY;
    }

    while (q--){
        char op[10];
        int key;

        scanf("%s %d", op, &key);

        if(strcmp(op, "INSERT") == 0){
            insert(key, m);
        }else if(strcmp(op, "SEARCH") == 0){
            if(search(key, m)){
                printf("FOUND\n");
            }else{
                printf("NOT FOUND\n");
            }
        }
    }

    return 0;
}
