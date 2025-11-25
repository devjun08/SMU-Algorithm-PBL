#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, W;
int INF = 2100000000;
vector<pair<int, int>> graph[501];
long long dist[501];
int pre[501];
int cycleBool = false;

int bellman_ford(int s) {
    // pre, dist 초기화
    for (int i = 1; i <= N; i++) {
        pre[i] = -1;
        dist[i] = INF;
    }
    cycleBool = false;

    // 시작 노드 값 설정
    pre[s] = -1;
    dist[s] = 0;

    int u, v, luv;
    for (int i = 1; i < N; i++) { // i, 도착까지의 간선의 수
        for (int u = 1; u <= N; u++) {
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
    for (int u = 1; u <= N; u++) {
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
    int s, e, t; 
    pair<int, int> p;
    int tc;

    scanf("%d", &tc);
    for (int j = 1; j <= tc; j++) {
        scanf("%d %d %d", &N, &M, &W); 

        // 그래프 초기화
        for (int i = 1; i <= N; i++) {
            graph[i].clear();
        }
        
        // 도로 간선 추가
        for (int i = 1; i <= M; i++) {
            scanf("%d %d %d", &s, &e, &t);
            // 도로는 방향이 없다. 반면 웜홀은 방향이 있다.
            graph[s].push_back(make_pair(e, t));
            graph[e].push_back(make_pair(s, t));
        }

        // 웜홀 간선 추가
        for (int i = 1; i <= W; i++) {
            scanf("%d %d %d", &s, &e, &t);
            graph[s].push_back(make_pair(e, -t)); // -100000 ~ 0
        }

        for (int i = 1; i <= N; i++) {
            sort(graph[i].begin(), graph[i].end());
        }

        bellman_ford(1);

        // 음수 사이클이 있는지에 따라 출력이 다름.
        if (cycleBool == false) {
            printf("NO\n");
        } else if (cycleBool == true) {
            printf("YES\n");
        }

        printf("\n");
    }
    

    return 0;
}