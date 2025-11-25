// bfs는 모든 곳을 탐색할 수 있다는 점.

#include <stdio.h>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int result; // 제출용 답안
int k;
int w, h;
int board[200][200];
bool visit[200][200][31] = { 0 };

int bfs() {
    queue<pair<pair<int, int>, pair<int, int>>> q;
    visit[0][0][0] = true;
    q.push({{0, 0}, {0, 0}});
    int nx, ny;

    // d_x,y 변화량 계산
    int h_dxy[][2] = {{-2, -1}, {-1, -2}, {2, 1}, {1, 2}, {1, -2}, {2, -1}, {-2, 1}, {-1, 2}};
    int dxy[][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

    while (!q.empty()) {
        // 매번 값 pop
        int curx = q.front().first.first;
        int cury = q.front().first.second;
        int distance = q.front().second.first;
        int horse = q.front().second.second;
        q.pop();

        if (curx == w - 1 && cury == h - 1) {
            return distance;
        }

        if (horse < k) {
            // 나이트(말)의 움직임
            for (int i = 0; i < 8; i++) {
                nx = curx + h_dxy[i][0];
                ny = cury + h_dxy[i][1];

                if (nx < 0 || nx > w - 1 || ny < 0 || ny > h - 1) {
                    continue; // 맵 밖으로 벗어나거나 장애물로 이동하려 한다면 고려하지 않음
                }

                if (board[ny][nx] == 0 && visit[ny][nx][horse + 1] != true) {
                    visit[ny][nx][horse + 1] = true;
                    q.push({{ny, nx}, {distance + 1, horse + 1}});
                }
            }
        }

        // 원숭이 움직임
            for (int i = 0; i < 4; i++) {
                nx = curx + dxy[i][0];
                ny = cury + dxy[i][1];

                if (nx < 0 || nx > w - 1 || ny < 0 || ny > h - 1) {
                    continue; // 맵 밖으로 벗어나거나 장애물로 이동하려 한다면 고려하지 않음
                }

                if (board[ny][nx] == 0 && visit[ny][nx][horse] != true) {
                    visit[ny][nx][horse] = true;
                    q.push({{ny, nx}, {distance + 1, horse}});
                }
            }
    }

    return -1;
}

int main() {
    scanf("%d", &k);
    scanf("%d %d", &w, &h);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    // bfs
    result = bfs();

    printf("%d", result);

    return 0;
}