#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
int K, V, E;
vector<int> graph[20001];
int visit[20001];
int flag_bg;
int res[5];
// 이분 그래프인지(1) 아닌지(0)
void init_visit()
{
    for (int i = 0; i < 20001; i++)
        visit[i] = -1;
}

void dfs_bg(int u, int flag)
{
    int w;
    visit[u] = flag;
    flag = (flag + 1) % 2; // flag 바꾸기:0->1, 1->0
    for (int i = 0; i < graph[u].size(); i++)
    {
        w = graph[u][i];
        if (visit[w] == -1)
            dfs_bg(w, flag);
        if (visit[w] == visit[u])
            flag_bg = 0;
    }
}

int main()
{
    // 1. 자료구조 및 데이터 입력
    int k, e, u, v;
    scanf("%d", &K); // # of test cases
    for (k = 0; k < K; k++)
    {
        init_visit();
        scanf("%d %d", &V, &E);
        // graph[v] 초기화
        for (v = 1; v <= V; v++)
        {
            graph[v].clear();
        }
        //// 확인용 출력
        // printf("[%d/%d]\n", k, K);
        // printf("V %d, E %d\n", V, E);
        for (e = 0; e < E; e++)
        { // # of edges
            scanf("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u); // undirected graph
            // printf("(%d, %d)\n", u, v); // 확인용 출력
        }
        // 2. graph에서의 dfs
        flag_bg = 1;
        for (v = 1; v <= V; v++)
        {
            if (visit[v] == -1)
                dfs_bg(v, 0);
        }
        // 3. 이분 그래프 판정
        res[k] = flag_bg;
    }
    for (k = 0; k < K; k++)
    {
        if (res[k])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}