/*
 * [프로그래머스 42884] 단속카메라 (Lv.3)
 * - 훈련 날짜: 2026-05-13 (수)
 * - 알고리즘: Greedy (그리디), Sorting (정렬)
 * - 목적: 2차원 배열의 다중 조건을 커스텀 정렬하고, 최적의 부분해를 누적하여 전역 최적해를 도출
 * - 엔진 실무 최적화:
 * 1. 객체의 진출 시점을 기준으로 오름차순 정렬하여, 최소한의 카메라( 레이캐스트 판정 )로
 * 모든 객체( AABB 겹침 판정 )를 커버하는 선형 탐색 최적화 달성.
 * 2. Range-Based for Loop( `const auto&` )를 사용하여 
 2차원 vector의 불필요한 객체 복사를 방지하고 캐시 적중률을 극대화함.
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
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    }

    int solution(vector<vector<int>> routes) {
        int answer = 0;

        int camera_pos = -30001;

        sort(routes.begin(), routes.end(), cmp);

        for (const auto& r : routes)
        {
            if (r[0] > camera_pos)
            {
                answer++;
                camera_pos = r[1];
            }
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    // [진입 지점, 진출 지점]
    vector<vector<int>> routes = {
        {-20, -15},
        {-14, -5},
        {-18, -13},
        {-5, -3}
    };
    // 기대 결과: 2 (카메라 위치: -15, -5)

    cout << "[테스트 1] 실행 결과: " << sol.solution(routes) << " / 기대 결과: 2\n";

    return 0;
}