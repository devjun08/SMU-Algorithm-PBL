#include <stdio.h>
#include <math.h>

int length, width, height;
int n_cube; 
int cube[20];
int cubeL[20];
int cubeCount = 0;
bool isFull = true;

int dnc(int length, int width, int height) {
    // conquer
    if (length <= 0 || width <= 0 || height <= 0) return 0;

    // divide
    int s;
    for (int i = 19; i >= 0; i--) {
        if (cube[i] == 0) // 큐브가 존재하지 않으니 하나 작은 크기의 큐브를 확인.
            continue;

        s = cubeL[i];
        if (s <= length && s <= width && s <= height) {
            cube[i]--;
            cubeCount++;

            dnc(length - s, width, height);
            dnc(s, width - s, height);
            dnc(s, s, height - s);

            return 0;
        }
    }

    isFull = false;
    return 0; // No longer able to fill cubes

    // combine (Unnecessary)
}

int main() {
    scanf("%d %d %d", &length, &width, &height);
    scanf("%d", &n_cube);

    int a, b;
    for (int i = 0; i < n_cube; i++) {
        scanf("%d %d", &a, &b);
        cube[a] = b;
    }
    // 후... 미리 계산해준다 특별히
    for (int i = 0; i < 20; i++) {
        cubeL[i] = (int)pow(2, i);
    }

    dnc(length, width, height);
    
    if (isFull == false) {
        printf("-1\n");
    } else {
        printf("%d", cubeCount);
    }

    return 0;
}