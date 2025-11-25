#include <stdio.h>
#include <math.h> // pow 함수 사용을 위해 포함

int dnc(int n, int x, int y) {
    /* 1. degenerate case -> conquer */
    /* n == 1 */
    if (n == 1) {
        if (x == 0 && y == 0)
            return 0;
        else if (x == 0 && y == 1)
            return 1;
        else if (x == 1 && y == 0)
            return 2;
        else if (x == 1 && y == 1)
            return 3;
    }

    /* 2. divide */
    /* half -> 2N-1 * 2N-1*/
    // d는 한 변의 길이 2^n에서 절반인 2^(n-1)을 의미
    int d = (int)pow(2, n - 1); // pow는 double을 반환하므로 int로 형변환

    /* x, y의 위치 다시 계산 */
    int nx = x;
    int ny = y;

    /* offset 계산 */
    int offset = 0;
    
    // 4개의 사분면으로 분할
    
    // UL (Upper Left, 좌상단)
    if (x < d && y < d) { 
        offset = 0;
    }
    // UR (Upper Right, 우상단)
    else if (x < d && y >= d) { 
        offset = d * d;
        ny = y - d; // ny: 새로운 사분면 내의 y 좌표
    }
    // DL (Down Left, 좌하단)
    else if (x >= d && y < d) { 
        offset = 2 * d * d;
        nx = x - d; // nx: 새로운 사분면 내의 x 좌표
    }
    // DR (Down Right, 우하단)
    else if (x >= d && y >= d) { 
        offset = 3 * d * d;
        nx = x - d; // nx: 새로운 사분면 내의 x 좌표
        ny = y - d; // ny: 새로운 사분면 내의 y 좌표
    }

    /* 3. combine */
    /* offset을 더하기 */
    // 현재 사분면의 시작 인덱스(offset)에 축소된 문제의 결과(재귀 호출)를 더함
    return offset + dnc(n - 1, nx, ny);
}

int main() {
    int n, x, y;

    // n: 2^n x 2^n 배열 크기, x, y: 찾고자 하는 좌표
    scanf("%d %d %d", &n, &x, &y); 
    
    int res = dnc(n, x, y);
    
    // printf("%d %d %d\n", n, x, y); // 확인용 (주석 처리됨)

    printf("%d", res); // 최종 결과 출력

    return 0;
}