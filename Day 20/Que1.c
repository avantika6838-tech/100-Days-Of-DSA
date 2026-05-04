/* Problem: Given an array of integers, count the number of subarrays whose sum is equal to zero.

Input:
- First line: integer n
- Second line: n integers

Output:
- Print the count of subarrays having sum zero

Example:
Input:
6
1 -1 2 -2 3 -3

Output:
6

Explanation: A subarray is a continuous part of the array. 
For the input array 1 -1 2 -2 3 -3, the following subarrays have sum zero: 
[1, -1], [2, -2], [3, -3], [1, -1, 2, -2], [2, -2, 3, -3], and [1, -1, 2, -2, 3, -3]. 
Since there are 6 such subarrays, the output is 6.
*/

#include<stdio.h>
int main(){

    int n, i, j;
    int arr[50];
    int count = 0, sum;

    printf("Enter n = ");
    scanf("%d", &n);

    printf("Enter elements = ");
    for(i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    for(i = 0; i < n; i++){
        sum = 0;
        
        for(j = i; j < n; j++){
            sum = sum + arr[j];

            if(sum == 0){
                count++;
            }
        }
    }

    printf("Number of subarrays with sum 0 = %d", count);

    return 0;
}
