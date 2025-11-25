#include <stdio.h>
#include <vector>
#include <cmath> // sqrt 함수 사용
#include <algorithm> // sort 함수 사용
#include <utility>

using namespace std;

// 정밀도를 위해 long double 사용
typedef long double ld; 

// 우주신 좌표 구조체 (좌표 값이 크므로 long long 사용)
struct Position {
    long long x, y;
};

// 엣지 구조체 (가중치는 유클리드 거리이므로 ld 사용)
struct Edge {
    int u, v;         
    ld weight;    
};

int N, M;
vector<Position> pos;
vector<Edge> all_edges;

// ----------------------------------------------------
// 1. Union-Find 클래스
// ----------------------------------------------------

class UnionFind {
    vector<int> parent, rank;

public: 
    UnionFind(int n_size) {
        parent.resize(n_size + 1);
        rank.resize(n_size + 1, 0);
        for (int i = 1; i <= n_size; ++i) {
            parent[i] = i; 
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            return parent[x] = find(parent[x]); // 경로 압축
        }
        return x;
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false; // 이미 같은 집합 (사이클 발생)
        }
        
        // 랭크 기반 Union
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true; 
    }
};

// ----------------------------------------------------
// 2. 유클리드 거리 계산 함수
// ----------------------------------------------------

ld getDistance(int i, int j) {
    long long dx = pos[i].x - pos[j].x;
    long long dy = pos[i].y - pos[j].y;
    
    // dx*dx + dy*dy는 long long으로 계산 후 ld로 형변환
    return sqrt((ld)(dx * dx + dy * dy)); 
}

// ----------------------------------------------------
// 3. Kruskal 알고리즘
// ----------------------------------------------------

void kruskal(UnionFind& uf) {
    ld total_cost = 0.0;
    
    // 엣지 리스트를 가중치 기준으로 오름차순 정렬
    sort(all_edges.begin(), all_edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    int union_count = 0;
    for (const auto& edge : all_edges) {
        // N-1개의 엣지를 찾으면 종료
        if (union_count == N - 1) break;

        // unite가 true를 반환할 때만 비용 추가 (새로운 연결)
        if (uf.unite(edge.u, edge.v)) {
            total_cost += edge.weight;
            union_count++;
        }
    }

    // 결과 출력: 소수점 둘째 자리까지, long double은 %Lf 사용
    printf("%.2Lf\n", total_cost); 
}

// ----------------------------------------------------
// 4. Main 함수: 입력 처리 및 실행 로직
// ----------------------------------------------------

int main() {
    // N, M 입력. 정수는 %d 사용.
    if (scanf("%d %d", &N, &M) != 2) return 0;

    pos.resize(N + 1); 

    // 우주신 좌표 입력. long long은 %lld 사용.
    for (int i = 1; i <= N; i++) {
        if (scanf("%lld %lld", &pos[i].x, &pos[i].y) != 2) return 0;
    }

    // Union-Find 초기화
    UnionFind uf(N); 

    // 이미 연결된 M개의 통로 입력 및 Union-Find에 즉시 반영
    for (int i = 0; i < M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) return 0;
        uf.unite(u, v); // 이미 연결된 통로를 미리 합쳐 놓음
    }

    // 모든 가능한 엣지 생성 (완전 그래프)
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            ld dist = getDistance(i, j);
            all_edges.push_back({i, j, dist});
        }
    }
    
    // 크루스칼 알고리즘 실행
    kruskal(uf);
    
    return 0;
}