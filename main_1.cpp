#include <iostream>
#include <windows.h>
using namespace std;

const int N = 512;

double A[N][N];
double x[N];
double res1[N], res2[N];

void init() {
    for (int i = 0; i < N; i++) {
        x[i] = i;
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }
}

// 列访问平凡算法
void naive() {
    for (int j = 0; j < N; j++) {
        res1[j] = 0;
        for (int i = 0; i < N; i++) {
            res1[j] += A[i][j] * x[i];
        }
    }
}

// 优化行访问
void optimized() {
    for (int j = 0; j < N; j++)
        res2[j] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res2[j] += A[i][j] * x[i];
        }
    }
}

int main() {
    init();

    LARGE_INTEGER head, tail, freq;
    QueryPerformanceFrequency(&freq);//时间

    QueryPerformanceCounter(&head);
    naive();
    QueryPerformanceCounter(&tail);
    cout << "Naive time: "
         << (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart
         << " ms" << endl;

    QueryPerformanceCounter(&head);
    optimized();
    QueryPerformanceCounter(&tail);
    cout << "Optimized time: "
         << (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart
         << " ms" << endl;

    cout << "Check: " << res1[0] << " " << res2[0] << endl;

    return 0;
}
