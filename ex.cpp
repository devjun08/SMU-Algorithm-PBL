#include <iostream>
#include <queue> // BFS를 위해 큐 사용
using namespace std;

// 원숭이의 상태를 저장할 구조체
struct monkey {
	int x, y; // 현재 위치 (x: 세로, y: 가로)
	int horse; // 지금까지 말의 움직임을 사용한 횟수
	int dist; // 시작점에서 현재 칸까지 이동한 횟수(거리)
};

// 전역 변수 선언
int K, W, H; // K: 말 이동 가능 횟수, W: 가로 크기, H: 세로 크기
int Map[200][200]; // 지도 정보 (0: 빈칸, 1: 장애물)
bool visited[200][200][31]; // 방문 여부 체크 (x, y, 말 이동 사용 횟수)

// 말의 움직임(나이트 이동 8방향)
const int dhorse[][2] = {
	{-1,-2},{-2,-1},{-2,1},{-1,2},
	{1,2},{2,1},{2,-1},{1,-2}
};

// 원숭이의 기본 움직임(상하좌우 4방향)
const int dmonkey[][2] = {
	{-1,0},{1,0},{0,-1},{0,1}
};

// BFS (너비 우선 탐색) 함수 정의
int bfs() {
	queue<monkey> q; // 원숭이의 이동 상태를 저장할 큐 생성
	q.push({0, 0, 0, 0}); // 시작점 (0,0), 말 이동 0회, 거리 0으로 초기화
	visited[0][0][0] = true; // 시작점 방문 처리

	while (!q.empty()) { // 큐가 빌 때까지 반복
		int x = q.front().x; // 현재 위치의 x좌표
		int y = q.front().y; // 현재 위치의 y좌표
		int horse = q.front().horse; // 현재까지 말 이동을 쓴 횟수
		int dist = q.front().dist; // 현재까지 이동한 거리
		q.pop(); // 큐에서 꺼냄

		// 목표 지점(H-1, W-1)에 도달하면 이동 횟수 반환
		if (x == H - 1 && y == W - 1) {
			return dist;
		}

		// 1.말처럼 이동할 수 있는 경우 (아직 말 이동 횟수 < K)
		if (horse < K) {
			for (int i = 0; i < 8; i++) { // 8가지 말 이동 방향 확인
				int nx = x + dhorse[i][0];
				int ny = y + dhorse[i][1];

				// 범위를 벗어나면 건너뜀
				if (nx < 0 || nx >= H || ny < 0 || ny >= W)
					continue;

				// 이동할 칸이 빈 칸이고, 아직 방문하지 않은 상태라면
				if (Map[nx][ny] == 0 && !visited[nx][ny][horse + 1]) {
					visited[nx][ny][horse + 1] = true; // 방문 처리 (말 이동 횟수 +1)
					q.push({nx, ny, horse + 1, dist + 1}); // 다음 위치를 큐에 삽입
				}
			}
		}

		// 2.원숭이처럼 상하좌우로 이동하는 경우
		for (int i = 0; i < 4; i++) {
			int nx = x + dmonkey[i][0];
			int ny = y + dmonkey[i][1];

			// 범위를 벗어나면 건너뜀
			if (nx < 0 || nx >= H || ny < 0 || ny >= W)
				continue;

			// 이동할 칸이 빈 칸이고, 아직 방문하지 않은 상태라면
			if (Map[nx][ny] == 0 && !visited[nx][ny][horse]) {
				visited[nx][ny][horse] = true; // 방문 처리 (말 이동 횟수는 그대로)
				q.push({nx, ny, horse, dist + 1}); // 다음 위치를 큐에 삽입
			}
		}


	}

	// 모든 경우를 탐색했는데도 도착할 수 없다면 -1 반환
	return -1;
}

int main() {
	cin >> K >> W >> H; //말 이동 가능 횟수 K, 가로 W, 세로 H

	// 지도 입력 받기
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j]; // 0: 빈칸, 1: 장애물
		}
	}

	int res = bfs(); // BFS 실행
	cout << res << '\n'; // 결과 출력
	return 0;
}