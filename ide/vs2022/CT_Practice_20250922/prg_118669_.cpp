/*
 * [프로그래머스 118669] 등산코스 정하기 (Lv.3)
 * - 훈련 날짜: 2026-05-18 (월)
 * - 알고리즘: Graph (그래프), Dijkstra (다익스트라 응용 - Min-Max Path)
 * - 목적: 다중 출발지에서 목적지까지 도달하는 수많은 경로 중, 최대 가중치(병목 구간)가 가장 작은 최적 경로 탐색
 * - 엔진 실무 최적화:
 * 1. Multi-Source Dijkstra: 모든 출입구를 우선순위 큐에 초깃값(0)으로 한 번에 밀어 넣어, 단 1회의 다익스트라 루프만으로 전체 맵의 병목 최적해를 도출함(O(E log V)).
 * 2. Cut-off (가지치기): 현재 큐에서 꺼낸 노드가 목적지(산봉우리)일 경우, 이웃 노드 탐색을 즉각 중단(continue)하여 불필요한 편도 이후의 연산 낭비를 완벽히 차단함.
 * 3. Memory Safety: C++ priority_queue의 top() 접근 시 `const auto&`를 사용할 경우 pop() 이후 발생하는 치명적인 Dangling Reference(허상 참조) 버그를 방지하기 위해, `const auto`를 통한 값 복사(Value Copy)를 수행하여 메모리 안정성을 확보함.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    struct Node {
        int intensity, pos;

        Node(int nintensity, int npos)
            :intensity(nintensity), pos(npos) {
        }

        bool operator>(const Node& other) const
        {
            return intensity > other.intensity;
        }
    };

    vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
        vector<int> answer(2);

        const int mx = 10000001;
        vector<vector<pair<int, int>>> adj(n + 1);
        vector<int> d(n + 1, mx);
        vector<bool> is_summit(n + 1, false);
        priority_queue<Node, vector<Node>, greater<Node>> pq;

        for (const int g : gates)
        {
            d[g] = 0;
            pq.emplace(d[g], g);
        }

        for (const int s : summits)
            is_summit[s] = true;

        for (const auto& p : paths)
        {
            adj[p[0]].emplace_back(p[2], p[1]);
            adj[p[1]].emplace_back(p[2], p[0]);
        }

        while (!pq.empty())
        {
            const auto cur = pq.top(); pq.pop();

            if (cur.intensity > d[cur.pos]) continue;

            if (is_summit[cur.pos]) continue;

            for (const auto& next : adj[cur.pos])
            {
                int new_intensity = max(cur.intensity, next.first);
                if (d[next.second] <= new_intensity) continue;

                d[next.second] = new_intensity;
                pq.emplace(d[next.second], next.second);
            }
        }

        answer[1] = mx;

        for (int i = 1; i <= n; i++)
        {
            if (!is_summit[i]) continue;

            if (answer[1] > d[i])
            {
                answer[0] = i;
                answer[1] = d[i];
            }
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    int n = 6;
    // [노드1, 노드2, 거리(비용)]
    vector<vector<int>> paths = {
        {1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {2, 5, 4},
        {3, 4, 4}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1}
    };
    vector<int> gates = { 1, 3 }; // 출입구
    vector<int> summits = { 5 };  // 산봉우리
    // 기대 결과: [5, 3]

    vector<int> result = sol.solution(n, paths, gates, summits);
    cout << "[테스트 1] 실행 결과: [" << result[0] << ", " << result[1] << "] / 기대 결과: [5, 3]\n";

    return 0;
}