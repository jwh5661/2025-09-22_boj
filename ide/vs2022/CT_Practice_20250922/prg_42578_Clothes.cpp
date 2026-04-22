/*
 * [프로그래머스 42578] 의상 (Lv.2)
 * - 훈련 날짜: 2026-04-21 (화)
 * - 알고리즘: 해시 (Hash)
 * - 목적: 카테고리별 개수 카운팅 및 조합(Combination) 수학 연산
 * - 엔진 실무 최적화:
 * 1. C++17 구조적 바인딩( Structured Binding )을 통한 map 순회 가독성 향상
 * 곱셈 누적 시 발생할 수 있는 오버플로우를 대비한 long long 타입 사용
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    int solution(vector<vector<string>> clothes) {
        long long answer = 1;

        unordered_map<string, int> clothes_map;

        for (const auto& c : clothes)
        {
            clothes_map[c[1]]++;
        }

        for (const auto& [key, val] : clothes_map)
        {
            answer *= (val + 1);
        }
        
        return (int)(answer - 1);
    }
};
// =========================================================================


// =========================================================================
// [로컬 테스트 드라이버 구역]
// =========================================================================
int main() {
    Solution sol;

    // 테스트 케이스 1
    vector<vector<string>> clothes1 = {
        {"yellow_hat", "headgear"},
        {"blue_sunglasses", "eyewear"},
        {"green_turban", "headgear"}
    };
    cout << "[테스트 1] 결과: " << sol.solution(clothes1) << " (기대값: 5)" << endl;

    // 테스트 케이스 2
    vector<vector<string>> clothes2 = {
        {"crow_mask", "face"},
        {"blue_sunglasses", "face"},
        {"smoky_makeup", "face"}
    };
    cout << "[테스트 2] 결과: " << sol.solution(clothes2) << " (기대값: 3)" << endl;

    return 0;
}