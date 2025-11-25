#include <stdio.h>
#include <stdlib.h>

int n;      // 행렬의 크기
int **arr;  // 2차원 동적 배열, 입력받은 행렬 저장
int cnt[3]; // 각 숫자의 개수 카운트, 인덱스: 0->-1, 1->0, 2->1

// 배열 인덱스 변환 함수: 입력값 (-1,0,1)을 (0,1,2) 범위 인덱스로 변환
int idx2n(int idx)
{
    return idx + 1;
}

// 지정 구역 내 모든 원소가 같은 값인지 확인하는 함수
int CheckSameCells(int xs, int xe, int ys, int ye)
{
    int i, j, idx;
    bool flag = true;  // 모두 같으면 true 유지
    idx = arr[xs][ys]; // 기준 값 (첫번째 셀 값)
    for (i = xs; i <= xe; i++)
    {
        for (j = ys; j <= ye; j++)
        {
            if (idx != arr[i][j])
            { // 다르면 false로 변환 후 break
                flag = false;
                break;
            }
        }
        if (!flag)
            break; // 외부 루프도 중단
    }
    return flag;
}

// 분할 정복 함수: (xs, xe, ys, ye) 범위
void dnc(int xs, int xe, int ys, int ye)
{
    int idx;

    // 1. 베이스 케이스: 구역 크기가 1x1이면 해당 숫자 카운트 증가
    if (xs == xe && ys == ye)
    {
        idx = arr[xs][ys];
        cnt[idx2n(idx)]++;
        return;
    }

    // 2. 만약 구역 내 모든 값이 같으면 카운트만 증가하고 종료
    if (CheckSameCells(xs, xe, ys, ye))
    {
        idx = arr[xs][ys];
        cnt[idx2n(idx)]++;
        return;
    }

    // 3. 구역을 9등분 하기 위한 중간 좌표 계산
    int xm1 = (2 * xs + xe) / 3; // 1/3 지점 1
    int xm2 = (xs + 2 * xe) / 3; // 1/3 지점 2
    int ym1 = (2 * ys + ye) / 3;
    int ym2 = (ys + 2 * ye) / 3;

    // 4. 9등분 된 각 구역에 대해 재귀 호출
    dnc(xs, xm1, ys, ym1);
    dnc(xm1 + 1, xm2, ys, ym1);
    dnc(xm2 + 1, xe, ys, ym1);
    dnc(xs, xm1, ym1 + 1, ym2);
    dnc(xm1 + 1, xm2, ym1 + 1, ym2);
    dnc(xm2 + 1, xe, ym1 + 1, ym2);
    dnc(xs, xm1, ym2 + 1, ye);
    dnc(xm1 + 1, xm2, ym2 + 1, ye);
    dnc(xm2 + 1, xe, ym2 + 1, ye);

    // 5. 이 문제는 별도의 결합 작업이 없고 재귀 결과 통계를 cnt 배열에 쌓음
}

int main()
{
    int i, j, val;

    // 0. 초기화
    for (i = 0; i < 3; i++)
        cnt[i] = 0;

    // 1. 행렬 크기 및 데이터 입력
    scanf("%d", &n);
    arr = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * n);
        for (j = 0; j < n; j++)
        {
            scanf("%d", &val);
            arr[i][j] = val;
        }
    }

    // 2. 분할 정복 시작: 전체 범위
    dnc(0, n - 1, 0, n - 1);

    // 3. 각 숫자별 구역 개수 출력
    for (i = 0; i < 3; i++)
        printf("%d\n", cnt[i]);

    // 4. 동적 할당 해제
    for (i = 0; i < n; i++)
        free(arr[i]);
    free(arr);

    return 0;
}
