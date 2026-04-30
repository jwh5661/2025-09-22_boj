/*
 * [프로그래머스 12949] 행렬의 곱셈 (Lv.2)
 * - 훈련 날짜: 2026-04-30 (목)
 * - 알고리즘: 게임 수학 (선형대수학 - Matrix)
 * - 목적: 두 행렬의 곱을 2차원 배열 기반으로 구현하여 그래픽스 파이프라인의 기초 연산 원리 파악
 * - 엔진 실무 최적화:
 * 1. M x N 크기의 결과를 담을 2차원 배열을 O(1)에 동적 할당 및 0으로 초기화.
 * 2. ( 추가 개념 ) C++의 Row-major 메모리 구조를 고려하여, 
 3중 루프의 순서를 i-k-j 로 배치할 경우 Cache Hit Rate를 극대화할 수 있음을 인지.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
        int r1 = arr1.size();
        int c1 = arr1[0].size();
        int r2 = arr2.size();
        int c2 = arr2[0].size();

        vector<vector<int>> answer(r1, vector<int>(c2, 0));

        for (int i = 0; i < r1; i++)
        {
            for (int k = 0; k < c1; k++)
            {
                for (int j = 0; j < c2; j++)
                    answer[i][j] += arr1[i][k] * arr2[k][j];
            }
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    // 테스트 1
    vector<vector<int>> a1 = { {1, 4}, {3, 2}, {4, 1} };
    vector<vector<int>> b1 = { {3, 3}, {3, 3} };
    // 기대 결과: {{15, 15}, {15, 15}, {15, 15}}

    vector<vector<int>> res1 = sol.solution(a1, b1);
    cout << "[테스트 1] 실행 결과:" << endl;
    for (const auto& row : res1) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    return 0;
}