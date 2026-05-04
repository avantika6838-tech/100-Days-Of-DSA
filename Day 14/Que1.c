* Problem: Write a program to check whether a given square matrix is an Identity Matrix.
 An identity matrix is a square matrix in which all diagonal elements are 1 and all non-diagonal elements are 0.

Input:
- First line: integer n representing number of rows and columns
- Next n lines: n integers each representing the matrix elements

Output:
- Print "Identity Matrix" if the matrix satisfies the condition
- Otherwise, print "Not an Identity Matrix"

Example:
Input:
3
1 0 0
0 1 0
0 0 1

Output:
Identity Matrix

*/

#include<stdio.h>
int main(){

    int n;
    int matrix[50][50];
    int i, j;
    int isIdentity = 1;   

    printf("Enter size of matrix (n x n)= ");
    scanf("%d", &n);

    printf("Enter matrix elements= \n");
    for(i = 0; i < n; i++){
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

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i == j){
                if(matrix[i][j] != 1){
                    isIdentity = 0;
                    break;
                }
            }
            else{
                if(matrix[i][j] != 0){
                    isIdentity = 0;
                    break;
                }
            }
        }
        if(isIdentity == 0)
            break;
    }

    if(isIdentity == 1){
        printf("Identity Matrix\n");
    }else{
        printf("Not an Identity Matrix\n");
    }

    return 0;
}


/* Rotate Image

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
DO NOT allocate another 2D matrix and do the rotation.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
*/

#include <stdio.h>

int main(){
    int n;
    int matrix[50][50];
    int i, j, temp;

    printf("Enter size of matrix (n x n)= ");
    scanf("%d", &n);

    printf("Enter matrix elements= \n");
    for(i = 0; i < n; i++){
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

    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n / 2; j++){
            temp = matrix[i][j];
            matrix[i][j] = matrix[i][n - 1 - j];
            matrix[i][n - 1 - j] = temp;
        }
    }

    printf("\nRotated matrix= \n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
