#include <stdio.h>
#include <algorithm> 
#include <vector>

using namespace std;

// dp[i] : i원으로 얻을 수 있는 최대 칼로리
int dp[10001]; 

int main() {
    int n, m;
    
    while (1) {
        int temp_n;
        float temp_m;
        
        // 입력 받기
        if (scanf("%d %f", &temp_n, &temp_m) != 2) break;   
        n = temp_n;
        m = (int)(temp_m * 100.0 + 0.5); // 돈을 정수로 변환

        if (n == 0 && m == 0) break;

        // 1차원이라서 초기화 속도가 엄청 빠름
        for (int i = 0; i <= m; i++) {
            dp[i] = 0;
        }

        // 사탕 입력 받으면서 바로 DP 계산 
        for (int i = 0; i < n; i++) {
            int c, p;
            float temp_p;
            scanf("%d %f", &c, &temp_p);
            p = (int)(temp_p * 100.0 + 0.5); // 가격

            // "돈(j)이 가격(p)보다 많으면, 사탕을 하나 더 사는 게 이득인가?" 확인
            for (int j = p; j <= m; j++) {
                dp[j] = max(dp[j], dp[j - p] + c);
            }
        }
        
        // 결과 출력
        printf("%d\n", dp[m]);
    }

    return 0;
}