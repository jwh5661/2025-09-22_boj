/*
 * [프로그래머스 43238] 입국심사 (Lv.3)
 * - 훈련 날짜: 2026-05-21 (목)
 * - 알고리즘: Parametric Search (이분 탐색 / 결정 문제)
 * - 목적: "N명을 처리하는 최소 시간"을 구하는 최적화 문제를, "X시간 동안 N명을 처리할 수 있는가?"를 묻는 결정(Yes/No) 문제로 뒤집어 탐색
 * - 엔진 실무 최적화:
 * 1. Data Type Scaling : 탐색 범위의 최댓값이 10억 * 10억 = 10^18에 달하므로,
 `mid`와 `cnt` 변수를 `long long`으로 선언하여 정수 오버플로우를 원천 차단함.
 * 2. Memory Copy Overhead 방지 : `solve` 함수에 컨테이너( `vector` )를 넘길 때 
 값 복사가 일어나지 않도록 참조자( `&` )를 사용하여 O(1) 메모리 접근 최적화를 달성함.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    bool solve(int n, long long x, vector<int>& times)
    {
        long long cnt = 0;

        for (int i = 0; i < times.size(); i++)
            cnt += x / times[i];

        return n <= cnt;
    }

    long long solution(int n, vector<int> times) {
        long long MaxTime = *max_element(times.begin(), times.end());
        long long st = 0, ed = MaxTime * n;

        while (st < ed)
        {
            long long mid = (st + ed) / 2;

            if (solve(n, mid, times)) ed = mid;
            else st = mid + 1;
        }

        return st;
    }
};
// =========================================================================

int main() {
    Solution sol;

    int n = 6;
    vector<int> times = { 7, 10 };
    // 기대 결과: 28

    cout << "[테스트 1] 실행 결과: " << sol.solution(n, times) << " / 기대 결과: 28\n";

    return 0;
}