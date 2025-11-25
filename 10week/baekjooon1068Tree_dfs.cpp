#include <stdio.h>
#include <vector>
using namespace std;

vector<int> graph[50]; 
// int visit[50]; // visit 배열 제거!
int n;      
int cnt = 0;

int dfs(int u, int v, int removeNode) {
    // 1. 제거할 노드라면 탐색하지 않고 즉시 리턴
    if (u == removeNode) {
        return 0;
    }

    // 2. 유효한 자식의 개수를 센다. (삭제후 변하는 리프노드를 구하기 위해)
    int validChildCount = 0;
    
    // u의 모든 인접 노드를 순회
    for (int i = 0; i < graph[u].size(); i++) {
        int w = graph[u][i];

         // 인접 노드 w가 부모 v가 아니고, 제거될 노드 removeNode도 아닌 경우에만 카운트
        if (w != v && w != removeNode) {
            validChildCount++;
        }
    }

    // 유효한 자식이 0개라면 리프노드가 될 것입니다.
    if (validChildCount == 0) {
        cnt++;
        return 0; 
    }
    
    // 4. 유효한 자식 노드만 골라서 DFS 재귀 호출
    for (int i = 0; i < graph[u].size(); i++) {
        int w = graph[u][i];
        
        if (w != v) { 
            dfs(w, u, removeNode);
        }
    }

    return 0;
}

int main() {
    int parent; // 변수명을 parent로 통일하는 것이 좋습니다.
    int root = -1;
    int removeNode;
    
    // 입력 처리
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &parent);
        if (parent == -1) {
            root = i; 
        } else {
            // 양방향 그래프 저장
            graph[i].push_back(parent);
            graph[parent].push_back(i);
        }
    }
    
    scanf("%d", &removeNode);

    // 예외 처리: 제거할 노드가 루트 노드인 경우
    if (root == removeNode) {
        printf("0\n");
        return 0;
    }

    // 루트 노드부터 DFS 시작
        dfs(root, -1, removeNode);

    printf("%d", cnt);

    return 0;
}