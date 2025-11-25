#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int cnt = 0;
int n_cube;
int A[20]; // 큐브 크기
int B[20]; // 큐브 개수

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void dnc(int len, int wid, int hei)
{
    /* 1. degenerate case -> conquer */
    /* length == 0 or width == 0 or height == 0 */
    if (len == 0 || wid == 0 || hei == 0)
        return;
    int i;
    int a = -1; // 가장 큰 큐브의 사이즈
    /* 2. divide */
    /* 1) 박스를 채울 수 있는 가장 큰 cube를 찾고 cnt++ */
    int my_min = min(len, min(wid, hei));
    for (i = n_cube - 1; i >= 0; i--)
    {
        if (A[i] <= my_min && B[i] > 0)
        {
            a = A[i];
            cnt++;  // 채우는 큐브 카운트
            B[i]--; // 개수 감소
            break;
        }
    }
    if (a == -1)
    {
        cnt = -1;
        return;
    }
    /* 2) 박스를 4분할 함 */
    // (L - a, W, H)
    dnc(len - a, wid, hei);
    // (a, W - a, a)
    dnc(a, wid - a, a);
    // (a, W, H - a)
    dnc(a, wid, hei - a);
    /* 3. combine */
}

int main()
{
    // 1. 입력 받기
    int len, wid, hei;
    scanf("%d %d %d", &len, &wid, &hei);
    scanf("%d", &n_cube);
    int i, k;
    for (i = 0; i < n_cube; i++)
    {
        scanf("%d %d", &k, &B[i]); // 큐브 크기, 개수
        A[i] = pow(2, k);
    }
    // 확인용 출력
    // printf("\n%d %d %d \n", len, wid, hei);
    // printf("%d \n", n_cube);
    // for (i = 0; i < n_cube; i++) {
    // printf("A[%d]: %d, B[%d]: %d \n", i, A[i], i, B[i]);
    //}
    // 2. 박스 채울 가장 큰 큐브 찾고 cnt++
    dnc(len, wid, hei);
    // 3. 출력
    printf("%d", cnt);
    return 0;
}