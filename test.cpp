#include <iostream>
#include <vector>

int main() {
    // vector는 원하는 만큼 크기가 늘어나는 동적 배열이다.
    std::vector<int> numbers; // 정수형 값을 담는 비어 있는 벡터
    std::cout << "초기 size: " << numbers.size() << "\n";

    // push_back(값)으로 맨 뒤에 데이터를 차례대로 넣는다.
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    std::cout << "push_back 후 size: " << numbers.size() << "\n";

    // [] 연산자로 배열처럼 접근한다. 인덱스는 0부터 시작한다.
    std::cout << "numbers[0] = " << numbers[0] << "\n";
    std::cout << "numbers[2] = " << numbers[2] << "\n";

    // back() 함수는 현재 마지막 원소를 돌려준다.
    std::cout << "마지막 값(back): " << numbers.back() << "\n";

    // 범위 기반 for문으로 모든 값을 순회할 수 있다.
    std::cout << "전체 값: ";
    for (int value : numbers) {
        std::cout << value << ' ';
    }
    std::cout << "\n";

    // pop_back()으로 맨 뒤 원소를 제거한다.
    numbers.pop_back();
    std::cout << "pop_back 후 size: " << numbers.size()
              << ", back: " << numbers.back() << "\n";

    // insert()로 중간에 새 값을 끼워 넣을 수 있다.
    numbers.insert(numbers.begin() + 1, 99); // 두 번째 위치에 99 삽입
    std::cout << "insert 후 값: ";
    for (int value : numbers) {
        std::cout << value << ' ';
    }
    std::cout << "\n";

    // 참조로 순회하면 벡터 안의 값을 직접 수정할 수도 있다.
    for (int &value : numbers) {
        value += 1;
    }
    std::cout << "참조 순회 후: ";
    for (int value : numbers) {
        std::cout << value << ' ';
    }
    std::cout << "\n";

    // clear()는 저장된 모든 값을 지운다.
    numbers.clear();
    std::cout << "clear 후 size: " << numbers.size() << "\n";

    return 0;
}
