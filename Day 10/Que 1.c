/*
Problem: Read a string and check if it is a palindrome using two-pointer comparison.

Input:
- Single line: string s

Output:
- Print YES if palindrome, otherwise NO

Example:
Input:
level

Output:
YES

Explanation: String reads same forwards and backwards
*/
#include <stdio.h>
#include <string.h>

int main() {
    char s[1001];          
    scanf("%s", s);
    int left = 0;
    int right = strlen(s) - 1;
    
    int is_palindrome = 1;   

    while (left < right) {
        if (s[left] != s[right]) {
            is_palindrome = 0;
            break;
        }
        left++;
        right--;
    }

    if (is_palindrome) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
