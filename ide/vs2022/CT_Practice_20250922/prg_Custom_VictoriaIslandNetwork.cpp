/*
 * [PRG_Mock_13] 빅토리아 아일랜드 네트워크 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-26 (금)
 * - 알고리즘: Dijkstra (다익스트라), Path Tracing (경로 역추적)
 * - 목적: 최단 경로 상의 간선이 하나씩 단절되는 모든 최악의 경우를 시뮬레이션하여 가장 오래 걸리는 우회 시간 도출
 * - 엔진 실무 최적화:
 * 1. `parent` 배열을 이용한 O(V) 역추적으로 원본 최단 경로를 구성하는 간선만을 정밀하게 추출.
 * 2. `path.reserve(n)`을 통한 벡터 메모리 재할당 오버헤드 방지 및 `avoid_u == -1` 분기를 통한 단일 함수 다형성 구현.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

const int MAX = 1005;
const int INF = 1e9;

vector<pair<int, int>> adj[MAX];
int dist_arr[MAX];
int parent[MAX];

int run_dijkstra(int start, int end, int avoid_u, int avoid_v) {
    for (int i = 0; i < MAX; i++)
        dist_arr[i] = INF;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist_arr[start] = 0;
    parent[start] = -1;
    pq.emplace(dist_arr[start], start);

    while (!pq.empty())
    {
        const auto cur = pq.top(); pq.pop();
        int cur_cost = cur.first;
        int cur_node = cur.second;

        if (cur_node == end) break;
        if (dist_arr[cur_node] < cur_cost) continue;
        
        for (const auto& next : adj[cur_node])
        {
            int next_cost = next.second;
            int next_node = next.first;

            if (cur_node == avoid_u && next_node == avoid_v) continue;
            if (cur_node == avoid_v && next_node == avoid_u) continue;
            if (dist_arr[next_node] <= cur_cost + next_cost) continue;

            dist_arr[next_node] = cur_cost + next_cost;
            pq.emplace(dist_arr[next_node], next_node);

            if (avoid_u == -1)
                parent[next_node] = cur_node;
        }
    }

    return dist_arr[end];
}

int solution(int n, int m, int s, int e, vector<vector<int>> roads) {
    vector<pair<int, int>> path;
    path.reserve(n);
    int result = 0;

    // 1. 초기화 (전역 배열 재사용 대비)
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
    }

    // 2. 양방향 그래프 구축
    for (const auto& r : roads)
    {
        adj[r[0]].emplace_back(r[1], r[2]);
        adj[r[1]].emplace_back(r[0], r[2]);
    }

    // 3. 최초 다익스트라 실행 (경로 탐색)
    run_dijkstra(s, e, -1, -1);

    // 4. parent 배열을 이용한 최단 경로 역추적 (간선 수집)
    int i = e;
    while (i != s)
    {
        path.emplace_back(parent[i], i);
        i = parent[i];
    }

    // 5. 수집된 간선을 하나씩 끊어보며 다익스트라 재실행 -> 최댓값 도출
    for (const auto& p : path)
        result = max(result, run_dijkstra(s, e, p.first, p.second));

    return result;
}
// =========================================================================

int main() {
    int n = 5; // 마을 수
    int m = 6; // 도로 수
    int s = 1; // 출발지
    int e = 5; // 도착지

    // {u, v, t} 
    vector<vector<int>> roads = {
        {1, 2, 2},
        {1, 3, 3},
        {2, 4, 4},
        {3, 4, 1},
        {4, 5, 2},
        {2, 5, 8}
    };

    /* * [시나리오 분석]
     * 최초 최단 경로: 1 -> 3 -> 4 -> 5 (시간: 3 + 1 + 2 = 6)
     * - (1, 3) 파괴 시: 1 -> 2 -> 4 -> 5 (시간: 2 + 4 + 2 = 8)
     * - (3, 4) 파괴 시: 1 -> 2 -> 4 -> 5 (시간: 2 + 4 + 2 = 8)
     * - (4, 5) 파괴 시: 1 -> 2 -> 5 (시간: 2 + 8 = 10)
     * 최악의 지연 시간: 10
     */

    int result = solution(n, m, s, e, roads);

    cout << "========================================" << endl;
    cout << "[최악의 우회 경로 도착 시간] : " << result << " (기대값: 10)" << endl;
    cout << "========================================" << endl;

    return 0;
}