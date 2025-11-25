#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int INF = 2100000000;
vector<pair<int, int>> graph[501];
long long dist[501];
int pre[501];
int cycleBool = false;

int bellman_ford(int s) {
    // pre, dist 초기화
    for (int i = 1; i <= n; i++) {
        pre[i] = -1;
        dist[i] = INF;
    }
    cycleBool = false;

    // 시작 노드 값 설정
    pre[s] = -1;
    dist[s] = 0;

    int u, v, luv;
    for (int i = 1; i < n; i++) { // i, 도착까지의 간선의 수
        for (int u = 1; u <= n; u++) {
            for (int k = 0; k < graph[u].size(); k++) {
                v = graph[u][k].first;
                luv = graph[u][k].second;

                if (dist[u] != INF && dist[v] > dist[u] + luv) {
                    dist[v] = dist[u] + luv;
                    pre[v] = u;
                }
            }
        }
    }

    // negative cycle 확인 (값이 계속 줄어드면 존재하는 것임)
    for (int u = 1; u <= n; u++) {
        for (int  k = 0; k < graph[u].size(); k++) {
            v = graph[u][k].first;
            luv = graph[u][k].second;

            if (dist[u] != INF && dist[v] > dist[u] + luv) {
                cycleBool = true;
            }
        }
    }

    return 0;
}

int main() {
    int u, v, w; 
    pair<int, int> p;

    scanf("%d %d", &n, &m); // 수정 

        // 그래프 초기화
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
        }
        
        // 그래프 간선 추가
        for (int i = 1; i <= m; i++) {
            scanf("%d %d %d", &u, &v, &w);
            graph[u].push_back(make_pair(v, w));
        }

        for (int i = 1; i <= n; i++) {
            sort(graph[i].begin(), graph[i].end());
        }

        bellman_ford(1);

        // 음수 사이클이 있는지에 따라 출력이 다름.
        if (cycleBool == false) {
            for (int i = 2; i <= n; i++) { // 2번부터 출력!!
                if (dist[i] == INF) printf("-1\n"); // i번째 도시에 갈 방법이 없다면!
                else printf("%lld\n", dist[i]);
            }
        } else if (cycleBool == true) {
            printf("-1\n");
        }

    return 0;
}