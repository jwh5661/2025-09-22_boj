/*
 * [PRG_Mock_08] 거래소 매물 스캐너 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-18 (목)
 * - 알고리즘: Two Pointers (투 포인터) / Sliding Window (슬라이딩 윈도우)
 * - 목적: 양수로만 이루어진 1차원 배열에서 구간 합이 K가 되는 최단 길이의 연속 부분 구간 탐색
 * - 엔진 실무 최적화:
 * 1. O(1) 메모리 스위칭 : 별도의 누적 합 배열을 동적 할당하지 않고,
 `sum` 변수 하나만으로 포인터 이동에 따른 증감을 실시간 처리하여 메모리 부하를 제로로 수렴시킴.
 * 2. 윈도우 축소 최적화 : `sum == k`로 정답을 찾았을 때 `break`하거나 `right`를 늘리지 않고,
 곧바로 `sum -= sequence[left++]`를 실행하여 윈도우를 강제로 좁힘으로써 더 짧은 최적의 구간을 즉시 탐색해 들어가는 고급 기어비 적용.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer(2, 0);
    int n = sequence.size();

    int left = 0, right = 0;
    long long sum = sequence[0];
    int min_len = 1e9;

    while (right < n && left <= right) {
        if (sum == k) {
            if (right - left + 1 < min_len) {
                answer[0] = left;
                answer[1] = right;
                min_len = right - left + 1;
            }
            sum -= sequence[left++];
        }
        else if (sum < k) {
            if (right == n - 1) break;
            sum += sequence[++right];
        }
        else {
            sum -= sequence[left++];
        }
    }

    return answer;
}
// =========================================================================

int main() {
    // k = 5 (목표 예산)
    // 인덱스:  0  1  2  3  4  5  6
    // 매물값:  1  1  1  2  3  4  5
    vector<int> sequence = { 1, 1, 1, 2, 3, 4, 5 };
    int k = 5;

    // 기대 정답 분석:
    // 1. [0, 3] 구간 (1+1+1+2 = 5) -> 길이 4
    // 2. [3, 4] 구간 (2+3 = 5) -> 길이 2
    // 3. [6, 6] 구간 (5 = 5) -> 길이 1 (최단 길이!)
    // 기대 반환 배열: {6, 6}

    vector<int> result = solution(sequence, k);

    cout << "========================================" << endl;
    cout << "[최적 구간 매물 인덱스] : [" << result[0] << ", " << result[1] << "]" << endl;
    cout << "========================================" << endl;

    return 0;
}