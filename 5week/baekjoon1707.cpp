#include <stdio.h>
#include <vector>
using namespace std;

bool flag_bg = false;
vector<vector<int>> graph(20001); // 최대 정점의 개수만큼 생성
vector<int> visit(20001, -1); // 방문했는지 플래그를 저장

int dfs_bg(int u, int flag) {
    if (flag_bg == true) return 0; // 이중 그래프임이 밝혀지면 바로 반환

    int w;
    visit[u] = flag;
    flag = (flag + 1) % 2;

    for (int i = 0; i < graph[u].size(); i++) {
        w = graph[u][i];

        if (visit[w] == -1) 
            dfs_bg(w, flag);

        if (visit[w] == visit[u]) {
            flag_bg = 1;
            return 0;
        }
            
    }

    return 0;
}

int main() {
    int vertexNum, edgeNum; // Number of vertex, edge
    int T; // test case
    scanf("%d", &T);    
    
    while (T > 0) {
        scanf("%d %d", &vertexNum, &edgeNum);

        // 테스트케이스 마다 초기화
        for (int i = 0; i <= vertexNum; i++) { 
            graph[i].clear();
            visit[i] = -1;
        }
        flag_bg = false;

        int u, v;   // 간선 추가
        for (int i = 0; i < edgeNum; i++) {
            scanf ("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        for (int i = 1; i <= vertexNum; i++) {
            if (visit[i] == -1)
                dfs_bg(i, 0);
        }

        printf(flag_bg ? "NO\n" : "YES\n");

        T--; 
    }

    return 0;
}