#include <stdio.h>
#include <math.h>

int N, r, c;
int coordinate;

int dnc(int N, int r, int c) {
    // degenerate Case
    if (N == 1) {
        if (r < 1 && c >= 1) coordinate += 1; // 1사분면
        else if (r < 1 && c < 1) coordinate += 0; // 2사분면
        else if (r >= 1 && c < 1) coordinate += 2; // 3사분면
        else if (r >= 1 && c >= 1) coordinate += 3; // 4사분면

        return 0;
    }
    
    // divide 
    int nMinus1 = (int)pow(2, N-1); // 2**(N-1)
    int box = nMinus1 * nMinus1; // 2**(N-1)by 행렬의 원소의 개수

    if (r < nMinus1) { // r이 2**(N-1) 보다 작은 경우 1 or 2사분면에 위치한다.
        if (c >= nMinus1) { // 1사분면에 위치한다.
            coordinate += box * 1;
            dnc(N-1, r, c - nMinus1);
        } else { // 2사분면에 위치한다.
            coordinate += box * 0;
            dnc(N-1, r, c);
        }
    } else if (r >= nMinus1) { // r이 2**(N-1) 보다 크거나 같은 경우 3 or 4사분면에 위치한다.
        if (c < nMinus1) { // 3사분면에 위치한다.
            coordinate += box * 2; 
            dnc(N-1, r - nMinus1, c);          
        } else { // 4사분면에 위치한다.
            coordinate += box * 3;
            dnc(N-1, r - nMinus1, c - nMinus1);
        }
    }

    return 0;
}

int main() {
    // input N r c
    scanf("%d %d %d", &N, &r, &c);
    coordinate = 0;
    //coordinate = pow(2, N) * pow(2, N) - 1; // 2**N by 2**N의 행렬이 있다고 했을때 마지막 방문하는 원소의 순서
    
    dnc(N, r, c);

    printf("%d", coordinate);

    
    return 0;
}