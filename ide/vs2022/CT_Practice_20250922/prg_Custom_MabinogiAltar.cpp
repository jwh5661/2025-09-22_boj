/*
 * [PRG_Mock_15] 마비노기 영웅전 제단 순회 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-29 (월)
 * - 알고리즘: DFS, Bitmasking, DP (Memoization), TSP(외판원 순회) 패턴
 * - 목적: N!의 폭발적인 탐색 공간을 비트마스킹과 메모이제이션을 결합하여 O(N * 2^N)으로 압축하여 경로 탐색
 * - 엔진 실무 최적화:
 * 1. `dp[current][visited_bit]` 형태의 캐싱을 통해 동일한 상태에 대한 중복 하위 탐색을 원천 차단
 * 2. C++ 배열의 포인터 붕괴를 방지하기 위해 `adj[i].clear()` 명시적 루프 초기화 적용으로 연속 쿼리 메모리 오염 방지.
 */

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

int N;
vector<int> adj[15];
int dp[15][1 << 15];

int dfs(int current, int visited_bit) {
    if (visited_bit == (1 << N) - 1)
        return 1;

    if (dp[current][visited_bit] != -1)
        return dp[current][visited_bit];

    int cnt = 0;

    for (int next : adj[current])
    {
        if (visited_bit & (1 << next)) continue;
        cnt += dfs(next, visited_bit | (1 << next));
    }

    return dp[current][visited_bit] = cnt;
}

int solution(int n, int m, vector<vector<int>> portal_data) {
    N = n;

    for (int i = 0; i < 15; i++)
    {
        adj[i].clear();
    }

    memset(dp, -1, sizeof(dp));
    
    for (const auto& p : portal_data)
        adj[p[0]].push_back(p[1]);

    int answer = dfs(0, (1 << 0));

    return answer;
}
// =========================================================================

int main() {
    int n = 4; // 제단의 수
    int m = 5; // 포탈의 수

    // {u, v} 단방향 포탈 정보
    vector<vector<int>> portal_data = {
        {0, 1}, {0, 2}, {1, 2}, {2, 1}, {1, 3}, {2, 3}
    };

    /* * [기대 정답 시나리오 분석]
     * 목표: 0번에서 출발하여 모든 제단 {0, 1, 2, 3}을 정확히 한 번씩 방문하고 끝나는 경로의 수
     * - 경로 1: 0 -> 1 -> 2 -> 3 (방문 제단: 0, 1, 2, 3 완료)
     * - 경로 2: 0 -> 2 -> 1 -> 3 (방문 제단: 0, 2, 1, 3 완료)
     * 결성 가능한 총 순회 경로의 수: 2
     */

    int result = solution(n, m, portal_data);

    cout << "========================================" << endl;
    cout << "[결계 해제 가능한 총 이동 경로의 수] : " << result << endl;
    cout << "[로컬 디버깅용 검증 기대값]          : 2" << endl;
    cout << "========================================" << endl;

    return 0;
}