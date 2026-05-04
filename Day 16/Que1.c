/* Rotate Array

Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

Example 1:
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]

Example 2:
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]

*/

#include<stdio.h>
int main(){
    
    int n, k, i, j;
    int arr[50];
    int rotated[50];
    printf("Enter number of elements= ");
    scanf("%d", &n);

    printf("Enter the %d elements= ",n);
    for(i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    printf("Enter k (positions to rotate)= ");
    scanf("%d", &k);
    k = k % n;

    for(i = 0; i < n; i++){
        rotated[(i + k) % n] = arr[i];
    }

    printf("Rotated array= ");
    for(i = 0; i < n; i++){
        printf("%d ", rotated[i]);
    }
    printf("\n");

    return 0;
}
