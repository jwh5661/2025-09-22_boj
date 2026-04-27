/*
 * [프로그래머스 72413] 합승 택시 요금 (Lv.3)
 * - 훈련 날짜: 2026-04-27 (월)
 * - 알고리즘: 그래프 (Dijkstra 응용)
 * - 목적: 다중 출발점 다익스트라를 통한 최적의 경로 분기점 산출
 * - 엔진 실무 최적화:
 * 1. 무방향 그래프의 대칭성( dist( A, B ) == dist( B, A ) )을 활용하여 
 N번의 탐색을 3번의 다익스트라 호출로 압축( O( E log V ))
 * 2. 다익스트라 알고리즘을 독립적인 메서드로 모듈화하여 재사용성과 가독성 극대화.
 * 3. 3개의 경로 비용을 합산하는 과정에서 발생할 수 있는 
 Integer Overflow를 방지하기 위해 안전한 초기값( INF = 1e8 ) 설계.
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
    const int INF = 1e8;

    vector<int> dijkstra(int n, int start, const vector<pair<int, int>> adj[]) {
        vector<int> dist(n + 1, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.emplace(dist[start], start);

        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            int cost = cur.first;
            int node = cur.second;

            if (dist[node] < cost) continue;

            for (const auto& next : adj[node]) {
                int nCost = cost + next.first;
                int nNext = next.second;

                if (dist[nNext] <= nCost) continue;

                dist[nNext] = nCost;
                pq.emplace(nCost, nNext);
            }
        }
        return dist;
    }

    int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
        int answer = INF;

        vector<pair<int, int>> adj[201];
        for (auto& fare : fares) {
            adj[fare[0]].push_back({ fare[2], fare[1] });
            adj[fare[1]].push_back({ fare[2], fare[0] });
        }

        vector<int> FromS = dijkstra(n, s, adj);
        vector<int> FromA = dijkstra(n, a, adj);
        vector<int> FromB = dijkstra(n, b, adj);

        for (int i = 1; i <= n; i++)
            answer = min(answer, FromS[i] + FromA[i] + FromB[i]);

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    int n1 = 6, s1 = 4, a1 = 6, b1 = 2;
    vector<vector<int>> f1 = { {4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41}, {5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25} };
    // 기대 결과: 82

    cout << "[보스 미션] 실행 결과: " << sol.solution(n1, s1, a1, b1, f1) << " / 기대 결과: 82\n";

    return 0;
}