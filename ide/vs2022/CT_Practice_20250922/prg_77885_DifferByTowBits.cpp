/*
 * [프로그래머스 77885] 2개 이하로 다른 비트 (Lv.2)
 * - 훈련 날짜: 2026-05-04 (월)
 * - 알고리즘: 게임 수학 (비트 조작 - Bit Manipulation)
 * - 목적: 순환문(Loop) 없이 비트 연산자 및 패턴 분석만으로 O(1) 시간에 정답을 도출
 * - 엔진 실무 최적화 :
 * 1. 64비트 정수( long long )를 다룰 때 발생하는 
 32비트 시프트 오버플로우( 1 << 31 )를 방지하기 위해 1LL 리터럴 사용.
 * 2. 가장 오른쪽 0비트를 추출하는 공식( ~x & ( x + 1 ) )을 활용하여 
 Branchless 로직으로 파이프라인 예측 실패( Branch Misprediction ) 비용을 제거함.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    vector<long long> solution(vector<long long> numbers) {
        vector<long long> answer;

        for (int i = 0; i < numbers.size(); i++)
        {
            unsigned long long val = numbers[i];

            val += ~numbers[i] & (numbers[i] + 1);
            val -= (~numbers[i] & (numbers[i] + 1)) >> 1;

            answer.push_back(val);
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;
    vector<long long> numbers = { 2, 7 };
    // 기대 결과: {3, 11}

    vector<long long> res = sol.solution(numbers);
    cout << "[테스트 1] 실행 결과: ";
    for (auto n : res) cout << n << " ";
    cout << "\n";

    return 0;
}