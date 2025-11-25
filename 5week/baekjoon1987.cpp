#include <stdio.h>

char board[20][20];
int visit[26] = { 0 }; // idx 0이 대문자 A
int R, C;
int count = 0; // current count
int max = -1;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int char2int(int x) { // A = 0 ... Z = 25 으로 변환
    int asc = x - 65;

    return asc;
}

int dfs(int x, int y) {
    int nx, ny;
    visit[char2int(board[x][y])] = 1; // 알파벳에 따른 이미 방문한 알파벳을 표시
    count++;

    for (int i = 0; i < 4; i++) { 
        nx = x + dx[i]; // 상하좌우 좌표계산
        ny = y + dy[i];

        if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue; // 맵 밖으로 나가면 continue

        if (visit[char2int(board[nx][ny])] == 0) dfs(nx, ny); // dfs 탐색
    }

    max = (count > max) ? count : max; // max값을 경신
    
    count--; // 카운트 값을 줄임
    visit[char2int(board[x][y])] = 0;

    return 0;
}

int main() {
    char my_str[256];
    // input
    scanf("%d %d", &R, &C);

    for (int i = 0; i < R; i++) {
        scanf("%s", board[i]);
    }

    // dfs
    dfs(0, 0);

    printf("%d", max);

    return 0;
}