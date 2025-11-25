#include <stdio.h>
#include <queue>
#include <string>
using namespace std;

int t;
int A, B;
int visit[10000];

string dslr() {
    queue<pair<int, string>> q;
    string currString;
    int currN;
    int d, s, l, r;

    q.push({A, ""});
    visit[A] = 1;
    
    while (!q.empty()) {
        currN = q.front().first;
        currString = q.front().second;
        q.pop();

        // 같으면 지금까지의 연산 문자 출력
        if (currN == B) {
            return currString;
        }

        // dslr 연산
        d = (currN * 2) % 10000;
        s = (currN == 0) ? 9999 : currN - 1;
        l = (currN % 1000) * 10 + (currN / 1000);
        r = (currN / 10) + (currN % 10) * 1000;

        // 방문한적 없다면 큐에 push
        if (visit[d] == 0) {
            q.push({d, currString + "D"});
            visit[d] = 1;
        } 
        if (visit[s] == 0) {
            q.push({s, currString + "S"});
            visit[s] = 1;
        }
        if (visit[l] == 0) {
            q.push({l, currString + "L"});
            visit[l] = 1;
        }
        if (visit[r] == 0) {
            q.push({r, currString + "R"});
            visit[r] = 1;
        }
    }

    return "";
}

int main() {
    scanf("%d", &t);
    
    for (int i = 0; i < t; i++) {
        // visit배열 초기화
        for (int i = 0; i < 10000; i++) {
            visit[i] = 0;
        }
        
        string s = "";
        scanf("%d %d", &A, &B);

        string result = dslr(); // c++ 스타일의 문자열 객체를 c언어 스타일의 문자로 변환
        printf("%s\n", result.c_str());
        
    }

    return 0;
}