/*
 * [프로그래머스 12971] 스티커 모으기(2) (Lv.3)
 * - 훈련 날짜: 2026-05-19 (화)
 * - 알고리즘: Dynamic Programming (동적 계획법)
 * - 목적: 원형 배열(Circular Array)의 인접 제약 조건을 회피하여 얻을 수 있는 최대 가치 산출
 * - 엔진 실무 최적화:
 * 1. 상태 제약 분리 : '첫 번째 원소를 선택하는 우주'와 '포기하는 우주'로 DP 테이블을 2개로 분할하여
 원형 배열이 가지는 위상학적 예외( 처음과 끝이 만나는 현상 )를 완벽하게 차단함.
 * 2. 분기 최적화 : '스티커를 뜯었는지 여부'를 별도의 boolean 배열이나 구조체로 추적하지 않고, 
 max 연산을 통해 이전 상태의 전역 최적해를 현재 상태로 전이시키는 DP의 핵심을 활용함.
 * 3. 예외 처리 : 데이터의 스케일이 N=1일 때 발생할 수 있는 Out-of-Bounds 메모리 참조 에러를 최상단 예외 분기로 방어함.
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
    int solution(vector<int> sticker) {
        int n = sticker.size();
        if (n == 1) return sticker[0];

        int prev1, prev2, answer1, answer2;

        prev1 = sticker[0];
        prev2 = prev1;

        for (int i = 2; i < n - 1; i++)
        {
            int temp = prev2;
            prev2 = max(prev2, prev1 + sticker[i]);
            prev1 = temp;
        }

        answer1 = prev2;
        
        prev1 = 0;
        prev2 = sticker[1];

        for (int i = 2; i < n; i++)
        {
            int temp = prev2;
            prev2 = max(prev2, prev1 + sticker[i]);
            prev1 = temp;
        }

        answer2 = prev2;

        return max(answer1, answer2);
    }
};
// =========================================================================

int main() {
    Solution sol;

    vector<int> sticker = { 14, 6, 5, 11, 3, 9, 2, 10 };
    // 기대 결과: 36 (14 + 11 + 9 + 2)

    cout << "[테스트 1] 실행 결과: " << sol.solution(sticker) << " / 기대 결과: 36\n";

    return 0;
}