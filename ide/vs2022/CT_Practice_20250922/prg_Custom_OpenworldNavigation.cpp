/*
 * [PRG_Mock_04] 오픈월드 내비게이션 엔진 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-15 (월)
 * - 알고리즘: Dijkstra (다익스트라 최단 경로 알고리즘)
 * - 목적: 양수 가중치를 가진 단방향 그래프에서 단일 출발지로부터 다른 모든 노드까지의 최소 이동 비용을 계산
 * - 엔진 실무 최적화:
 * 1. 최소 힙 제어 : `priority_queue`에 `greater` 구조체를 결합하여, 거리가 가장 짧은 노드부터 O(log V) 속도로 우선 탐색하도록 최적화.
 * 2. 메모리 참조 안정성 확보 : `pq.top()`의 반환값을 레퍼런스가 아닌 값 복사로 받아,
 `pop()` 호출 시 발생할 수 있는 댕글링 레퍼런스( UB )를 원천 차단함.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

vector<int> solution(int v, vector<vector<int>> edges, int start_node) {
    vector<int> answer;
    answer.reserve(v + 1);
    const int INF = 1e9;
    vector<vector<pair<int, int>>> adj(v + 1);
    vector<int> dist(v + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (const auto& e : edges)
        adj[e[0]].emplace_back(e[2], e[1]);

    dist[start_node] = 0;
    pq.emplace(0, start_node);

    while (!pq.empty())
    {
        const auto cur = pq.top(); pq.pop();

        if (cur.first > dist[cur.second]) continue;

        for (const auto& next : adj[cur.second])
        {
            int cost = dist[cur.second] + next.first;

            if (cost >= dist[next.second]) continue;

            dist[next.second] = cost;
            pq.emplace(cost, next.second);
        }
    }
    
    for (int i = 1; i <= v; i++)
    {
        if (dist[i] == INF) answer.push_back(-1);
        else answer.push_back(dist[i]);
    }

    return answer;
}
// =========================================================================

int main() {
    int v = 5;
    int start_node = 1;
    // 도로 정보: {출발지, 도착지, 가중치}
    vector<vector<int>> edges = {
        {1, 2, 2},
        {1, 3, 5},
        {2, 3, 1},
        {2, 4, 7},
        {3, 5, 3},
        {4, 5, 2}
    };

    // 기대 정답 분석 (시작 노드 1):
    // 1번(자기자신) -> 0
    // 2번 -> 2 (1->2)
    // 3번 -> 3 (1->2->3) : 비용 2 + 1 = 3 (다이렉트 5보다 작으므로 갱신됨)
    // 4번 -> 9 (1->2->4)
    // 5번 -> 6 (1->2->3->5)
    // 기대 반환 배열: {0, 2, 3, 9, 6}

    vector<int> result = solution(v, edges, start_node);

    cout << "========================================" << endl;
    cout << "[마을 별 최소 이동 비용] " << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << "마을 " << i + 1 << ": " << result[i] << endl;
    }
    cout << "========================================" << endl;

    return 0;
}