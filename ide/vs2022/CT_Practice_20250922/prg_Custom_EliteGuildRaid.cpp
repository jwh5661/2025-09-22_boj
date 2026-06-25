/*
 * [PRG_Mock_11] 엘리트 공격대 편성 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-25 (목)
 * - 알고리즘: DP on Trees (트리 DP)
 * - 목적: 상하 관계(트리 구조)에서 인접한 노드를 동시에 선택하지 않는 조건 하에 최대 전투력 산출
 * - 엔진 실무 최적화:
 * 1. O(N) Bottom-Up Accumulation : 리프 노드에서부터 부모 노드로 올라오며 점화식을 누적 계산하여,
 30만 개의 노드를 단 한 번의 DFS로 완벽히 스캔.
 * 2. 부모-자식 역주행 방지 : `if ( child == parent ) continue;` 단 한 줄의 방어 로직으로 
 추가적인 `visited` 배열 할당 없이 메모리를 극단적으로 절약함.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

const int MAX = 300005;
vector<int> tree[MAX];
int dp[MAX][2];
int power[MAX];

void DFS(int cur, int parent) {
    dp[cur][1] = power[cur];

    for (int child : tree[cur])
    {
        if (child == parent) continue;
        DFS(child, cur);
        dp[cur][0] += max(dp[child][0], dp[child][1]);
        dp[cur][1] += dp[child][0];
    }
}

int solution(vector<int> p, vector<vector<int>> edges) {
    int n = p.size();

    // 1. 초기화 (전역 변수 재사용 시 초기화 필수)
    for (int i = 1; i <= n; i++) {
        tree[i].clear();
        dp[i][0] = 0;
        dp[i][1] = 0;
        // 전투력 매핑 (1-based index 편의를 위함)
        power[i] = p[i - 1];
    }

    // 2. 양방향 트리 간선 구축
    for (const auto& e : edges)
    {
        tree[e[0]].push_back(e[1]);
        tree[e[1]].push_back(e[0]);
    }

    // 3. DFS 엔진 점화 (1번 노드를 임의의 루트로 설정)
    DFS(1, 0);

    // 4. 최댓값 반환
    return max(dp[1][0], dp[1][1]);
}
// =========================================================================

int main() {
    // 5명의 전투력 (1번 길드원부터 순서대로)
    vector<int> p = { 10, 30, 40, 10, 20 };

    // 조직도 (양방향 연결선)
    vector<vector<int>> edges = {
        {1, 2},
        {1, 3},
        {2, 4},
        {2, 5}
    };

    /* * 트리 구조:
     * 1(10)
     * /     \
     * 2(30)   3(40)
     * /   \
     * 4(10) 5(20)
     * * 최적 선발 시나리오: 2번(30) + 3번(40) 선발 = 총합 70
     * (이때 직속 상관인 1번과 직속 부하인 4, 5번은 선발 불가)
     */

    int result = solution(p, edges);

    cout << "========================================" << endl;
    cout << "[공격대 전투력 총합 최댓값] : " << result << " (기대값: 70)" << endl;
    cout << "========================================" << endl;

    return 0;
}