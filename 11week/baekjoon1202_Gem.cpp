#include <stdio.h>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

priority_queue <int> pq_gem; // 오름차순 정렬
priority_queue <int, vector<int>, greater<int>> pq_Backpack; // 내림차순 정렬
pair<int, int> jew[30000];
int c[300000]; // 가방 용량
int n, k;

int profitSum = 0;

int greedy() {
    // 오름차 순으로 정렬
    sort(jew, jew + n);
    sort(c, c + k);

    priority_queue<int> pq;
    int myVal;
    
    int i, j = 0;
    // 용량이 작은 가방부터
    for (i = 0; i < k; i++) {
        // 가방에 담을 수 있는 보석 가격을 pq에 저장
        // 한번 큐에 들어간 보석은 다시 들어가면 안됨
        for (; j < n; j++) {
            if (c[i] < jew[i].first) {
                break;
            }
            pq.push(jew[j].second);
        }

        // pq의 top을 선택
        while (!pq.empty()) {
            myVal = pq.top();
            pq.pop();

            profitSum += myVal;
            break; // 하나만 닫고 끝냄
        }
    }

    return 0;
}

int main() {
    
    scanf("%d %d", &n, &k);

    // 보석 정보 입력
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &jew[i].first, &jew[i].second);   
    }

    // 가방 정보 입력
    for (int i = 0; i < k; i++) {
        scanf("%d", &c[i]); 
    }

    greedy();

    printf("%d", profitSum);


    return 0;
}