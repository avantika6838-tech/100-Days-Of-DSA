/* Problem: Given a matrix, calculate the sum of its primary diagonal elements. The primary diagonal consists of elements where row index equals column index.

Input:
- First line: two integers m and n
- Next m lines: n integers each

Output:
- Print the sum of the primary diagonal elements

Example:
Input:
3 3
1 2 3
4 5 6
7 8 9

Output:
15
*/

#include <stdio.h>
int main(){
    
    int n, m, sum = 0;
    int i, j;
    int matrix[50][50];
    printf("Enter the order of matrix (row,column) = ");
    scanf("%d %d", &n, &m);

    if(n != m){
        printf("Matrix is not square.");
        return 0;
    }

    printf("Enter elements of Matrix (%d x %d)=\n",m,n);
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nThe matrix is= \n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
        printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < n; i++){
        sum += matrix[i][i];   
    }

    printf("The sum of main diagonal elements are = %d\n", sum);

    return 0;
}

/* Set Matrix Zeroes

Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.

Example 1:
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Example 2:
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 */

#include<stdio.h>
#include<stdbool.h>
int main(){
    
    int m, n;
    int i, j;
    int matrix[50][50];
    printf("Enter number of rows= ");
    scanf("%d", &m);
    printf("Enter number of columns= ");
    scanf("%d", &n);

    printf("Enter matrix elements= \n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nMatrix= \n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    bool firstRowZero = false;
    bool firstColZero = false;

    for(i = 0; i < m; i++){
        if(matrix[i][0] == 0){
            firstColZero = true;
            break;
        }
    }

    for(j = 0; j < n; j++) {
        if(matrix[0][j] == 0) {
            firstRowZero = true;
            break;
        }
    }

    for(i = 1; i < m; i++){
        for(j = 1; j < n; j++){
            if(matrix[i][j] == 0){
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    for(i = 1; i < m; i++){
        for(j = 1; j < n; j++){
            if(matrix[i][0] == 0 || matrix[0][j] == 0){
                matrix[i][j] = 0;
            }
        }
    }

    if(firstColZero){
        for(i = 0; i < m; i++){
            matrix[i][0] = 0;
        }
    }

    if(firstRowZero){
        for(j = 0; j < n; j++){
            matrix[0][j] = 0;
        }
    }

    printf("\nMatrix after setting zeroes= \n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
