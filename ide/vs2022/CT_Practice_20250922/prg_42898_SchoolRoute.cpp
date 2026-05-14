/*
 * [프로그래머스 42898] 등굣길 (Lv.3)
 * - 훈련 날짜: 2026-05-14 (목)
 * - 알고리즘: Dynamic Programming (동적 계획법)
 * - 목적: 2차원 그리드 상의 최단 경로 경우의 수 산출 및 장애물(예외 상태) 전이 처리
 * - 엔진 실무 최적화:
 * 1. 배열의 0번 인덱스를 버리는 패딩 기법을 적용하여, 
 점화식 계산 시 불필요한 Out-of-Bounds 예외 처리 오버헤드를 완벽히 제거함.
 * 2. 매 연산마다 모듈러 연산을 강제하여, 
 지수 형태로 폭발적으로 증가하는 경로 카운팅 시 발생할 수 있는 Integer Overflow를 원천 차단함.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    int solution(int m, int n, vector<vector<int>> puddles) {
        const int MOD = 1000000007;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (const auto& p : puddles) {
            dp[p[1]][p[0]] = -1;
        }

        dp[1][1] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i == 1 && j == 1) continue;

                if (dp[i][j] == -1) {
                    dp[i][j] = 0;
                    continue;
                }

                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            }
        }

        return dp[n][m];
    }
};
// =========================================================================

int main() {
    Solution sol;

    int m = 4; // 가로(열)
    int n = 3; // 세로(행)
    // 웅덩이 좌표 [열, 행]
    vector<vector<int>> puddles = { {2, 2} };
    // 기대 결과: 4

    cout << "[테스트 1] 실행 결과: " << sol.solution(m, n, puddles) << " / 기대 결과: 4\n";

    return 0;
}