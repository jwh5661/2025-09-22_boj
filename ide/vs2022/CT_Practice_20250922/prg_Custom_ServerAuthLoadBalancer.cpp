/*
 * [PRG_Mock_07] 인증 서버 부하 분산기 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-17 (수)
 * - 알고리즘: Parametric Search (매개 변수 탐색 / 이분 탐색)
 * - 목적: 처리 속도가 다른 다중 서버 환경에서 M명의 유저를 모두 처리하는 데 걸리는 최소 시간을 도출
 * - 엔진 실무 최적화:
 * 1. O(N log X) 시공간 압축 : 우선순위 큐나 시뮬레이션을 쓰면 O(M log N)으로 폭발하는 로직을,
 결정 문제로 뒤집어 약 60번의 탐색 루프만으로 10억 스케일을 도축함.
 * 2. 누산기 오버플로우 방어 : `isPossible` 함수 내에서 `cnt`가 목표치 `m`에 도달하는 즉시 누산을 중단하고 `return true`를 던짐으로써,
 잉여 연산 제거 및 `long long` 초과 오버플로우를 원천 차단함.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

bool isPossible(long long target_time, int m, vector<int>& times)
{
    long long cnt = 0;

    for (int t : times)
    {
        cnt += target_time / t;

        if (cnt >= m)
            return true;
    }

    return false;
}

long long solution(int n, long long m, vector<int> times) {
    long long answer = 0;
    long long low = 1;
    long long max_time = 0;
    for (int t : times) if (t > max_time) max_time = t;
    long long high = max_time * m;

    while (low <= high) {
        long long mid = (low + high) / 2; 

        if (isPossible(mid, m, times))
        {
            answer = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }

    return answer;
}
// =========================================================================

int main() {
    int n = 2; // 심사관(서버) 수 (사실 times.size()와 같음)
    long long m = 6; // 대기열 유저 수
    vector<int> times = { 7, 10 }; // 각 서버의 1명 처리 시간

    // 기대 정답 분석:
    // 시간: 7초 -> 1번 서버 1명, 2번 서버 0명 (총 1명, 실패)
    // 시간: 14초 -> 1번 서버 2명, 2번 서버 1명 (총 3명, 실패)
    // 시간: 21초 -> 1번 서버 3명, 2번 서버 2명 (총 5명, 실패)
    // 시간: 28초 -> 1번 서버 4명, 2번 서버 2명 (총 6명, 성공! 정답!)
    // 기대 반환값: 28

    long long result = solution(n, m, times);

    cout << "========================================" << endl;
    cout << "[모든 유저 인증에 필요한 최소 시간] : " << result << "초" << endl;
    cout << "========================================" << endl;

    return 0;
}