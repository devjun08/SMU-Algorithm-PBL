#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

#define MAX_NUM 50

int N, M;

struct QueueItem {
    int y, x, dist;
};

// map graph
char map[MAX_NUM][MAX_NUM];
bool visit[50][50];
vector <pair<int, int>> verticies; // s, k의 좌표 x, y

// sk graph
vector <pair<int, int>> skgraph[10000]; // 각각의 버텍스에 대해서 어떤 것과 연결을 가지고 있는지


// sk그래프에서 사용할 w 구하기 <= BFS
int get_dist(int x1, int y1, int x2, int y2) {
    int vx, vy; // current (현재)
    int nx, ny; // next (다음)
    int distance; // distance
    queue<QueueItem> q; // 큐에는 {x, y} 순서로 저장됨 (q.front().first = x, q.front().second = y)

    // dx는 X축(열) 변화, dy는 Y축(행) 변화
    int dx[4] = {-1, 0, 0, 1}; 
    int dy[4] = {0, -1, 1, 0};

    int i, j;
    // dist 초기화 (MAX_NUM이 50이므로 50x50 기준으로 초기화)
    for (i = 0; i < N; i++) { // N이 실제 맵 크기입니다.
        for (j = 0; j < N; j++) {
            visit[i][j] = false;
        }
    }
    
    // 시작 지점 설정
    // x1, y1을 매개변수 순서대로 받지만, dist 배열에는 [y][x] 순서로 접근해야 함.
    q.push({y1, x1, 0}); 
    visit[y1][x1] = true; // dist[y][x] = 0

    // dist 구하기 (BFS)
    while (!q.empty()) {
        // 큐에서 현재 좌표 추출 (first=x, second=y)
        vx = q.front().x;  // current x
        vy = q.front().y; // current y
        distance = q.front().dist; // current distance
        q.pop();

        // 목표 지점에 도달한 경우 즉시 반환
        if (vx == x2 && vy == y2) {
            return distance; // dist[y][x] 반환
        }

        for (i = 0; i < 4; i++) {
            nx = vx + dx[i]; // next x
            ny = vy + dy[i]; // next y

            // 1. 맵 범위 체크
            if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
                continue;
            }
            
            // 2. 벽('1') 체크
            if (map[ny][nx] == '1') { // map[y][x] 접근
                continue;
            }

            // 3. 미방문(dist가 -1) 체크 및 큐에 추가
            if (visit[ny][nx] == false) { // dist[다음 y][다음 x] 확인
                q.push({ny, nx, distance + 1});
                visit[ny][nx] = true; // dist[y][x] = true
            }
        }
    }
    
    // 목표 지점에 도달하지 못한 경우
    return -1;
}

// 프림 알고리즘 구현
long long prim_mst() {
    // 1. 최소 힙(Min-Heap)을 구현할 우선순위 큐 정의
    // pair<int, int> : {가중치, 정점 인덱스}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 2. MST에 정점이 포함되었는지 체크할 배열
    int v_count = verticies.size();
    vector<bool> visited(v_count, false);

    long long total_weight = 0;
    int edge_count = 0; // MST에 포함된 간선의 개수 (v_count - 1이 될 때까지)

    // 3. 임의의 시작점 설정 (S가 verticies[0]에 있으므로 0번 정점에서 시작)
    pq.push({0, 0}); // {가중치 0, 정점 인덱스 0}

    while (!pq.empty()) {
        int w = pq.top().first;
        int u = pq.top().second; // 현재 선택된 정점 인덱스
        pq.pop();

        // 4. 이미 MST에 포함된 정점이면 건너뜀
        if (visited[u]) continue;
        
        // MST에 정점 포함
        visited[u] = true;
        total_weight += w;
        edge_count++;

        // MST에 포함된 간선이 정점 개수 - 1이면 종료
        if (edge_count == v_count) break;

        // 5. 현재 정점 u와 연결된 모든 간선 검토
        int num_edges = skgraph[u].size(); // 현재 정점 u에 연결된 간선의 총 개수
        for (int i = 0; i < num_edges; ++i) {
            // skgraph[u][i]는 {가중치, 이웃 정점 인덱스} 형태의 pair입니다.
            int next_w = skgraph[u][i].first;
            int v = skgraph[u][i].second; // 이웃 정점 인덱스

            // 이웃 정점 v가 아직 MST에 포함되지 않았다면
            if (!visited[v]) {
            // 간선을 우선순위 큐에 추가
            pq.push({next_w, v});
            }
        }
    }
    
    // MST가 모든 정점을 포함하는지 확인 (edge_count == v_count가 되어야 함)
    // 만약 MST가 연결되지 않았다면 (경로 -1을 제대로 처리했다면 이럴 일은 없지만, 안전을 위해 체크)
    if (edge_count != v_count) {
        return -1; // 모든 K를 연결할 수 없는 경우
    }

    return total_weight;
}

int main() {
    scanf("%d %d", &N, &M);

    // 1. map 그래프 구축
    int i, j;
    char str[100];
    for (i = 0; i < N; i++) {
        scanf("%s", str);
        for (j = 0; j < N; j++) {
            map[i][j] = str[j];

            if (str[j] == 'S') {
                verticies.push_back( { i, j } ); 
            } else if (str[j] == 'K') {
                verticies.push_back( { i, j } );
            }
        }
    }

    /*
    // map 그래프 테스트
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
    */

    // 2. sk 그래프 구축
    int n = verticies.size();
    
    for (i = 0; i < n; i++) {
        skgraph[i].clear();
    }

    // 3. sk의 edge의 cost 계산 <= bfs
    int w;
    int x1, y1, x2, y2;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            // weight i, j 거리
            x1 = verticies[i].second; 
            y1 = verticies[i].first;
            x2 = verticies[j].second;
            y2 = verticies[j].first;
            w = get_dist(x1, y1, x2, y2);

            if (w != -1) { // ⬅️ w가 -1이 아닐 때만 간선을 추가함
            skgraph[i].push_back({w, j});
            skgraph[j].push_back({w, i});
            }
        }
    }

    // 4. mcst 생성 - Prim 알고리즘 호출
    long long result = prim_mst();

    // 5. 결과 출력
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%lld\n", result);
    }

    return 0;
}