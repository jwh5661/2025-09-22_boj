/*
 * [프로그래머스 12978] 배달 (Lv.2)
 * - 훈련 날짜: 2026-04-27 (월)
 * - 알고리즘: 그래프 (Dijkstra)
 * - 목적: 가중치가 있는 그래프에서 시작점으로부터 일정 거리 이하인 노드 탐색
 * - 엔진 실무 최적화:
 * 1. priority_queue와 greater를 활용한 Min-Heap 구조로 최단 거리 노드를 O( log V )만에 추출.
 * 2. 이미 더 짧은 경로로 방문한 노드는 큐에서 꺼내자마자 무시( cost > visited[node] )하는 
 조기 차단( Early Rejection ) 로직 적용.
 * 3. Data 영역에 선언된 전역 컨테이너( adj ) 사용 시, 
 멀티 세션( 다중 테스트 케이스 ) 환경에서 발생할 수 있는 상태 오염 주의.
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
    vector<pair<int, int>> adj[51];
    int visited[51];

    int solution(int N, vector<vector<int>> road, int K) {
        int answer = 0;
        const int INF = 1e9;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        fill(visited, visited + N + 1, INF);

        for (int i = 0; i < road.size(); i++)
        {
            int dep = road[i][0], arr = road[i][1], cost = road[i][2];

            adj[dep].emplace_back(cost, arr);
            adj[arr].emplace_back(cost, dep);
        }

        visited[1] = 0;
        pq.emplace(visited[1], 1);

        while (!pq.empty())
        {
            auto cur = pq.top(); pq.pop();
            int cost = cur.first;
            int node = cur.second;

            if (cost > visited[node]) continue;

            for (const auto& next : adj[node])
            {
                int ncost = cost + next.first;
                int nnode = next.second;

                if (visited[nnode] <= ncost) continue;
            
                visited[nnode] = ncost;
                pq.emplace(ncost, nnode);

            }
        }

        for (int i = 1; i <= N; i++)
        {
            if (visited[i] <= K) answer++;
        }

        return answer;
    }
};
// =========================================================================


int main() {
    Solution sol;

    int n1 = 5;
    vector<vector<int>> r1 = { {1, 2, 1}, {2, 3, 3}, {5, 2, 2}, {1, 4, 2}, {5, 3, 1}, {5, 4, 2} };
    int k1 = 3;
    // 기대 결과: 4

    int n2 = 6;
    vector<vector<int>> r2 = { {1, 2, 1}, {1, 3, 2}, {2, 3, 2}, {3, 4, 3}, {3, 5, 2}, {3, 5, 3}, {5, 6, 1} };
    int k2 = 4;
    // 기대 결과: 4

    cout << "[테스트 1] 실행 결과: " << sol.solution(n1, r1, k1) << " / 기대 결과: 4\n";
    cout << "[테스트 2] 실행 결과: " << sol.solution(n2, r2, k2) << " / 기대 결과: 4\n";

    return 0;
}