/*
 * [프로그래머스 43105] 정수 삼각형 (Lv.3)
 * - 훈련 날짜: 2026-04-24 (금)
 * - 알고리즘: 동적 계획법 (DP)
 * - 목적: 삼각형 꼭대기에서 바닥까지 이어지는 경로 중 숫자의 합이 최대가 되는 경로 찾기
 * - 엔진 실무 최적화:
 * 1. Top-Down 방식의 복잡한 경계선( Out of bounds ) 예외 처리를 피하기 위해 Bottom-Up 방식 채택.
 * 2. 2차원 DP 테이블 대신 1차원 배열( O( N )의 공간 복잡도 )을 활용한 덮어쓰기( In-place ) 최적화로
 캐시 히트율( Cache Hit Rate ) 극대화.
 * 3. 원본 입력값( triangle )을 훼손하지 않는 안전한( Side-effect free ) 데이터 처리.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    int dp[501];

    int solution(vector<vector<int>> triangle) {
        int n = (int)triangle.size();
       
        for (int i = 0; i < n; i++)
        {
            dp[i] = triangle[n - 1][i];
        }

        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                dp[j] = max(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }

        return dp[0];
    }
};
// =========================================================================

int main() {
    Solution sol;
    vector<vector<int>> t1 = { {7}, {3, 8}, {8, 1, 0}, {2, 7, 4, 4}, {4, 5, 2, 6, 5} };
    // 기대 결과: 30

    cout << "[테스트 1] 실행 결과: " << sol.solution(t1) << " / 기대 결과: 30\n";
    return 0;
}