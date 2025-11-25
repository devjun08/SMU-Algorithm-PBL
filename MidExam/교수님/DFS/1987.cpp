#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
vector<int> graph[20];
int visit[26];
int R, C;
int curr_dist; // 현재 path의 길이
int max_dist;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y)
{
    int nx, ny;
    visit[graph[x][y]] = 1;
    curr_dist++;
    for (int i = 0; i < 4; i++)
    {
        nx = x + dx[i];
        ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= R || ny >= C)
            continue;
        if (visit[graph[nx][ny]] == 0)
        {
            dfs(nx, ny);
        }
    }
    max_dist = (max_dist < curr_dist) ? curr_dist : max_dist;
    curr_dist--;
    visit[graph[x][y]] = 0;
}

int a2i(char c)
{
    return (int)(c - 'A'); // c - 65
                           // A->0, B->1, ...,
}

int main()
{
    // 1. 자료구조 및 데이터 입력
    int i, j;
    char str[256];
    scanf("%d %d", &R, &C);
    for (i = 0; i < R; i++)
    {
        scanf("%s", &str);
        for (j = 0; j < C; j++)
        {
            // graph[i][j] = (int)str[j];
            graph[i].push_back(a2i(str[j])); // char -> int
        }
    }
    // 확인용 출력
    for (i = 0; i < R; i++)
    {
        for (j = 0; j < C; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    
    // 2. map graph에서의 dfs 구현
    // 3. 최장 길이의 문자열 찾기 구현
    curr_dist = 0;
    dfs(0, 0);
    printf("Result: \n");
    printf("%d \n", max_dist);
    return 0;
}