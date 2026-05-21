/*
 * [프로그래머스 64062] 징검다리 건너기 (Lv.3)
 * - 훈련 날짜: 2026-05-21 (목)
 * - 알고리즘: Parametric Search (이분 탐색 / 결정 문제)
 * - 목적: 징검다리를 건널 수 있는 최대 인원을 구하는 `최적화 문제`를, "X명이 건널 때 간격이 K 이하로 유지되는가?"를 묻는 `결정 문제`로 치환하여 탐색
 * - 엔진 실무 최적화:
 * 1. Branch Optimization : 건널 수 없는 돌의 개수를 세는 대신 
 `밟은 돌 간의 인덱스 간격( i - idx )`을 측정하여 O(N) 순회 시 분기 연산을 최소화함.
 * 2. Infinite Loop Preservation : Upper Bound 갱신( `st = mid` ) 시 발생할 수 있는 무한 루프를 방지하기 위해
 `mid = ( st + ed + 1 ) / 2`의 Ceiling 연산을 적용함.
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
    bool solve(int x, int k, vector<int>& stones)
    {
        int idx = -1;

        for (int i = 0; i < (int)stones.size(); i++)
        {
            if (stones[i] >= x)
            {
                if (i - idx > k) return false;
                idx = i;
            }
        }

        return (int)stones.size() - idx <= k;
    }

    int solution(vector<int> stones, int k) {
        int st = 0, ed = *max_element(stones.begin(), stones.end());

        while (st < ed)
        {
            int mid = (st + ed + 1) / 2;

            if (solve(mid, k, stones)) st = mid;
            else ed = mid - 1;
        }

        return st;
    }
};
// =========================================================================

int main() {
    Solution sol;

    vector<int> stones = { 2, 4, 5, 3, 2, 1, 4, 2, 5, 1 };
    int k = 3;
    // 기대 결과: 3

    cout << "[테스트 1] 실행 결과: " << sol.solution(stones, k) << " / 기대 결과: 3\n";

    return 0;
}