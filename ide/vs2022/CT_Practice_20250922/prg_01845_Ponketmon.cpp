/*
 * [프로그래머스 1845] 폰켓몬 (Lv.1)
 * - 훈련 날짜: 2026-04-21 (화)
 * - 알고리즘: 해시 (Hash / Set)
 * - 목적: std::unordered_set을 활용한 중복 제거 및 최댓값 산출
 * - 엔진 실무 최적화:
 * 1. 데이터의 존재 유무( 종류 )만 중요할 때는 map 대신 set을 사용하여 메모리 절약
 * 2. size_t와 int 간의 타입 충돌을 방지하기 위한 명시적 캐스팅 적용
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm> // min 함수 사용을 위함

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// 아래 클래스 전체와 필요한 #include 문만 프로그래머스에 복사하여 제출합니다.
// =========================================================================
class Solution {
public:
    int solution(vector<int> nums) {
        unordered_set<int> us;

        for (int n : nums)
            us.insert(n);

        return min((int)us.size(), (int)nums.size() / 2);
    }
};
// =========================================================================


// =========================================================================
// [로컬 테스트 드라이버 구역]
// Visual Studio에서 로컬 테스트를 하기 위한 용도입니다. 
// 프로그래머스에는 제출하지 않습니다.
// =========================================================================
int main() {
    // 1. 테스트 케이스 데이터 세팅
    vector<int> nums1 = { 3, 1, 2, 3 };
    vector<int> nums2 = { 3, 3, 3, 2, 2, 4 };
    vector<int> nums3 = { 3, 3, 3, 2, 2, 2 };

    // 2. Solution 객체 생성 및 함수 실행
    Solution sol;
    int result1 = sol.solution(nums1);
    int result2 = sol.solution(nums2);
    int result3 = sol.solution(nums3);

    // 3. 결과 출력 및 검증
    cout << "[테스트 1] 실행 결과: " << result1 << " / 기대 결과: 2\n";
    cout << "[테스트 2] 실행 결과: " << result2 << " / 기대 결과: 3\n";
    cout << "[테스트 3] 실행 결과: " << result3 << " / 기대 결과: 2\n";

    return 0;
}