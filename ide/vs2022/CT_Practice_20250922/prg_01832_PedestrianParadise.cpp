/*
 * [프로그래머스 1832] 보행자 천국 (Lv.3)
 * - 훈련 날짜: 2026-05-19 (화)
 * - 알고리즘: Dynamic Programming (동적 계획법), 3D State Machine
 * - 목적: 방향 제한(관성)이 존재하는 2D 그리드 맵에서의 최단 경로 경우의 수 산출
 * - 엔진 실무 최적화:
 * 1. 3차원 상태 배열 설계 : dp[y][x][dir] 형태로 Z축에 '진입 방향( 가로/세로 )' 상태를 캐싱하여,
 관성( 직진만 가능 )이 유지되어야 하는 제약 조건을 O(1) 분기문으로 완벽히 통제함.
 * 2. Look-behind 전이 논리 : 현재 칸의 속성을 검사하는 대신, "나에게 오려는 직전 칸의 속성"을 검사하여
 값을 가져오는 역방향 참조 방식을 사용하여 복잡한 엣지 케이스를 우아하게 회피함.
 * 3. 메모리 연산 방어 : 오버플로우를 방지하기 위해 
 매 덧셈 연산 및 대입 연산 직후에 즉각적으로 모듈로 연산을 수행하여 데이터 무결성을 보장함.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================

class Solution {
public:
    int MOD = 20170805;

    int solution(int m, int n, vector<vector<int>> city_map) {
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));

        for (int i = 0; i < m; i++)
        {
            if (city_map[i][0] == 1) break;
            dp[i][0][1] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            if (city_map[0][i] == 1) break;
            dp[0][i][0] = 1;
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (city_map[i][j - 1] == 0)
                    dp[i][j][0] = (dp[i][j - 1][0] + dp[i][j - 1][1]) % MOD;
                else if (city_map[i][j - 1] == 2)
                    dp[i][j][0] = dp[i][j - 1][0] % MOD;
                else if (city_map[i][j - 1] == 1)
                    dp[i][j][0] = 0;

                if (city_map[i - 1][j] == 0)
                    dp[i][j][1] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
                else if (city_map[i - 1][j] == 2)
                    dp[i][j][1] = dp[i - 1][j][1] % MOD;
                else if (city_map[i - 1][j] == 1)
                    dp[i][j][1] = 0;
            }
        }

        return (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
    }
};
// =========================================================================

int main() {
    Solution sol;

    int m = 3;
    int n = 3;
    vector<vector<int>> city_map = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    // 기대 결과: 6

    cout << "[테스트 1] 실행 결과: " << sol.solution(m, n, city_map) << " / 기대 결과: 6\n";

    return 0;
}