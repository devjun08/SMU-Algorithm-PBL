#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n;
int **arr;
int cnt[3];

bool allSame(int xs, int xe, int ys, int ye)
{
    int temp = arr[xs][ys];

    for (int i = xs; i <= xe; i++)
    {
        for (int j = ys; j <= ye; j++)
        {
            if (temp != arr[i][j])
            {
                return false;
            }
        }
    }

    if (temp == -1)
        cnt[0]++;
    else if (temp == 0)
        cnt[1]++;
    else if (temp == 1)
        cnt[2]++;

    return true;
}

int dnc(int xs, int xe, int ys, int ye)
{
    // degenrate case
    if (xs == xe)
    {
        if (arr[xs][ys] == -1)
            cnt[0]++;
        else if (arr[xs][ys] == 0)
            cnt[1]++;
        else if (arr[xs][ys] == 1)
            cnt[2]++;

        return 0;
    }

    bool same = allSame(xs, xe, ys, ye); // 같은 값인지 확인
    if (same == true)
        return 0;

    // divide
    int length = (xe - xs + 1) / 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dnc(xs + i * length, xs + (i + 1) * length - 1, 
                ys + j *length, ys + (j + 1) * length -1);
        }
    }

    return 0;
}

int main()
{
    // 입력 처리 및 동적할당
    scanf("%d", &n);
    arr = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    dnc(0, n - 1, 0, n - 1);

    // Test
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", cnt[i]);
    }

    // 메모리 해제
    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);

    return 0;
}