/*
 * [프로그래머스 87390] n^2 배열 자르기 (Lv.2)
 * - 훈련 날짜: 2026-04-30 (목)
 * - 알고리즘: 게임 수학 (1D - 2D 인덱스 매핑)
 * - 목적: 물리적 메모리 할당 없이, 1차원 인덱스로부터 2차원 행렬의 가상 좌표와 값을 O(1)에 도출
 * - 엔진 실무 최적화:
 * 1. N 최대 10^7일 때 발생할 수 있는 10^14 크기의 Memory Overflow ( OOM )을 방지하기 위해
 2차원 배열 동적 할당을 전면 배제 ( 지연 평가 기법 활용 ).
 * 2. 1차원 인덱스 i를 2D 좌표로 변환하는 공식 ( row = i/n, col = i%n )과 
 셀의 패턴 수식 ( max( row, col) + 1 )을 결합하여, 필요한 구간[ left, right ]의 데이터만
 O( R - L ) 시간 복잡도로 실시간 스트리밍 산출.

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
    vector<int> solution(int n, long long left, long long right) {
        vector<int> answer;

        for (long long i = left; i <= right; i++)
            answer.push_back(max(i / n, i % n) + 1);

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    // 테스트 1
    int n1 = 3;
    long long left1 = 2, right1 = 5;
    // 기대 결과: {3, 2, 2, 3}

    vector<int> res1 = sol.solution(n1, left1, right1);
    cout << "[테스트 1] 실행 결과: ";
    for (int val : res1) cout << val << " ";
    cout << "\n";

    // 테스트 2
    int n2 = 4;
    long long left2 = 7, right2 = 14;
    // 기대 결과: {4, 3, 3, 3, 4, 4, 4, 4}

    vector<int> res2 = sol.solution(n2, left2, right2);
    cout << "[테스트 2] 실행 결과: ";
    for (int val : res2) cout << val << " ";
    cout << "\n";

    return 0;
}