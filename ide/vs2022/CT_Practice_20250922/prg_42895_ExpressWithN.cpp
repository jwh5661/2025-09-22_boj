/*
 * [프로그래머스 42895] N으로 표현 (Lv.3)
 * - 훈련 날짜: 2026-04-24 (금)
 * - 알고리즘: 동적 계획법 (DP)
 * - 목적: 주어진 숫자 N과 사칙연산만을 사용하여 타겟 숫자를 만드는 최소 횟수 산출
 * - 엔진 실무 최적화:
 * 1. unordered_set을 활용하여 중복된 연산 결과를 O( 1 )로 제거.
 * 2. 스코프( Scope ) 혼동을 유발하는 switch문 대신 
 if - else if - continue 제어 흐름을 사용하여 코드 안정성 확보.
 * 3. 메인 로직 진입 전, 초기화 단계( Seed todtjd )에서도 즉시 정답을 판별( Early Exit )하여 
 엣지 케이스( 예 : N = 5, number = 55 ) 방어.
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    unordered_set<int> dp[8];

    int solution(int N, int number) {
        if (N == number) return 1;

        const int mx = 8;
        int nn = 0;

        for (int i = 0; i < mx; i++)
        {
            nn *= 10;
            nn += N;
            
            if (nn == number) return i + 1;

            dp[i].insert(nn);
        }

        for (int i = 1; i < mx; i++)
        {
            for (int j = 0; j < i; j++)
            {
                for (int x : dp[j])
                {
                    for (int y : dp[i - j - 1])
                    {
                        int val = 0;
                        for (int d = 0; d < 4; d++)
                        {
                            if (d == 0)  val = x + y;
                            else if (d == 1) val = x - y;
                            else if (d == 2) val = x * y;
                            else if (d == 3)
                            {
                                if (y == 0) continue;
                                val = x / y;
                            }

                            if (val == number) return i + 1;

                            dp[i].insert(val);
                        }
                    }
                }
            }
        }

        return -1;
    }
};
// =========================================================================

int main() {
    Solution sol;
    // 테스트 1: N=5, number=12, 결과=4
    // 테스트 2: N=2, number=11, 결과=3
    cout << "[테스트 1] 실행 결과: " << sol.solution(5, 12) << " / 기대 결과: 4\n";
    cout << "[테스트 2] 실행 결과: " << sol.solution(2, 11) << " / 기대 결과: 3\n";
    return 0;
}