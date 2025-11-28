#include <stdio.h>
#include <utility>
#include <algorithm> // max 함수
#include <cstring>   

using namespace std;

// DP 테이블 크기 주의 (메모리 약 200MB 사용)
int dp[10001][5005]; 

int n, m; 
pair<int, int> candy[5001]; 

void init_dp() {
    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= n + 1; j++) {
            dp[i][j] = -1;
        }
    }
}

int cal(int currentMoney, int k) { 
    // 1. 메모이제이션 체크
    if (dp[currentMoney][k] != -1) {
        return dp[currentMoney][k];
    }

    // 2. Base Case: 사탕 종류를 다 봤을 때
    if (k > n) {
        return 0;
    }
    
    int price_k = candy[k].second;
    int calory_k = candy[k].first;

    // 3. 경우의 수 A: 이 사탕(k)을 안 사고 넘어가는 경우
    // k + 1로 이동
    int result = cal(currentMoney, k + 1); 
    
    // 4. 경우의 수 B: 이 사탕(k)을 하나 사는 경우
    // 돈이 충분하다면 산다.
    // ★중요★: 샀으면 'k + 1'이 아니라 다시 'k'를 호출해서 또 살 수 있게 함 (이게 for문을 대체함)
    if (currentMoney >= price_k) {
        int buy_current = cal(currentMoney - price_k, k) + calory_k;
        result = max(result, buy_current);
    }
    
    // 5. 저장 및 리턴
    return dp[currentMoney][k] = result;
}

int main() {
    int a;
    float b;

    while (1) {
        if (scanf("%d %f", &a, &b) != 2) break;
        n = a;
        m =(int)(b * 100.0 + 0.5);

        if (n == 0 && m == 0) break;

        for (int i = 1; i <= n; i++) {
            if (scanf("%d %f", &a, &b) != 2) break;
            candy[i] = { a, (int)(b * 100 + 0.5) };
        }
        
        init_dp(); 
        printf("%d\n", cal(m, 1));
    }

    return 0;
}