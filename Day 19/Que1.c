/*Problem: Given an array of integers, find two elements whose sum is closest to zero.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the pair of elements whose sum is closest to zero

Example:
Input:
5
1 60 -10 70 -80
Output:
-10 1

Explanation: Among all possible pairs, the sum of -10 and 1 is -9, which is the closest to zero compared to other pairs.
*/

#include<stdio.h>
int main(){

    int n, i, j;
    int arr[50];
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    int min_sum = arr[0] + arr[1];
    int num1 = arr[0]; 
    int num2 = arr[1];

    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            int sum = arr[i] + arr[j];

            int temp_sum = sum;
            if(temp_sum < 0){
                temp_sum = -temp_sum;
            }

            int temp_min = min_sum;
            if(temp_min < 0){
                temp_min = -temp_min;
            }

            if(temp_sum < temp_min){
                min_sum = sum;
                num1 = arr[i];
                num2 = arr[j];
            }
        }
    }

    printf("%d %d\n", num1, num2);

    return 0;
}
