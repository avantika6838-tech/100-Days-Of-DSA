/* You are given an array arr[] of size n - 1 that contains distinct integers in the range from 1 to n (inclusive). 
This array represents a permutation of the integers from 1 to n with one element missing. 
Your task is to identify and return the missing element.
*/
// Solution.c
long long missingNum(int arr[], int size) {
    long long n = (long long)size + 1;  
    long long totalSum = n * (n + 1) / 2;
    long long arrSum = 0;

    for (int i = 0; i < size; i++) {
        arrSum += arr[i];
    }

    return (int)(totalSum - arrSum);
}
