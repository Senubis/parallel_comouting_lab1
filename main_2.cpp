#include <iostream>
#include <windows.h>
using namespace std;

const int N = 1000000;
int a[N];

void init() {
    for (int i = 0; i < N; i++) {
        a[i] = 3;
    }
}

// 平凡算法，一个一个加
long long naive() {
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }
    return sum;
}

// 两路优化
long long optimized() {
    long long sum1 = 0, sum2 = 0;

    for (int i = 0; i < N; i += 2) {
        sum1 += a[i];
        sum2 += a[i + 1];
    }

    return sum1 + sum2;
}

int main() {
    init();

    LARGE_INTEGER head, tail, freq;
    QueryPerformanceFrequency(&freq);//内置精确时间比较

    long long s1, s2;

    QueryPerformanceCounter(&head);
    s1 = naive();
    QueryPerformanceCounter(&tail);
    cout << "Naive time: "
         << (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart
         << " ms" << endl;

    QueryPerformanceCounter(&head);
    s2 = optimized();
    QueryPerformanceCounter(&tail);
    cout << "Optimized time: "
         << (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart
         << " ms" << endl;

    cout << "Check: " << s1 << " " << s2 << endl;

    return 0;
}
