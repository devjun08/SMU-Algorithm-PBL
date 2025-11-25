// 교수님 코드 복습해라 ㅅㅂ

#include <stdio.h>
#include <stdlib.h>

char** board;
int cnt = 0; 

void dfs() {
    return;
}

void main() {
    int r, c;
    scanf("%d %d", &r, &c); 
    board = (char**)malloc(r * sizeof(char*));

    for (int i = 0; i < r; i++) {
        board[i] = (char*)malloc(r * sizeof(char));
        scanf("%s", board[i]);
        printf("%s\n", board[i]);
    }

    


    return;
}